#include "stdafx.h"
#include "PatientMeasuredVals.h"

/**
* Obsahuje v�echna nam��en� data jednoho pacienta
*/

PatientMeasuredVals::PatientMeasuredVals(int measuredValCount)
{
	measuredVals = new MeasuredVal*[measuredValCount];
	PatientMeasuredVals::measuredValCount = measuredValCount;

}



PatientMeasuredVals::~PatientMeasuredVals()
{
}

/* p�id� k pacientovi dal�� nam��en� hodnoty */
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
