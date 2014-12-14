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
	Params * getParams();
	int getCountMeasuredVal();
	MeasuredVal ** getMeasuredVals();
	void setParams(Params * params);
	void setFitness(double fitness);
	double getFitness();
private:
	Params * generateParams();
	Params * params;
	Bounds * bounds;
	double fitness;
public:
	void init();
	char *test;
private:
	int countMeasuredVal;
	/* pole struktur namìøených hodnot */
	MeasuredVal **measuredVals;
};

