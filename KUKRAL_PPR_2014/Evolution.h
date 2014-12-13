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
	Vytvoøí první evoluci
	*/
	int createFirstGen();
	Individual ** individuals;
	Individual ** mutationVectors;
	Bounds * bounds;
public:
	double getBestFit();
	/** Probere všechny jedince a vybere toho s nejlepší fitnes fcí */
	double calBestFit();
	void createNew();
private:
	void loadBounds();
};

