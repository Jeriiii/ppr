#pragma once
#include <random>

class RandomNumber
{
public:
	RandomNumber();
	~RandomNumber();
	int globalSeed = 0;
	std::mt19937 generator;
	double generate(double min, double max);
	int generateInt(int min, int max);
	void setSeed(int seed);
};

