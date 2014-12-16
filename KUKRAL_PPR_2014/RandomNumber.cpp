#include "stdafx.h"
#include "RandomNumber.h"
#include <time.h>

/**
* Tøída pro vygenerování náhodného èísla
*/

RandomNumber::RandomNumber()
{
	setSeed(clock());
}

RandomNumber::~RandomNumber()
{
}

/**
* Vygeneruje náhodnı int
*/
int RandomNumber::generateInt(int min, int max)
{
	int randomNum;

	std::uniform_int_distribution<int> dis(min, max);

	randomNum = dis(generator);

	return randomNum;
}

/**
* Vygeneruje náhodnı double
*/
double RandomNumber::generate(double min, double max)
{
	double randomNum;

	std::uniform_real_distribution<double> dis(min, max);

	randomNum = dis(generator);

	return randomNum;
}

/* nastaví globální seed pro celou tøídu */
void RandomNumber::setSeed(int seed) {
	std::mt19937 generator(seed);
	RandomNumber::generator = generator;
}
