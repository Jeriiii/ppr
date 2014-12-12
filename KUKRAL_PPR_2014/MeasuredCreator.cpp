#include "stdafx.h"
#include "MeasuredCreator.h"
#include "PatientMeasuredVals.h"
//#include "libs/qtools/QDateTime.h"
#include "spline.h"
#include <sqlite3.h>
#include <iostream>
#include <string.h>
#include <vector>

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
	int i, measuredValCount;
	
	MeasuredVal * measuredVal;
	PatientMeasuredVals * patientMeasuredVals;
	CppSQLite3Query measuredValDb;
	std::string loadNum;

	measuredValDb = getMeasuredValByPatient(db, patientId);
	measuredValCount = countMeasuredValByPatient(db, patientId);

	patientMeasuredVals = new PatientMeasuredVals(measuredValCount);
	for (i = 0; !measuredValDb.eof(); i++)
	{
		measuredVal = new MeasuredVal();
		measuredVal->t = atof(measuredValDb.fieldValue(0));
		if (! measuredValDb.fieldIsNull(1)) {
			measuredVal->b = atof(measuredValDb.fieldValue(1));
		}
		if (!measuredValDb.fieldIsNull(2)) {
			measuredVal->i = atof(measuredValDb.fieldValue(2));
		}

		//std::vector<double> X(5), Y(5);
		//X[0] = 0.1; X[1] = 0.4; X[2] = 1.2; X[3] = 1.8; X[4] = 2.0;
		//Y[0] = 0.1; Y[1] = 0.7; Y[2] = 0.6; Y[3] = 1.1; Y[4] = 0.9;

		//tk::spline s;
		//s.set_points(X, Y);    // currently it is required that X is already sorted

		//double x = 1.5;

		//printf("spline at %f is %f\n", x, s(x));

		patientMeasuredVals->setMeasuredVal(measuredVal, i);
		measuredValDb.nextRow();
	}
	
	return patientMeasuredVals;
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
//double QDateTime2RatTime(const QDateTime *qdt) {
//	const qint64 diffFrom1970To1900 = 2209161600000;
//	const double MSecsPerDay = 24.0*60.0*60.0*1000.0;
//	const double InvMSecsPerDay = 1.0 / MSecsPerDay;
//
//	qint64 diff = qdt->toMSecsSinceEpoch() + diffFrom1970To1900;
//	return ((double)diff)*InvMSecsPerDay;
//}
