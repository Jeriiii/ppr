#include "stdafx.h"
#include "Individual.h"
#include "RandomNumber.h"
#include "Params.h"

/**
* Jedinec v evoluci
*/

Individual::Individual(int countMeasuredVal, MeasuredVal ** measuredVals, Bounds * bounds, int serialNumber)
{
	Individual::bounds = bounds;
	Individual::countMeasuredVal = countMeasuredVal;
	Individual::measuredVals = measuredVals;
	Individual::serialNumber = serialNumber;
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

/* vr�t� pr�v� pou��van� parametry */
Params * Individual::getParams() {
	return params;
}

/* nastav� jedinci nov� parametry */
void Individual::setParams(Params * params) {
	delete Individual::params; //smaz�n� star�ch parametr�
	Individual::params = params;
}

void Individual::setFitness(double fitness) {
	Individual::fitness = fitness;
}

double Individual::getFitness() {
	return fitness;
}

/* vr�t� po�et nam��en�ch hodnot */
int Individual::getCountMeasuredVal() {
	return countMeasuredVal;
}

/* vr�t� nam��en� hodnoty */
MeasuredVal ** Individual::getMeasuredVals() {
	return measuredVals;
}

/* vygeneruje zcela nov� parametry */
Params * Individual::generateParams()
{
	RandomNumber * rn = new RandomNumber();
	Params * params = new Params;

	params->p = rn->generate(bounds->pmin, bounds->pmax);
	params->cg = rn->generate(bounds->cgmin, bounds->cgmax);
	params->c = rn->generate(bounds->cmin, bounds->cmax);

	params->pp = rn->generate(bounds->ppmin, bounds->ppmax);
	params->cgp = rn->generate(bounds->cgpmin, bounds->cgpmax);
	params->cp = rn->generate(bounds->cpmin, bounds->cpmax);

	params->dt = rn->generate(bounds->dtmin, bounds->dtmax);
	params->h = rn->generate(bounds->hmin, bounds->hmax);

	params->k = rn->generate(bounds->kmin, bounds->kmax);

	params->m = rn->generate(bounds->mmin, bounds->mmax);
	params->n = rn->generate(bounds->nmin, bounds->nmax);

	return params;
}


