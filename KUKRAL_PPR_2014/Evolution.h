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
	Vytvoøí první evoluci
	*/
	int createFirstGen();
	Individual ** individuals;
	Individual ** mutationVectors;
public:
	double getBestFit();
	/** Probere všechny jedince a vybere toho s nejlepší fitnes fcí */
	double calBestFit();
	void createNew();
};

