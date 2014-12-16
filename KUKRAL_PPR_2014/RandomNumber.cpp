#include "stdafx.h"
#include "RandomNumber.h"
#include <random>
#include <time.h>

/**
* Tøída pro vygenerování náhodného èísla
*/

RandomNumber::RandomNumber()
{
}


RandomNumber::~RandomNumber()
{
}

/**
* Vygeneruje náhodnı int
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
* Vygeneruje náhodnı double
*/
double RandomNumber::generate(double min, double max, int seed)
{
	double randomNum;
	std::mt19937 generator(clock() + globalSeed + seed);
	std::uniform_real_distribution<double> dis(min, max);

	randomNum = dis(generator);

	return randomNum;
}

/* nastaví globální seed pro celou tøídu */
void RandomNumber::setSeed(int seed) {
	globalSeed = seed;
}
