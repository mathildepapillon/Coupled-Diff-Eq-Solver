// rk4.c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "forces.h"
#include "params.h"
#include "vector_mtx.h"
#include "rk4.h"

void RK4Step(double *q, double *q_next, FuncPt *QVelos, double t_now, 
	double h, int num_eq)
{
	double t_half, t_next;
	static int ind = 0; 			// static variables 
	static double *q_local, *q_sum; 

	ind++;

	if (ind == 1) // first time fctn is called: allocate memory
	{
		q_local = vector_malloc(num_eq);
		q_sum = vector_malloc(num_eq);
	}

	t_half = t_now + h/2;
	t_next = t_now + h;

	// initialize 
	Vector_Clear(q_sum, num_eq);

	// RK first step
	OneStepNeq(q, q, q_local, QVelos, t_now, 0.5*h, num_eq);
	Vector_APlusScaledBtoA(q_sum, q_local, 1.0/3.0, num_eq);

	// RK second step
	OneStepNeq(q, q_local, q_next, QVelos, t_half, 0.5*h, num_eq);
	Vector_APlusScaledBtoA(q_sum, q_next, 2.0/3.0, num_eq);

	// RK third step
	OneStepNeq(q, q_next, q_local, QVelos, t_half, h, num_eq);
	Vector_APlusScaledBtoA(q_sum, q_local, 1.0/3.0, num_eq);

	// RK fourth step
	OneStepNeq(q, q_local, q_next, QVelos, t_next, h, num_eq);
	Vector_APlusScaledBtoA(q_sum, q_next, 1.0/6.0, num_eq);

	// add -1/2 of q to q_sum
	Vector_APlusScaledBtoA(q_sum, q, -1.0/2.0, num_eq);

	// copy q_sum to q_next
	Vector_Copy(q_sum, q_next, num_eq);

	return;
} // RK4 step

void OneStepNeq(double *q_now, double *q_in, double *q_next, FuncPt *QVelos, 
	double t_in, double h, int num_eq)
{
	int i; 

	// get q_next
	for (i=0; i<num_eq; i++)
	{
		q_next[i] = q_now[i] + h*(*QVelos[i])(q_in, t_in, num_eq);
	}

	return;
} // OneStepNeq

double AdaptiveRK4Step(double *q, double *q_next, FuncPt *QVelos, double t_now,
	double *t_next, double h, int num_eq)
{
	double *q_full_1, *q_half;
	double err;
	double halfh = h/2.;
	double t_loc = t_now + halfh;

	q_full_1 = vector_malloc(num_eq);
	q_half = vector_malloc(num_eq);

	//  full step
	RK4Step(q, q_full_1, QVelos, t_now, h, num_eq);

	//  two half steps
	RK4Step(q, q_half, QVelos, t_now, halfh, num_eq);
	RK4Step(q_half, q_next, QVelos, t_loc, halfh, num_eq);

	//  error estimate
	err = EstimateError(q_full_1, q_next, t_now, h, num_eq);

	*t_next = t_now + h; //evolve time

	// free memory 
	free(q_full_1);
	free(q_half);

	return err;
} // AdaptiveRK4Step

double EstimateError(double *q_full, double *q_next, double t_now, 
	double h, int num_eq)
{
	double err;

	err = Vector_Distance(q_full, q_next, num_eq);
	err /= 15;

	return err;
} // EstimateError

double EstimateNextH(double err, double err0, double h)
{
	// get next h based off of previous error
	double factor = 0.5;

	// declare variables
	double new_h;
	new_h = h*pow((factor*err0/err),0.2);

	return new_h;
} // EstimateNextH

























