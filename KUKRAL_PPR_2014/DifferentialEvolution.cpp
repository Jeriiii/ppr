#include "stdafx.h"
#include "DifferentialEvolution.h"
#include "Evolution.h"
#include "MeasuredCreator.h"
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
	int i, j;
	double bestFit, endFit = 0.01; //ukon�ovac� konstanta
	MeasuredCreator * mc;
	PatientMeasuredVals ** patients;
	PatientMeasuredVals * patient;

	evo = new Evolution();

	/* na�te nam��en� hodnoty z db a dopo��t� chyb�j�c� */
	mc = new MeasuredCreator();

	countPatients = mc->getCountPatients();
	patients = mc->getMeasuredVals();

	delete mc;

	/* postupn� spust� evoluci na v�echny jedince */
	for (j = 0; j < countPatients; j++) {
		patient = patients[j];
		evo->createFirstGen(patient->countMeasuredVals(), patient->getMeasuredVals());

		/* spu�t�n� evoluce na jednoho jedince */
		for (i = 0; true; i++) {
			bestFit = evo->startNew(i * 100);
			if (bestFit < endFit) {
				break;
			}
			if (i % 10 == 0) {
				printf("krok %d, bestFit %f \n", i / 10, bestFit);
			}
			i++;
		}

		delete patient;
	}

	std::cout << "bestfit is " << bestFit;

	/* nejlep�� jedinec */
	Individual * bestIndividual = evo->getBestIndividual();

	delete evo;
	return 0;
}
