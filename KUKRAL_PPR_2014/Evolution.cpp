#include "stdafx.h"
#include "Evolution.h"
#include "MeasuredCreator.h"
#include "libs/simpleini-master/SimpleIni.h"
#include "Fitness.h"
#include <iostream>

#include "RandomNumber.h"

Evolution::Evolution()
{
	r = new RandomNumber;
	bestIndividual = NULL;
	loadBounds();
	createFirstGen();
}


Evolution::~Evolution()
{
	int i;
	for (i = 0; i < countIndividuals; i++)
	{
		delete individuals[i];
	}
	delete individuals;
	delete r;
}

/* vytvo�� zku�ebn� jedince a vybere ty lep�� ze zku�ebn�ch a z min. generace */
void Evolution::calVectors(Params ** mutationVectors)
{
	int i;
	Params ** tryVectors; //parametry zku�ebn�ch jedinc�
	Params * tryParams; //parametry jednoho zku�en�ho jedince
	Fitness * fit = new Fitness();
	double tryFitness;
	Individual * oldIndividual; //jedinec ze star� generace

	tryVectors = createTryVectors(mutationVectors);

	for (i = 0; i < countIndividuals; i++)
	{
		oldIndividual = individuals[i];
		tryParams = tryVectors[i];
		fit = new Fitness();

		/* vypo��t� fitness fci zku�ebn�ho jedince */
		fit->setMeasuredVals(oldIndividual->getMeasuredVals(), oldIndividual->getCountMeasuredVal());
		tryFitness = fit->getMedian(tryParams);

		/* pokud je lep�� ne� star��ho jedince, ulo�� ji */
		if (tryFitness < oldIndividual->getFitness()) {
			oldIndividual->setFitness(tryFitness);
			oldIndividual->setParams(tryParams);
		}
		
	}

	delete fit;
}

/* vytvo�� zku�ebn� vektory */
Params ** Evolution::createTryVectors(Params ** mutationVectors) {
	int i;
	Params * tryParams; //parametry zku�ebn�ho jedince
	Params ** tryVectors; //parametry zku�ebn�ch jedinc�
	Params * mutationParams; //muta�n� vektor
	Individual * oldIndividual; //jedinec ze star� generace

	tryVectors = new Params *[countIndividuals];
	for (i = 0; i < countIndividuals; i++)
	{
		oldIndividual = individuals[i];
		tryParams = oldIndividual->getParams();
		mutationParams = mutationVectors[i];

		/* parametry p, cg, c */
		if (CR > r->generate(0, 1)) {
			tryParams->p = mutationParams->p;
		}

		if (CR > r->generate(0, 1)) {
			tryParams->cg = mutationParams->cg;
		}

		if (CR > r->generate(0, 1)) {
			tryParams->c = mutationParams->c;
		}

		/* parametry pp, cgp, cp */
		if (CR > r->generate(0, 1)) {
			tryParams->pp = mutationParams->pp;
		}

		if (CR > r->generate(0, 1)) {
			tryParams->cgp = mutationParams->cgp;
		}

		if (CR > r->generate(0, 1)) {
			tryParams->cp = mutationParams->cp;
		}

		/* parametry dt, h */
		if (CR > r->generate(0, 1)) {
			tryParams->dt = mutationParams->dt;
		}

		if (CR > r->generate(0, 1)) {
			tryParams->h = mutationParams->h;
		}
		/* paramerty k, m, n */
		if (CR > r->generate(0, 1)) {
			tryParams->k = mutationParams->k;
		}

		if (CR > r->generate(0, 1)) {
			tryParams->m = mutationParams->m;
		}

		if (CR > r->generate(0, 1)) {
			tryParams->n = mutationParams->n;
		}
		tryVectors[i] = tryParams;
	}

	return tryVectors;
}

/* vytvo�� muta�n� vektory */
Params ** Evolution::createMutationVectors()
{
	int i, r1, r2, r3;
	Individual * i1, * i2, * i3;
	Params *mutationParams, *p1, *p2, *p3;
	Params ** mutationVectors;
	

	mutationVectors = new Params*[countIndividuals];
	for (i = 0; i < countIndividuals; i++)
	{
		r1 = r->generateInt(0, countIndividuals - 1);
		r2 = r->generateInt(0, countIndividuals - 1);
		r3 = r->generateInt(0, countIndividuals - 1);

		i1 = individuals[r1];
		i2 = individuals[r2];
		i3 = individuals[r3];

		p1 = i1->getParams();
		p2 = i2->getParams();
		p3 = i3->getParams();

		mutationParams = createMutationParams(p1, p2, p3);
		mutationVectors[i] = mutationParams;
	}

	return mutationVectors;

}

/* vytvo�� nov� muta�n� vektor */
Params * Evolution::createMutationParams(Params * p1, Params *p2, Params *p3) {
	Params * mutationParams = new Params();

	mutationParams->p = getMutationParam(p1->p, p2->p, p3->p, bounds->pmin, bounds->pmax);
	mutationParams->cg = getMutationParam(p1->cg, p2->cg, p3->cg, bounds->cgmin, bounds->cgmax);
	mutationParams->c = getMutationParam(p1->c, p2->c, p3->c, bounds->cmin, bounds->cmax);

	mutationParams->pp = getMutationParam(p1->pp, p2->pp, p3->pp, bounds->ppmin, bounds->ppmax);
	mutationParams->cgp = getMutationParam(p1->cgp, p2->cgp, p3->cgp, bounds->cgpmin, bounds->cgpmax);
	mutationParams->cp = getMutationParam(p1->cp, p2->cp, p3->cp, bounds->cpmin, bounds->cpmax);

	mutationParams->dt = getMutationParam(p1->dt, p2->dt, p3->dt, bounds->dtmin, bounds->dtmax);
	mutationParams->h = getMutationParam(p1->h, p2->h, p3->h, bounds->hmin, bounds->hmax);

	mutationParams->k = getMutationParam(p1->k, p2->k, p3->k, bounds->kmin, bounds->kmax);

	mutationParams->m = getMutationParam(p1->m, p2->m, p3->m, bounds->mmin, bounds->mmax);
	mutationParams->n = getMutationParam(p1->n, p2->n, p3->n, bounds->nmin, bounds->nmax);

	return mutationParams;
}

/* vypo��t� jeden muta�n� parametr */
double Evolution::getMutationParam(double p1, double p2, double p3, double min, double max) {
	double param;
	
	param = p1 + F * (p2 - p3);

	/* pokud se dostane za meze */
	if (param > max || param < min) {
		param = r->generate(max, min);
	}

	return param;
}

/* vytvo�� novou evoluci */
void Evolution::createNew()
{
	Params ** mutationVectors = createMutationVectors();
	calVectors(mutationVectors);
	delete mutationVectors;
}

/* za�n� nevou evoluci a vr�t� nejlep�� fitness fci */
double Evolution::startNew()
{
	double bestFit;
	
	createNew();
	bestFit = calBestFit();
	return bestFit;
}

/* Vr�t� nejlep��ho jedince z t�to evoluce */
Individual * Evolution::getBestIndividual() {
	return bestIndividual;
}

/* vytvo�� jedince kter�m se vygeneruj� po��te�n� parametry a p�i�ad� se jim nam��en� hodnoty */
void Evolution::createFirstGen()
{
	Individual * ind;
	MeasuredCreator * mc;
	PatientMeasuredVals ** patients;
	PatientMeasuredVals * patient;
	Fitness * fit;
	int i;
	double fitness;

	/* na�te nam��en� hodnoty z db a dopo��t� chyb�j�c� */
	mc = new MeasuredCreator();

	countIndividuals = mc->getCountPatients();
	patients = mc->getMeasuredVals();

	delete mc;

	/* vytvo�� jedince a p�i�ad� jim nam��en� hodnoty */
	individuals = new Individual*[countIndividuals];
	fit = new Fitness;
	for (i = 0; i < countIndividuals; i++)
	{
		patient = patients[i];
		
		ind = new Individual(patient->countMeasuredVals(), patient->getMeasuredVals(), bounds);
		fit->setMeasuredVals(ind->getMeasuredVals(), ind->getCountMeasuredVal());
		fitness = fit->getMedian(ind->getParams());
		ind->setFitness(fitness);

		delete patient;
		individuals[i] = ind;
	}
	delete fit;
}

/* Vr�t� v�sledek fitnes fce nejlep��ho jedince */
double Evolution::calBestFit()
{
	int i;
	double fitness;
	double bestFitness = individuals[0]->getFitness();
	bestIndividual = individuals[0];

	for (i = 0; i < countIndividuals; i++)
	{
		fitness = individuals[i]->getFitness();
		if (fitness < bestFitness) {
			bestFitness = fitness;
			bestIndividual = individuals[i];
		}
	}
	return bestFitness;
}

/* na�te meze z init souboru */
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
