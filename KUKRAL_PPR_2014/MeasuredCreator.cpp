#include "stdafx.h"
#include "MeasuredCreator.h"
#include <sqlite3.h>
#include <iostream>
#include <string.h>

/**
* T��da zaji��uj�c� ny�ten� nam��en�ch hodnot z datab�ze a ulo�en� do struktury
*/
MeasuredCreator::MeasuredCreator()
{
	patientMeasredVals = createMeasredVal();
}


MeasuredCreator::~MeasuredCreator()
{
	delete database;
}


MeasuredVal ** MeasuredCreator::getMeasuredVal()
{
	return NULL;
}


int MeasuredCreator::getCountPatients()
{
	return countPatients;
}

/* vytvo�� od v�ech pacient� z�znamy o nam��en�ch datech */
MeasuredVal *** MeasuredCreator::createMeasredVal()
{
	int i;
	const char *patientId;
	CppSQLite3DB db;
	CppSQLite3Query patients;
	MeasuredVal *** patientsMeasured;

	db.open("data.sqlite3");
	/* celkov� po�et pacient� */
	countPatients = (int)db.execScalar("SELECT COUNT(id) FROM subject");
	
	/* slukov�n� hodnot jednotliv�ch pacient� */
	patients = db.execQuery("SELECT id FROM subject");

	i = 0;
	patientsMeasured = new MeasuredVal **[countPatients];
	while (!patients.eof())
	{
		patientId = patients.fieldValue(0);
		patientsMeasured[i] = getPatient(&db, i, patientId);
		i++;
		patients.nextRow();
	}

	patients.finalize();
	//clouse db se zavola automaticky v destruktoru

	return patientsMeasured;
}


/* Vr�t� pacientovo nam��en� hodnoty */
MeasuredVal ** MeasuredCreator::getPatient(CppSQLite3DB * db, int patientNumber, const char *patientId)
{
	int i, measuredValCount;
	
	MeasuredVal * measuredVal;
	MeasuredVal ** measuredVals;
	CppSQLite3Query measuredValDb;

	measuredValDb = *getMeasuredValByPatient(db, patientId);
	measuredValCount = countMeasuredValByPatient(db, patientId);

	i = 0;
	measuredVals = new MeasuredVal*[measuredValCount];
	while (!measuredValDb.eof())
	{
		measuredVal = new MeasuredVal();
		//TODO nastaven� �asu measuredVal->t
		measuredVal->b = atof(measuredValDb.fieldValue(1));
		measuredVal->i = atof(measuredValDb.fieldValue(2));
		measuredVals[i] = measuredVal;
		i++;
		measuredValDb.nextRow();
	}
	return measuredVals;
}



/* po�et v�ech hodnot jednoho pacienta */
int MeasuredCreator::countMeasuredValByPatient(CppSQLite3DB * db, const char * patientId)
{
	char * query;
	strcpy(query, "SELECT count(id) FROM measuredvalue WHERE segmentid = ");
	strcat(query, patientId);
	return db->execScalar(query);
}

/* vybr�n� v�ech hodnot jednoho pacienta */
CppSQLite3Query * MeasuredCreator::getMeasuredValByPatient(CppSQLite3DB * db, const char * patientId)
{
	char * query;
	strcpy(query, "SELECT measuredat, blood, ins FROM measuredvalue WHERE segmentid = ");
	strcat(query, patientId);
	return &db->execQuery(query);
}
