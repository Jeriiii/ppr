#pragma once

#include "MeasuredVal.h"

class PatientMeasuredVals
{
public:
	PatientMeasuredVals(int measuredValCount);
	~PatientMeasuredVals();
private:
	MeasuredVal ** measuredVals;
	int measuredValCount;
public:
	void setMeasuredVal(MeasuredVal * patientMeasuredVal, int patientNumber);
	MeasuredVal ** getMeasuredVals();
	int countMeasuredVals();
	MeasuredVal * getMeasuredVal(int patientNumber);
};

