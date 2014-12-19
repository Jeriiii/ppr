#include "stdafx.h"
#include "MeasuredCreator.h"
#include "PatientMeasuredVals.h"
#include "spline.h"
//#include <sqlite3.h>
#include <iostream>
#include <string.h>
//#include <QApplication> // Qt includes
//#include <QPushButton>
//#include <QLabel>

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
	int k, measuredValCount, serialNumber = 0;
	std::vector<double> tiVec, iVec;
	double b, i, t, lastT = 0.0, ttest = 0.0;
	const char * date;

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
		measuredVal = NULL;
		date = measuredValDb.fieldValue(0);
		//t = atof(date);
		ttest++;
		t = ttest / 2000.0;
		assert(t <= 1);
		assert(t != 0);

		/* pokud je nam��ena its, ulo�� ji */
		if (!measuredValDb.fieldIsNull(2)) {
			i = atof(measuredValDb.fieldValue(2));

			tiVec.push_back(t);
			iVec.push_back(i);

			lastT = t;
		}

		/* pokud je nam��ena b, ulo�� ji */
		if (!measuredValDb.fieldIsNull(1)) {
			measuredVal = new MeasuredVal();
			measuredVal->t = t;

			b = atof(measuredValDb.fieldValue(1));
			measuredVal->b = b;

			if (!measuredValDb.fieldIsNull(2)) {
				measuredVal->i = i;
			}
		}		

		/* ukl�d� jen z�znamy s napo��tanou hodnotou krve */
		if (!measuredValDb.fieldIsNull(1)) {
			patientMeasuredVals->setMeasuredVal(measuredVal, serialNumber);
			serialNumber++;
		}
		measuredValDb.nextRow();
	}


	patientMeasuredVals = recalculateBloodIst(tiVec, iVec, patientMeasuredVals, serialNumber, lastT);
	
	return patientMeasuredVals;
}

/* dopo��t� nevypln�n� polo�ky krve a ist */
PatientMeasuredVals * MeasuredCreator::recalculateBloodIst(dvector tiVec, dvector iVec, PatientMeasuredVals * pmv, int k, double lastT) {
	int j;
	MeasuredVal * measuredVal;
	
	/* ulo�� vektory pro pozd�j�� dopo��t�v�n� */
	tk::spline iFnc;

	iFnc.set_points(tiVec, iVec);

	/* dopo��t� nevypln�n� hodnoty ist */
	for (j = 0; j<k; j++)
	{
		measuredVal = pmv->getMeasuredVal(j);

		if (measuredVal->i == 0.0 && measuredVal->t <= lastT) {
			/* dopo��t� hodnotu i */
			measuredVal->i = iFnc(measuredVal->t);
		}

	}

	return pmv;
}

/* po�et v�ech hodnot jednoho pacienta */
int MeasuredCreator::countMeasuredValByPatient(CppSQLite3DB * db, const char * patientId)
{
	char query[90];
	strcpy_s(query, "SELECT count(id) FROM measuredvalue WHERE blood IS NOT NULL AND segmentid = ");
	strcat_s(query, patientId);
	return db->execScalar(query);
}

/* vybr�n� v�ech hodnot jednoho pacienta */
CppSQLite3Query MeasuredCreator::getMeasuredValByPatient(CppSQLite3DB * db, const char * patientId)
{
	CppSQLite3Query q;
	char query[100];
	strcpy_s(query, "SELECT measuredat, blood, ist FROM measuredvalue WHERE segmentid = ");
	strcat_s(query, patientId);
	q = db->execQuery(query);
	return q;
}

/* p�evod �asu do jin�ho form�tu */
//double QDateTime2RatTime(const QDateTime *qdt) {
//	const qint64 diffFrom1970To1900 = 2209161600000;
//	const double MSecsPerDay = 24.0*60.0*60.0*1000.0;
//	const double InvMSecsPerDay = 1.0 / MSecsPerDay;
//
//	qint64 diff = qdt->toMSecsSinceEpoch() + diffFrom1970To1900;
//	return ((double)diff)*InvMSecsPerDay;
//}
