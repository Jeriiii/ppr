#pragma once
#include "libs/mtrand/mtrand.h";
class RandomNumber
{
public:
	RandomNumber(int lenght);
	~RandomNumber();
	/**
	* Vygeneruje n�hodn� integer
	* @return N�hodn� integer
	*/
	int generate(double min, double max);
public:
	MTRand_int32 *irand;
};

