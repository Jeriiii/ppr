#include "stdafx.h"
#include "Fitness.h"
#include <algorithm>


Fitness::Fitness()
{
	Fitness::MeasuredVals = NULL;
	Fitness::countMeasuredVals = 0;

}


Fitness::~Fitness()
{
}

void Fitness::setMeasuredVals(MeasuredVal ** MeasuredVals, int countMeasuredVals) {
	Fitness::MeasuredVals = MeasuredVals;
	Fitness::countMeasuredVals = countMeasuredVals;
	calIstAproximation();
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

/* pr�m�rn� rozd�l lev�ch a prav�ch hodnot */
double Fitness::sumDiff(Params * params) {
	double sum = 0.0;
	double sum1 = 0.0, sum2 = 0.0, sum3 = 0.0, sum4 = 0.0;
	int i;
	
	for (i = 0; i < countMeasuredVals; i = i + 4) {
		sum1 = sum1 + getFitness(params, MeasuredVals[i]);
		sum2 = sum2 + getFitness(params, MeasuredVals[i]);
		sum3 = sum3 + getFitness(params, MeasuredVals[i]);
		sum4 = sum4 + getFitness(params, MeasuredVals[i]);
	}

	sum = sum1 + sum2 + sum3 + sum4;

	return sum / countMeasuredVals;
}

/* Vr�t� fitness fci jednoho m��en� */
double Fitness::getFitness(Params * p, MeasuredVal * MeasuredVal) {
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
