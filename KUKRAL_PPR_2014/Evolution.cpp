#include "stdafx.h"
#include "Evolution.h"
#include "MeasuredCreator.h"
#include "libs/simpleini-master/SimpleIni.h"
#include <iostream>

#include "RandomNumber.h"

Evolution::Evolution()
{
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
}


void Evolution::calVectors()
{

}


void Evolution::calMutationVectors()
{

}

void Evolution::createNew()
{
	calMutationVectors();
	calVectors();
}

/* zaènì nevou evoluci a vrátí nejlepší fitness fci */
double Evolution::startNew()
{
	double bestFit;
	
	bestFit = calBestFit();
	return bestFit;
}

/* Vrátí nejlepšího jedince z této evoluce */
Individual * Evolution::getBestIndividual() {
	return bestIndividual;
}

/* vytvoøí jedince kterým se vygenerují poèáteèní parametry a pøiøadí se jim namìøené hodnoty */
int Evolution::createFirstGen()
{
	Individual * ind;
	MeasuredCreator * mc;
	PatientMeasuredVals ** patients;
	PatientMeasuredVals * patient;
	int i;

	/* naète namìøené hodnoty z db a dopoèítá chybìjící */
	mc = new MeasuredCreator();

	countIndividuals = mc->getCountPatients();
	patients = mc->getMeasuredVals();

	delete mc;

	/* vytvoøí jedince a pøiøadí jim namìøené hodnoty */
	individuals = new Individual*[countIndividuals];
	for (i = 0; i < countIndividuals; i++)
	{
		patient = patients[i];
		ind = new Individual(patient->countMeasuredVals(), patient->getMeasuredVals(), bounds);
		delete patient;
		individuals[i] = ind;
	}

	return 0;
}

/* Vrátí výsledek fitnes fce nejlepšího jedince */
double Evolution::calBestFit()
{
	return 0.0000001;
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
