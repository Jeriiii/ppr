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
	generateParams();
}


Individual::~Individual()
{
	delete[] measuredVals;
	delete[] params;
}


int Individual::cal()
{
	return 0;
}

/* vygeneruje zcela nové parametry */
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
