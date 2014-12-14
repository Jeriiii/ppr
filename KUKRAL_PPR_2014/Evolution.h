#pragma once

#include "Individual.h"
#include "Bounds.h"
#include "RandomNumber.h"

#define INI_SECTION_NAME "Bounds"
#define F 1 //mutaèní konstanta mezi 0 a 2
#define CR 0.5 //práh køížení mezi 0 a 1

class Evolution
{
public:
	Evolution();
	~Evolution();
private:
	void calVectors(Params ** mutationVectors);
	int countIndividuals;
	Individual ** individuals;
	Bounds * bounds;
	Individual * bestIndividual;
	double calBestFit();
	void createNew();
	void createFirstGen();
	Params ** createMutationVectors();
	Params * createMutationParams(Params * p1, Params *p2, Params *p3);
	Params ** createTryVectors(Params ** mutationVectors);
	double getMutationParam(double p1, double p2, double p3, double max, double min);
	RandomNumber * r;
public:
	double getBestFit();
	double startNew();
	Individual * getBestIndividual();
private:
	void loadBounds();
};

