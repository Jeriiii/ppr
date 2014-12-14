#pragma once

#include "MeasuredVal.h"
#include "Bounds.h"
#include "Params.h"

class Individual
{

public:
	Individual(int countMeasuredVal, MeasuredVal ** measuredVals, Bounds * bounds);
	~Individual();
	int cal();
private:
	Params * generateParams();
	double * params;
	Bounds * bounds;
public:
	void init();
	char *test;
private:
	int countMeasuredVal;
	/* pole struktur namìøených hodnot */
	MeasuredVal **measuredVals;
};

