#include "stdafx.h"
#include "RandomNumber.h"
#include "libs/mtrand/mtrand.h";


RandomNumber::RandomNumber(int lenght)
{
	unsigned long init[4] = { 0x123, 0x234, 0x345, 0x456 }, length = lenght;
	irand = new MTRand_int32(init, length);
}


RandomNumber::~RandomNumber()
{
	delete(irand);
}

int RandomNumber::generate(double min, double max)
{
	int randomNum = irand->operator()();
	return randomNum;
}
