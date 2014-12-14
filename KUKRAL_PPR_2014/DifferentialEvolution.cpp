#include "stdafx.h"
#include "DifferentialEvolution.h"
#include "Evolution.h"
#include <iostream>

/************************************************************************/
/* Tøída zajišující kompletní dif. evoluci                             */
/************************************************************************/

DifferentialEvolution::DifferentialEvolution()
{
}


DifferentialEvolution::~DifferentialEvolution()
{
}


int DifferentialEvolution::start()
{
	Evolution * evo;
	double bestFit;
	double endFit = 0.01; //ukonèovací konstanta
	evo = new Evolution();

	while(true) {
		bestFit = evo->startNew();
		if (bestFit < endFit) {
			break;
		}

	}

	std::cout << "bestfit is " << bestFit;

	/* nejlepší jedinec */
	Individual * bestIndividual = evo->getBestIndividual();

	delete evo;
	return 0;
}
