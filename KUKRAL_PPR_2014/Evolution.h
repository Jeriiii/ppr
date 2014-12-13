#pragma once

#include "Individual.h"
#include "Bounds.h"

#define INI_SECTION_NAME "Bounds"

class Evolution
{
public:
	Evolution();
	~Evolution();
private:
	void calVectors();
	void calMutationVectors();
	int countIndividuals;
	/**
	Vytvo�� prvn� evoluci
	*/
	int createFirstGen();
	Individual ** individuals;
	Individual ** mutationVectors;
	Bounds * bounds;
public:
	double getBestFit();
	/** Probere v�echny jedince a vybere toho s nejlep�� fitnes fc� */
	double calBestFit();
	void createNew();
private:
	void loadBounds();
};

