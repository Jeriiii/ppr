#include "stdafx.h"
#include "Evolution.h"
#include "libs/simpleini-master/SimpleIni.h"
#include "Fitness.h"
#include <iostream>

#include "RandomNumber.h"

Evolution::Evolution()
{
	r = new RandomNumber;
	bestIndividual = NULL;
	loadBounds();
}


Evolution::~Evolution()
{
	int i;
	for (i = 0; i < COUNT_INDIVIDUALS; i++)
	{
		delete individuals[i];
	}
	delete individuals;
	delete r;
}

/* vytvoøí zkušební jedince a vybere ty lepší ze zkušebních a z min. generace */
void Evolution::calVectors(Params ** mutationVectors)
{
	int i;
	Params ** tryVectors; //parametry zkušebních jedincù
	Params * tryParams; //parametry jednoho zkušeního jedince
	Fitness * fit = new Fitness();
	double tryFitness;
	Individual * oldIndividual; //jedinec ze staré generace

	tryVectors = createTryVectors(mutationVectors);

	for (i = 0; i < COUNT_INDIVIDUALS; i++)
	{
		oldIndividual = individuals[i];
		tryParams = tryVectors[i];

		/* vypoèítá fitness fci zkušebního jedince */
		fit->setMeasuredVals(oldIndividual->getMeasuredVals(), oldIndividual->getCountMeasuredVal());
		tryFitness = fit->getMedian(tryParams);

		/* pokud je lepší než staršího jedince, uloží ji */
		if (tryFitness < oldIndividual->getFitness()) {
			oldIndividual->setFitness(tryFitness);
			oldIndividual->setParams(tryParams);
		}

		delete tryParams;
	}

	delete fit;
}

/* vytvoøí zkuèební vektory */
Params ** Evolution::createTryVectors(Params ** mutationVectors) {
	int i;
	Params * tryParams; //parametry zkušebního jedince
	Params ** tryVectors; //parametry zkušebních jedincù
	Params * mutationParams, *oldParams; //mutaèní vektor
	Individual * oldIndividual; //jedinec ze staré generace

	tryVectors = new Params *[COUNT_INDIVIDUALS];
	for (i = 0; i < COUNT_INDIVIDUALS; i++)
	{
		oldIndividual = individuals[i];
		tryParams = new Params; 
		oldParams = oldIndividual->getParams();

		mutationParams = mutationVectors[i];

		/* parametry p, cg, c */
		tryParams->p = createTryParam(oldParams->p, mutationParams->p, i + 1);
		tryParams->cg = createTryParam(oldParams->cg, mutationParams->cg, i + 2);
		tryParams->c = createTryParam(oldParams->c, mutationParams->c, i + 3);

		/* parametry pp, cgp, cp */
		tryParams->pp = createTryParam(oldParams->pp, mutationParams->pp, i + 4);
		tryParams->cgp = createTryParam(oldParams->cgp, mutationParams->cgp, i + 5);
		tryParams->cp = createTryParam(oldParams->cp, mutationParams->cp, i + 6);

		/* parametry dt, h */
		tryParams->dt = createTryParam(oldParams->dt, mutationParams->dt, i + 7);
		tryParams->h = createTryParam(oldParams->h, mutationParams->h, i + 8);
		/* paramerty k, m, n */
		tryParams->k = createTryParam(oldParams->k, mutationParams->k, i + 9);
		tryParams->m = createTryParam(oldParams->m, mutationParams->m, i + 10);
		tryParams->n = createTryParam(oldParams->n, mutationParams->n, i + 11);

		tryVectors[i] = tryParams;
	}

	return tryVectors;
}

double Evolution::createTryParam(double oldParam, double mutationParam, int i) {
	if (CR > r->generate(0, 1, i)) {
		return mutationParam;
	}
	else {
		return oldParam;
	}
}

/* vytvoøí mutaèní vektory */
Params ** Evolution::createMutationVectors()
{
	int i, r1, r2, r3;
	Individual * i1, * i2, * i3;
	Params *mutationParams, *p1, *p2, *p3;
	Params ** mutationVectors;
	

	mutationVectors = new Params*[COUNT_INDIVIDUALS];
	for (i = 0; i < COUNT_INDIVIDUALS; i++)
	{
		r1 = r->generateInt(0, COUNT_INDIVIDUALS - 1, i + 1);
		r2 = r->generateInt(0, COUNT_INDIVIDUALS - 1, i + 2);
		r3 = r->generateInt(0, COUNT_INDIVIDUALS - 1, i + 3);

		i1 = individuals[r1];
		i2 = individuals[r2];
		i3 = individuals[r3];

		p1 = i1->getParams();
		p2 = i2->getParams();
		p3 = i3->getParams();

		mutationParams = createMutationParams(p1, p2, p3, i);
		mutationVectors[i] = mutationParams;
	}

	return mutationVectors;

}

/* vytvoøí nový mutaèní vektor */
Params * Evolution::createMutationParams(Params * p1, Params *p2, Params *p3, int i) {
	Params * mutationParams = new Params();

	mutationParams->p = getMutationParam(p1->p, p2->p, p3->p, bounds->pmin, bounds->pmax, i + 1);
	mutationParams->cg = getMutationParam(p1->cg, p2->cg, p3->cg, bounds->cgmin, bounds->cgmax, i + 2);
	mutationParams->c = getMutationParam(p1->c, p2->c, p3->c, bounds->cmin, bounds->cmax, i + 3);

	mutationParams->pp = getMutationParam(p1->pp, p2->pp, p3->pp, bounds->ppmin, bounds->ppmax, i + 4);
	mutationParams->cgp = getMutationParam(p1->cgp, p2->cgp, p3->cgp, bounds->cgpmin, bounds->cgpmax, i + 5);
	mutationParams->cp = getMutationParam(p1->cp, p2->cp, p3->cp, bounds->cpmin, bounds->cpmax, i + 6);

	mutationParams->dt = getMutationParam(p1->dt, p2->dt, p3->dt, bounds->dtmin, bounds->dtmax, i + 7);
	mutationParams->h = getMutationParam(p1->h, p2->h, p3->h, bounds->hmin, bounds->hmax, i + 8);

	mutationParams->k = getMutationParam(p1->k, p2->k, p3->k, bounds->kmin, bounds->kmax, i + 9);

	mutationParams->m = getMutationParam(p1->m, p2->m, p3->m, bounds->mmin, bounds->mmax, i + 10);
	mutationParams->n = getMutationParam(p1->n, p2->n, p3->n, bounds->nmin, bounds->nmax, i + 11);

	return mutationParams;
}

/* vypoèítá jeden mutaèní parametr */
double Evolution::getMutationParam(double p1, double p2, double p3, double min, double max, int i) {
	double param;
	
	param = p1 + F * (p2 - p3);

	/* pokud se dostane za meze */
	if (param > max || param < min) {
		param = r->generate(min, max, i);
	}

	return param;
}

/* vytvoøí novou evoluci */
void Evolution::createNew()
{
	Params ** mutationVectors = createMutationVectors();
	calVectors(mutationVectors);
	delete mutationVectors;
}

/* zaènì nevou evoluci a vrátí nejlepší fitness fci */
double Evolution::startNew(int i)
{
	double bestFit;
	
	r->setSeed(i);
	createNew();
	bestFit = calBestFit();
	return bestFit;
}

/* Vrátí nejlepšího jedince z této evoluce */
Individual * Evolution::getBestIndividual() {
	return bestIndividual;
}

/* vytvoøí jedince kterým se vygenerují poèáteèní parametry a pøiøadí se jim namìøené hodnoty */
void Evolution::createFirstGen(int countMeasuredVals, MeasuredVal ** MeasuredVals)
{
	Individual * ind;
	Fitness * fit;
	int i;
	double fitness;

	/* vytvoøí jedince a pøiøadí jim namìøené hodnoty */
	individuals = new Individual*[COUNT_INDIVIDUALS];
	fit = new Fitness;
	for (i = 0; i < COUNT_INDIVIDUALS; i++)
	{
		ind = new Individual(countMeasuredVals, MeasuredVals, bounds);
		fit->setMeasuredVals(MeasuredVals, countMeasuredVals);
		fitness = fit->getMedian(ind->getParams());
		ind->setFitness(fitness);

		individuals[i] = ind;
	}
	delete fit;
}

/* Vrátí výsledek fitnes fce nejlepšího jedince */
double Evolution::calBestFit()
{
	int i;
	double fitness;
	double bestFitness = individuals[0]->getFitness();
	bestIndividual = individuals[0];

	for (i = 0; i < COUNT_INDIVIDUALS; i++)
	{
		fitness = individuals[i]->getFitness();
		if (fitness < bestFitness) {
			bestFitness = fitness;
			bestIndividual = individuals[i];
		}
	}
	return bestFitness;
}

/* naète meze z init souboru */
void Evolution::loadBounds()
{
	CSimpleIniA ini;
	Bounds * b;

	b = new Bounds;
	ini.LoadFile("bounds.ini");

	
	b->pmin = atof(ini.GetValue(INI_SECTION_NAME, "pmin", "default"));
	b->pmax = atof(ini.GetValue(INI_SECTION_NAME, "pmax", "default"));
	b->cgmin = atof(ini.GetValue(INI_SECTION_NAME, "cgmin", "default"));
	b->cgmax = atof(ini.GetValue(INI_SECTION_NAME, "cgmax", "default"));
	b->cmin = atof(ini.GetValue(INI_SECTION_NAME, "cmin", "default"));
	b->cmax = atof(ini.GetValue(INI_SECTION_NAME, "cmax", "default"));

	b->ppmin = atof(ini.GetValue(INI_SECTION_NAME, "ppmin", "default"));
	b->ppmax = atof(ini.GetValue(INI_SECTION_NAME, "ppmax", "default"));
	b->cgpmin = atof(ini.GetValue(INI_SECTION_NAME, "cgpmin", "default"));
	b->cgpmax = atof(ini.GetValue(INI_SECTION_NAME, "cgpmax", "default"));
	b->cpmin = atof(ini.GetValue(INI_SECTION_NAME, "cpmin", "default"));
	b->cpmax = atof(ini.GetValue(INI_SECTION_NAME, "cpmax", "default"));

	b->dtmin = atof(ini.GetValue(INI_SECTION_NAME, "dtmin", "default"));
	b->dtmax = atof(ini.GetValue(INI_SECTION_NAME, "dtmax", "default"));
	b->hmin = atof(ini.GetValue(INI_SECTION_NAME, "hmin", "default"));
	b->hmax = atof(ini.GetValue(INI_SECTION_NAME, "hmax", "default"));

	b->kmin = atof(ini.GetValue(INI_SECTION_NAME, "kmin", "default"));
	b->kmax = atof(ini.GetValue(INI_SECTION_NAME, "kmax", "default"));

	b->mmin = atof(ini.GetValue(INI_SECTION_NAME, "mmin", "default"));
	b->mmax = atof(ini.GetValue(INI_SECTION_NAME, "mmax", "default"));
	b->nmin = atof(ini.GetValue(INI_SECTION_NAME, "nmin", "default"));
	b->nmax = atof(ini.GetValue(INI_SECTION_NAME, "nmax", "default"));

	bounds = b;
}
