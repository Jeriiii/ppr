#include "stdafx.h"
#include "DifferentialEvolution.h"
#include "Evolution.h"
#include <iostream>

/************************************************************************/
/* T��da zaji��uj�c� kompletn� dif. evoluci                             */
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
	double endFit = 0.01; //ukon�ovac� konstanta
	evo = new Evolution();

	while(true) {
		bestFit = evo->startNew();
		if (bestFit < endFit) {
			break;
		}

	}

	std::cout << "bestfit is " << bestFit;

	/* nejlep�� jedinec */
	Individual * bestIndividual = evo->getBestIndividual();

	delete evo;
	return 0;
}
