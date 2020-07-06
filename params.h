#ifndef PARAM_H
#define PARAM_H

// numerical value of pi
#define PI 3.1415926535897932385

// pointer to a vector function 
typedef double (*FuncPt)(double *q, double t, int num_elems);

typedef struct euler_params
{
	// initial values
	double *q_i;
	double t_i;
	double t_f;

	FuncPt *QVelos;

	// problem specific quantities

	double h;
	int num_eq;

	double prec_goal; // level of tolerance for error. dictates when evolution stops

	//  masses in kg
	double mass1;
	double mass2;

	//  lengths in m
	double length1;
	double length2;
} NeqParams;

NeqParams PARAM_DATA;
#endif