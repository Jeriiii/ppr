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
* Tøída zajišující nyètení namìøenıch hodnot z databáze a uloení do struktury
*/
MeasuredCreator::MeasuredCreator()
{
	patientMeasredVals = createMeasredVal();
}


MeasuredCreator::~MeasuredCreator()
{
}

/* vrátí namìøené hodnoty pacientù */
PatientMeasuredVals ** MeasuredCreator::getMeasuredVals()
{
	return patientMeasredVals;
}

/* vrátí poèet pacientù */
int MeasuredCreator::getCountPatients()
{
	return countPatients;
}

/* vytvoøí od všech pacientù záznamy o namìøenıch datech */
PatientMeasuredVals ** MeasuredCreator::createMeasredVal()
{
	int i;
	const char *patientId;
	CppSQLite3DB db;
	CppSQLite3Query patients;
	PatientMeasuredVals ** patientsMeasured = NULL;


	try{
		db.open("data.sqlite3");
		/* celkovı poèet pacientù */
		countPatients = db.execScalar("SELECT COUNT(id) FROM subject");
	
		/* slukování hodnot jednotlivıch pacientù */
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


/* Vrátí pacientovo namìøené hodnoty */
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

	/* naète namìøené hodnoty */
	for (k = 0; !measuredValDb.eof(); k++)
	{
		measuredVal = new MeasuredVal();
		t = atof(measuredValDb.fieldValue(0));
		measuredVal->t = t;

		/* pokud je namìøena krev, uloí ji */
		if (! measuredValDb.fieldIsNull(1)) {
			b = atof(measuredValDb.fieldValue(1));
			measuredVal->b = b;

			tbVec.push_back(t);
			bVec.push_back(b);
		}

		/* pokud je namìøena its, uloí ji */
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

/* dopoèítá nevyplnìné poloky krve a ist */
PatientMeasuredVals * MeasuredCreator::recalculateBloodIst(dvector tbVec, dvector bVec, dvector tiVec, dvector iVec, PatientMeasuredVals * pmv, int k) {
	int j;
	MeasuredVal * measuredVal;
	
	/* uloí vektory pro pozdìjší dopoèítávání */
	tk::spline iFnc, bFnc;
	bFnc.set_points(tbVec, bVec);
	iFnc.set_points(tiVec, iVec);

	/* dopoèítá nevyplnìné hodnoty */
	for (j = 0; j<k; j++)
	{
		measuredVal = pmv->getMeasuredVal(j);
		if (measuredVal->b == 0.0) {
			/* dopoèítá hodnotu b */
			measuredVal->b = bFnc(measuredVal->t);
		}

		if (measuredVal->i == 0.0) {
			/* dopoèítá hodnotu b */
			measuredVal->i = bFnc(measuredVal->t);
		}

	}

	return pmv;
}

/* poèet všech hodnot jednoho pacienta */
int MeasuredCreator::countMeasuredValByPatient(CppSQLite3DB * db, const char * patientId)
{
	char query[70];
	strcpy_s(query, "SELECT count(id) FROM measuredvalue WHERE segmentid = ");
	strcat_s(query, patientId);
	return db->execScalar(query);
}

/* vybrání všech hodnot jednoho pacienta */
CppSQLite3Query MeasuredCreator::getMeasuredValByPatient(CppSQLite3DB * db, const char * patientId)
{
	CppSQLite3Query q;
	char query[80];
	strcpy_s(query, "SELECT measuredat, blood, ist FROM measuredvalue WHERE segmentid = ");
	strcat_s(query, patientId);
	q = db->execQuery(query);
	return q;
}

/* pøevod èasu do jiného formátu */
double QDateTime2RatTime(const QDateTime *qdt) {
	const qint64 diffFrom1970To1900 = 2209161600000;
	const double MSecsPerDay = 24.0*60.0*60.0*1000.0;
	const double InvMSecsPerDay = 1.0 / MSecsPerDay;

	qint64 diff = qdt->toMSecsSinceEpoch() + diffFrom1970To1900;
	return ((double)diff)*InvMSecsPerDay;
}
