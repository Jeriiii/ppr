#include "stdafx.h"
#include "Fitness.h"
#include <algorithm>


Fitness::Fitness(MeasuredVal ** MeasuredVals, int countMeasuredVals)
{
	Fitness::MeasuredVals = MeasuredVals;
	Fitness::countMeasuredVals = countMeasuredVals;

}


Fitness::~Fitness()
{
}

/* vytvo�� aproximaci pro ist v libovoln�m �ase */
void Fitness::calIstAproximation() {
	int i;
	MeasuredVal * MeasuredVal;
	dvector istVec, tVec;

	for (i = 0; i < countMeasuredVals; i++) {
		MeasuredVal = MeasuredVals[i];

		tVec.push_back(MeasuredVal->t);
		istVec.push_back(MeasuredVal->i);
	}

	/* vytvo�en� aprofimace */
	istAproximation.set_points(tVec, istVec);
}

/* vr�t� i v libovoln�m �ase d�ky aproximaci */
double Fitness::getIst(double t) {
	return istAproximation(t);
}

/* spo��t� fitness fce pro v�echny m��en� a vr�t� jejich medi�n */
int Fitness::getMedian(Params * params)
{
	int i;
	dvector fitness;
	double fitnessMedian;
	std::vector<double>::iterator begin, middle, end;

	for (i = 0; i < countMeasuredVals; i++) {
		fitness.push_back(getFitness(params, MeasuredVals[i]));
	}

	/* ur�en� medi�nu pomoc� selection algoritmu */
	begin = fitness.begin();
	end = fitness.end();
	middle = begin + (end - begin) / 2;

	std::nth_element(begin, middle, end);
	fitnessMedian = *middle;

	return fitnessMedian;
}

/* Vr�t� fitness fci jednoho m��en� */
int Fitness::getFitness(Params * p, MeasuredVal * MeasuredVal) {
	double i = MeasuredVal->i, t = MeasuredVal->t, b = MeasuredVal->b;
	double fn1, fn2, fn3, fn4, fn5r, fn5l;
	double fitness;

	fn1 = i - getIst(t - p->h) * p->h;
	fn2 = b * (b - i);
	fn3 = p->p * b + p->cg * fn2 + p->c;
	fn4 = fn1 * (p->pp * b + p->cgp * fn2 + p->cp);
	fn5r = fn3 - fn4;
	fn5l = p->m * getIst(t + p->dt + p->k * fn1) + p->n * getIst(t + p->dt);

	fitness = fn5r - fn5l;
	
	/* pokud je fitness fce z�porn�, ud�l� z n� kladnou */
	if (fitness < 0) {
		fitness = -fitness;
	}

	return fitness;
}
