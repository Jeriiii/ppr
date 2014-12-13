#pragma once

#include "MeasuredVal.h"
#include "libs/cpp-sqlite/CppSQLite3.h"
#include "PatientMeasuredVals.h"
#include <vector>

typedef std::vector<double> dvector; //kratší zápis vektoru

class MeasuredCreator
{
public:
	MeasuredCreator();
	~MeasuredCreator();
	PatientMeasuredVals ** getMeasuredVals();
	int getCountPatients();
	PatientMeasuredVals ** patientMeasredVals;
private:
	PatientMeasuredVals ** createMeasredVal();
	int countPatients;
	PatientMeasuredVals * getPatient(CppSQLite3DB * db, int patientNumber, const char * patientId);
	int countMeasuredValByPatient(CppSQLite3DB * db, const char * patientId);
	CppSQLite3Query getMeasuredValByPatient(CppSQLite3DB * db, const char * patientId);
	PatientMeasuredVals * recalculateBloodIst(dvector tbVec, dvector bVec, dvector tiVec, dvector iVec, PatientMeasuredVals * pmv, int k);
};

