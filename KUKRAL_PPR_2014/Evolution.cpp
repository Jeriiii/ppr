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
	for (size_t i = 0; i < countIndividuals; i++)
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

double Evolution::getBestFit()
{
	double bestFit;
	
	bestFit = calBestFit();
	return bestFit;
}


int Evolution::createFirstGen()
{
	Individual * ind;
	MeasuredCreator * mc;
	PatientMeasuredVals ** patients;
	PatientMeasuredVals * patient;

	mc = new MeasuredCreator();

	countIndividuals = mc->getCountPatients();
	patients = mc->getMeasuredVals();

	delete mc;

	individuals = new Individual*[countIndividuals];
	for (size_t i = 0; i < countIndividuals; i++)
	{
		patient = patients[i];
		ind = new Individual(patient->countMeasuredVals(), patient->getMeasuredVals());
		delete patient;
		individuals[i] = ind;
	}

	individuals[32]->cal();

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
