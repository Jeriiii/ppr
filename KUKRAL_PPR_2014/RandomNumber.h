#pragma once
class RandomNumber
{
public:
	RandomNumber();
	~RandomNumber();
	int globalSeed = 0;
	double generate(double min, double max, int seed);
	int generateInt(int min, int max, int seed);
	void setSeed(int seed);
};

