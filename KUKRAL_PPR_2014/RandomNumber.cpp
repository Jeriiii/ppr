#include "stdafx.h"
#include "RandomNumber.h"
#include <random>
#include <time.h>

/**
* T��da pro vygenerov�n� n�hodn�ho ��sla
*/

RandomNumber::RandomNumber()
{
}


RandomNumber::~RandomNumber()
{
}

/**
* Vygeneruje n�hodn� int
*/
int RandomNumber::generateInt(int min, int max, int seed)
{
	int randomNum;
	std::mt19937 generator(clock() + globalSeed + seed);
	std::uniform_int_distribution<int> dis(min, max);

	randomNum = dis(generator);

	return randomNum;
}

/**
* Vygeneruje n�hodn� double
*/
double RandomNumber::generate(double min, double max, int seed)
{
	double randomNum;
	std::mt19937 generator(clock() + globalSeed + seed);
	std::uniform_real_distribution<double> dis(min, max);

	randomNum = dis(generator);

	return randomNum;
}

/* nastav� glob�ln� seed pro celou t��du */
void RandomNumber::setSeed(int seed) {
	globalSeed = seed;
}
