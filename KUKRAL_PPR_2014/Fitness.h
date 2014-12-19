#pragma once

#include "Params.h"
#include "MeasuredVal.h"
#include "vector.h"
#include "spline.h"

class Fitness
{
public:
	Fitness(MeasuredVal ** MeasuredVals, int countMeasuredVals);
	~Fitness();
	int countMeasuredVals;
	double sumDiff(Params * params);
private:
	
	tk::spline istAproximation;
	MeasuredVal ** MeasuredVals;
	double getFitness(Params * params, MeasuredVal * MeasuredVal);
	void calIstAproximation();
	double getIst(double t);
};

