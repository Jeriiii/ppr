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
* Vygeneruje náhodnı double
*/
double RandomNumber::generate(double min, double max)
{
	double randomNum;
	std::mt19937 generator(clock());
	std::uniform_real_distribution<double> dis(min, max);

	randomNum = dis(generator);

	return randomNum;
}
