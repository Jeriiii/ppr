// KUKRAL_PPR_2014.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Database.h"
#include "RandomNumber.h"
#include "DifferentialEvolution.h"
#include <iostream>

static void dbTest(); //dekladace fce


int _tmain(int argc, _TCHAR* argv[])
{
	DifferentialEvolution * df;
	
	/*RandomNumber * r;
	r = new RandomNumber();
	r->generate();
	delete(r);*/

	df = new DifferentialEvolution();
	df->start();
	delete(df);

	printf("Pro ukonèení programu stisknìte libovolnou klávesu.");
	getchar();
	return 0;
}



