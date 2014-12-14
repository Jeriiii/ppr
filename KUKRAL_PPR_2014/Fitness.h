#pragma once

#include "Params.h"
#include "MeasuredVal.h"
#include "vector.h"
#include "spline.h"

class Fitness
{
public:
	Fitness(MeasuredVal ** measuredVals, int countMeasuredVals);
	~Fitness();
	int getMedian(Params * params);
	int countMeasuredVals;
private:
	
	tk::spline istAproximation;
	MeasuredVal ** MeasuredVals;
	int getFitness(Params * params, MeasuredVal * MeasuredVal);
	void calIstAproximation();
	double getIst(double t);
};

