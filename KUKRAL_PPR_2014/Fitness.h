#pragma once

#include "Params.h"
#include "MeasuredVal.h"
#include "vector.h"
#include "spline.h"

class Fitness
{
public:
	Fitness();
	~Fitness();
	double getMedian(Params * params);
	int countMeasuredVals;
	void setMeasuredVals(MeasuredVal ** MeasuredVals, int countMeasuredVals);
private:
	
	tk::spline istAproximation;
	MeasuredVal ** MeasuredVals;
	double getFitness(Params * params, MeasuredVal * MeasuredVal);
	void calIstAproximation();
	double getIst(double t);
};

