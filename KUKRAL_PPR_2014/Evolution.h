#pragma once

#include "Individual.h"
#include "Bounds.h"
#include "RandomNumber.h"
#include "Fitness.h"

#define INI_SECTION_NAME "Bounds"
#define COUNT_INDIVIDUALS 40
#define F 1 //mutaèní konstanta mezi 0 a 2
#define CR 0.5 //práh køížení mezi 0 a 1

class Evolution
{
public:
	Evolution();
	~Evolution();
	void createFirstGen(int countMeasuredVals, MeasuredVal ** MeasuredVals);
private:
	void calVectors(Params ** mutationVectors);
	Individual ** individuals;
	Bounds * bounds;
	Fitness * fit;
	Individual * bestIndividual;
	double calBestFit();
	void createNew();
	Params ** createMutationVectors();
	Params * createMutationParams(Params * p1, Params *p2, Params *p3);
	Params ** createTryVectors(Params ** mutationVectors);
	double getMutationParam(double p1, double p2, double p3, double max, double min);
	RandomNumber * r;
	double createTryParam(double tryParam, double mutationParam);
public:
	double getBestFit();
	double startNew(int i);
	Individual * getBestIndividual();
private:
	void loadBounds();
};

