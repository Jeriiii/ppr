#pragma once
/* parametry */
struct Params
{
	double p;
	double cg;
	double c;

	/* nasledujici hodnoty jsou p s indexem fi */
	double pp;
	double cgp;
	double cp;

	double dt;
	double h;

	double k;

	double m;
	double n;
};