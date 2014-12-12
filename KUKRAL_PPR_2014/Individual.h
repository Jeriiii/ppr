#pragma once
class Individual
{
public:
	Individual(int countMeasuredVal);
	~Individual();
	int cal();
private:
	int createParams();
	double * params;
public:
	void init();
	char *test;
private:
	/* nam��en� hodnota */
	struct MeasuredVal
	{
		double b; //krev
		double i; //ist
		double t; //�as
	};
	int countMeasuredVal;
	/* pole struktur nam��en�ch hodnot */
	MeasuredVal **measuredVals;
	
};

