#include "stdafx.h"
#include "MeasuredCreator.h"
#include "PatientMeasuredVals.h"
#include "spline.h"
#include <sqlite3.h>
#include <iostream>
#include <string.h>
#include <QApplication> // Qt includes
#include <QPushButton>
#include <QLabel>

/**
* T��da zaji��uj�c� ny�ten� nam��en�ch hodnot z datab�ze a ulo�en� do struktury
*/
MeasuredCreator::MeasuredCreator()
{
	patientMeasredVals = createMeasredVal();
}


MeasuredCreator::~MeasuredCreator()
{
}

/* vr�t� nam��en� hodnoty pacient� */
PatientMeasuredVals ** MeasuredCreator::getMeasuredVals()
{
	return patientMeasredVals;
}

/* vr�t� po�et pacient� */
int MeasuredCreator::getCountPatients()
{
	return countPatients;
}

/* vytvo�� od v�ech pacient� z�znamy o nam��en�ch datech */
PatientMeasuredVals ** MeasuredCreator::createMeasredVal()
{
	int i;
	const char *patientId;
	CppSQLite3DB db;
	CppSQLite3Query patients;
	PatientMeasuredVals ** patientsMeasured = NULL;


	try{
		db.open("data.sqlite3");
		/* celkov� po�et pacient� */
		countPatients = db.execScalar("SELECT COUNT(id) FROM subject");
	
		/* slukov�n� hodnot jednotliv�ch pacient� */
		patients = db.execQuery("SELECT id FROM subject");

		patientsMeasured = new PatientMeasuredVals *[countPatients];
		for (i = 0; !patients.eof(); i++)
		{
			patientId = patients.fieldValue(0);
			patientsMeasured[i] = getPatient(&db, i, patientId);
			patients.nextRow();
		}

		patients.finalize();
		//clouse db se zavola automaticky v destruktoru
	}
	catch (CppSQLite3Exception& e)
	{
		std::cerr << e.errorCode() << ":" << e.errorMessage() << std::endl;
	}

	return patientsMeasured;
}


/* Vr�t� pacientovo nam��en� hodnoty */
PatientMeasuredVals * MeasuredCreator::getPatient(CppSQLite3DB * db, int patientNumber, const char *patientId)
{
	int k, measuredValCount;
	std::vector<double> tbVec, tiVec, bVec, iVec;
	double b, i, t;

	MeasuredVal * measuredVal;
	PatientMeasuredVals * patientMeasuredVals;
	CppSQLite3Query measuredValDb;
	std::string loadNum;

	measuredValDb = getMeasuredValByPatient(db, patientId);
	measuredValCount = countMeasuredValByPatient(db, patientId);

	patientMeasuredVals = new PatientMeasuredVals(measuredValCount);

	/* na�te nam��en� hodnoty */
	for (k = 0; !measuredValDb.eof(); k++)
	{
		measuredVal = new MeasuredVal();
		t = atof(measuredValDb.fieldValue(0));
		measuredVal->t = t;

		/* pokud je nam��ena krev, ulo�� ji */
		if (! measuredValDb.fieldIsNull(1)) {
			b = atof(measuredValDb.fieldValue(1));
			measuredVal->b = b;

			tbVec.push_back(t);
			bVec.push_back(b);
		}

		/* pokud je nam��ena its, ulo�� ji */
		if (!measuredValDb.fieldIsNull(2)) {
			i = atof(measuredValDb.fieldValue(2));
			measuredVal->i = i;

			tiVec.push_back(t);
			iVec.push_back(i);
		}

		patientMeasuredVals->setMeasuredVal(measuredVal, k);
		measuredValDb.nextRow();
	}

	patientMeasuredVals = recalculateBloodIst(tbVec, bVec, tiVec, iVec, patientMeasuredVals, k);
	
	return patientMeasuredVals;
}

/* dopo��t� nevypln�n� polo�ky krve a ist */
PatientMeasuredVals * MeasuredCreator::recalculateBloodIst(dvector tbVec, dvector bVec, dvector tiVec, dvector iVec, PatientMeasuredVals * pmv, int k) {
	int j;
	MeasuredVal * measuredVal;
	
	/* ulo�� vektory pro pozd�j�� dopo��t�v�n� */
	tk::spline iFnc, bFnc;
	bFnc.set_points(tbVec, bVec);
	iFnc.set_points(tiVec, iVec);

	/* dopo��t� nevypln�n� hodnoty */
	for (j = 0; j<k; j++)
	{
		measuredVal = pmv->getMeasuredVal(j);
		if (measuredVal->b == 0.0) {
			/* dopo��t� hodnotu b */
			measuredVal->b = bFnc(measuredVal->t);
		}

		if (measuredVal->i == 0.0) {
			/* dopo��t� hodnotu b */
			measuredVal->i = bFnc(measuredVal->t);
		}

	}

	return pmv;
}

/* po�et v�ech hodnot jednoho pacienta */
int MeasuredCreator::countMeasuredValByPatient(CppSQLite3DB * db, const char * patientId)
{
	char query[70];
	strcpy_s(query, "SELECT count(id) FROM measuredvalue WHERE segmentid = ");
	strcat_s(query, patientId);
	return db->execScalar(query);
}

/* vybr�n� v�ech hodnot jednoho pacienta */
CppSQLite3Query MeasuredCreator::getMeasuredValByPatient(CppSQLite3DB * db, const char * patientId)
{
	CppSQLite3Query q;
	char query[80];
	strcpy_s(query, "SELECT measuredat, blood, ist FROM measuredvalue WHERE segmentid = ");
	strcat_s(query, patientId);
	q = db->execQuery(query);
	return q;
}

/* p�evod �asu do jin�ho form�tu */
double QDateTime2RatTime(const QDateTime *qdt) {
	const qint64 diffFrom1970To1900 = 2209161600000;
	const double MSecsPerDay = 24.0*60.0*60.0*1000.0;
	const double InvMSecsPerDay = 1.0 / MSecsPerDay;

	qint64 diff = qdt->toMSecsSinceEpoch() + diffFrom1970To1900;
	return ((double)diff)*InvMSecsPerDay;
}
