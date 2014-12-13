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

/* Nastav� jedno m��en� pacientovi */
void PatientMeasuredVals::setMeasuredVal(MeasuredVal * patientMeasuredVal, int patientNumber)
{
	measuredVals[patientNumber] = patientMeasuredVal;
}

/* Vr�t� jedno m��en� pacienta */
MeasuredVal * PatientMeasuredVals::getMeasuredVal(int patientNumber)
{
	return measuredVals[patientNumber];
}


MeasuredVal ** PatientMeasuredVals::getMeasuredVals()
{
	return measuredVals;
}


int PatientMeasuredVals::countMeasuredVals()
{
	return measuredValCount;
}
