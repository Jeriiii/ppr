#include "stdafx.h"
#include "Evolution.h"


Evolution::Evolution()
{
	createFirstGen();
}


Evolution::~Evolution()
{
	for (size_t i = 0; i < COUNT_INDIVIDUALS; i++)
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
	individuals = new Individual*[COUNT_INDIVIDUALS];
	for (size_t i = 0; i < COUNT_INDIVIDUALS; i++)
	{
		ind = new Individual(10);
		individuals[i] = ind;
	}

	individuals[32]->cal();

	return 0;
}


double Evolution::calBestFit()
{
	return 0.0000001;
}
