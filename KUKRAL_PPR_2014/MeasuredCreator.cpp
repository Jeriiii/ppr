#include "stdafx.h"
#include "MeasuredCreator.h"
#include <sqlite3.h>
#include <iostream>
#include <string.h>

/**
* Tøída zajišující nyètení namìøených hodnot z databáze a uložení do struktury
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

/* vytvoøí od všech pacientù záznamy o namìøených datech */
MeasuredVal *** MeasuredCreator::createMeasredVal()
{
	int i;
	const char *patientId;
	CppSQLite3DB db;
	CppSQLite3Query patients;
	MeasuredVal *** patientsMeasured;

	db.open("data.sqlite3");
	/* celkový poèet pacientù */
	countPatients = (int)db.execScalar("SELECT COUNT(id) FROM subject");
	
	/* slukování hodnot jednotlivých pacientù */
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


/* Vrátí pacientovo namìøené hodnoty */
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
		//TODO nastavení èasu measuredVal->t
		measuredVal->b = atof(measuredValDb.fieldValue(1));
		measuredVal->i = atof(measuredValDb.fieldValue(2));
		measuredVals[i] = measuredVal;
		i++;
		measuredValDb.nextRow();
	}
	return measuredVals;
}



/* poèet všech hodnot jednoho pacienta */
int MeasuredCreator::countMeasuredValByPatient(CppSQLite3DB * db, const char * patientId)
{
	char * query;
	strcpy(query, "SELECT count(id) FROM measuredvalue WHERE segmentid = ");
	strcat(query, patientId);
	return db->execScalar(query);
}

/* vybrání všech hodnot jednoho pacienta */
CppSQLite3Query * MeasuredCreator::getMeasuredValByPatient(CppSQLite3DB * db, const char * patientId)
{
	char * query;
	strcpy(query, "SELECT measuredat, blood, ins FROM measuredvalue WHERE segmentid = ");
	strcat(query, patientId);
	return &db->execQuery(query);
}
