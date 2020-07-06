// main.c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "vector_mtx.h"
#include "params.h" // parameter definitions
#include "init.h" // initialization 
#include "evolve.h" // time evolution with RK4
#include "rk4.h"
#include "forces.h"

// problem: double pendulum 
//  variables are theta_1, theta_2, p_1, and p_2

int main(int argc, char **argv)
{
	char *input_file; // input file name
	double *q;
	double t_i, t_f;

	input_file = argv[1];

	ReadInParams(input_file); //read in
	PrintParams(); //write onto

	q = vector_malloc(PARAM_DATA.num_eq); //velocity vector

	InitializeNeq(q); //start with initial data
	
	EvolveNeq(q); // evolve q

	return 0;
} // main