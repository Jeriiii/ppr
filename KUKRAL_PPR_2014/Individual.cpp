#include "stdafx.h"
#include "Individual.h"
#include "RandomNumber.h"
#include "Params.h"

/**
* Jedinec v evoluci
*/

Individual::Individual(int countMeasuredVal, MeasuredVal ** measuredVals, Bounds * bounds)
{
	Individual::bounds = bounds;
	Individual::countMeasuredVal = countMeasuredVal;
	Individual::measuredVals = measuredVals;
	params = generateParams();
}


Individual::~Individual()
{
	delete[] measuredVals;
	delete params;
}


int Individual::cal()
{
	return 0;
}

/* vrátí právì pouívané parametry */
Params * Individual::getParams() {
	return params;
}

/* nastaví jedinci nové parametry */
void Individual::setParams(Params * params) {
	Individual::params = params;
}

void Individual::setFitness(double fitness) {
	Individual::fitness = fitness;
}

double Individual::getFitness() {
	return fitness;
}

/* vrátí poèet namìøenıch hodnot */
int Individual::getCountMeasuredVal() {
	return countMeasuredVal;
}

/* vrátí namìøené hodnoty */
MeasuredVal ** Individual::getMeasuredVals() {
	return measuredVals;
}

/* vygeneruje zcela nové parametry */
Params * Individual::generateParams()
{
	RandomNumber * rn = new RandomNumber();
	Params * params = new Params;

	params->p = rn->generate(bounds->pmin, bounds->pmax, 1);
	params->cg = rn->generate(bounds->cgmin, bounds->cgmax, 2);
	params->c = rn->generate(bounds->cmin, bounds->cmax, 3);

	params->pp = rn->generate(bounds->ppmin, bounds->ppmax, 4);
	params->cgp = rn->generate(bounds->cgpmin, bounds->cgpmax, 5);
	params->cp = rn->generate(bounds->cpmin, bounds->cpmax, 6);

	params->dt = rn->generate(bounds->dtmin, bounds->dtmax, 7);
	params->h = rn->generate(bounds->hmin, bounds->hmax, 8);

	params->k = rn->generate(bounds->kmin, bounds->kmax, 9);

	params->m = rn->generate(bounds->mmin, bounds->mmax, 10);
	params->n = rn->generate(bounds->nmin, bounds->nmax, 11);

	return params;
}
