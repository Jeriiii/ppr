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

/* Nastaví jedno mìøení pacientovi */
void PatientMeasuredVals::setMeasuredVal(MeasuredVal * patientMeasuredVal, int patientNumber)
{
	measuredVals[patientNumber] = patientMeasuredVal;
}

/* Vrátí jedno mìøení pacienta */
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
