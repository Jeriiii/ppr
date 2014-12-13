#pragma once

#include "MeasuredVal.h"
#include "Bounds.h"

class Individual
{

public:
	Individual(int countMeasuredVal, MeasuredVal ** measuredVals, Bounds * bounds);
	~Individual();
	int cal();
private:
	int createParams();
	double * params;
public:
	void init();
	char *test;
private:
	int countMeasuredVal;
	/* pole struktur namìøených hodnot */
	MeasuredVal **measuredVals;
};

