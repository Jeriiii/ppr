#include "stdafx.h"
#include "DifferentialEvolution.h"
#include "Evolution.h"


DifferentialEvolution::DifferentialEvolution()
{
}


DifferentialEvolution::~DifferentialEvolution()
{
}


int DifferentialEvolution::start()
{
	Evolution * evo;
	double bestFit = 0.0;
	double endParam = 0.001; //ukonèovací konstanta
	evo = new Evolution();

	//while(true) {

	//	evo->createNew();
	//	bestFit = evo->getBestFit();
	//	if (bestFit < endParam) {
	//		break;
	//	}

	//}

	delete evo;
	return 0;
}
