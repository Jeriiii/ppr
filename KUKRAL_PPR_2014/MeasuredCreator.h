#include "MeasuredVal.h";
#include "libs/cpp-sqlite/CppSQLite3.h"
#pragma once
class MeasuredCreator
{
public:
	MeasuredCreator();
	~MeasuredCreator();
	MeasuredVal ** getMeasuredVal();
	/* vrátí poèet pacientù */
	int getCountPatients();
	MeasuredVal *** createMeasredVal();
	MeasuredVal *** patientMeasredVals;
private:
	CppSQLite3DB *database;
	int countPatients;
	MeasuredVal ** getPatient(CppSQLite3DB * db, int patientNumber, const char * patientId);
	int countMeasuredValByPatient(CppSQLite3DB * db, const char * patientId);
	CppSQLite3Query * getMeasuredValByPatient(CppSQLite3DB * db, const char * patientId);
};

