#include "stdafx.h"
#include "Individual.h"
#include "RandomNumber.h"



Individual::Individual(int countMeasuredVal, MeasuredVal ** measuredVals)
{
	createParams();
	Individual::countMeasuredVal = countMeasuredVal;
}


Individual::~Individual()
{
	printf("des");
	delete[] params;
}


int Individual::cal()
{
	return 0;
}


int Individual::createParams()
{
	RandomNumber * rn = new RandomNumber(4);
	params = new double[10];
	params[0] = rn->generate(0.1, 100.1);
	return 0;
}
