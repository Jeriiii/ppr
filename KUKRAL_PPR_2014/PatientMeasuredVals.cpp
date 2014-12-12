#include "stdafx.h"
#include "PatientMeasuredVals.h"

/**
* Obsahuje všechna namìøená data jednoho pacienta
*/

PatientMeasuredVals::PatientMeasuredVals(int measuredValCount)
{
	measuredVals = new MeasuredVal*[measuredValCount];
	PatientMeasuredVals::measuredValCount = measuredValCount;

}



PatientMeasuredVals::~PatientMeasuredVals()
{
}

/* pøidá k pacientovi další namìøené hodnoty */
void PatientMeasuredVals::setMeasuredVal(MeasuredVal * patientMeasuredVal, int patientNumber)
{
	measuredVals[patientNumber] = patientMeasuredVal;
}


MeasuredVal ** PatientMeasuredVals::getMeasuredVals()
{
	return measuredVals;
}


int PatientMeasuredVals::countMeasuredVals()
{
	return measuredValCount;
}
