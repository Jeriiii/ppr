#pragma once
#include "Individual.h";

#define COUNT_INDIVIDUALS 40

class Evolution
{
public:
	Evolution();
	~Evolution();
private:
	void calVectors();
	void calMutationVectors();
	/**
	Vytvo�� prvn� evoluci
	*/
	int createFirstGen();
	Individual ** individuals;
	Individual ** mutationVectors;
public:
	double getBestFit();
	/** Probere v�echny jedince a vybere toho s nejlep�� fitnes fc� */
	double calBestFit();
	void createNew();
};

