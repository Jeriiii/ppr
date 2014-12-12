#include "MeasuredVal.h";
#pragma once
class Individual
{

public:
	Individual(int countMeasuredVal, MeasuredVal ** measuredVals);
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

