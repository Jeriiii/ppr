// KUKRAL_PPR_2014.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "RandomNumber.h"
#include "DifferentialEvolution.h"
#include <iostream>

static void dbTest(); //dekladace fce


int _tmain(int argc, _TCHAR* argv[])
{
	DifferentialEvolution * df;

	df = new DifferentialEvolution();
	df->start();
	delete(df);

	std::cout << "Pro ukon�en� programu stiskn�te libovolnou kl�vesu.";
	getchar();
	return 0;
}



