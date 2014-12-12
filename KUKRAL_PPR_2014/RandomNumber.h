#pragma once
#include "libs/mtrand/mtrand.h";
class RandomNumber
{
public:
	RandomNumber(int lenght);
	~RandomNumber();
	/**
	* Vygeneruje náhodnı integer
	* @return Náhodnı integer
	*/
	int generate(double min, double max);
public:
	MTRand_int32 *irand;
};

