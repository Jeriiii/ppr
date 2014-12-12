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
	/* namìøená hodnota */
	struct MeasuredVal
	{
		double b; //krev
		double i; //ist
		double t; //èas
	};
	int countMeasuredVal;
	/* pole struktur namìøenıch hodnot */
	MeasuredVal **measuredVals;
	
};

