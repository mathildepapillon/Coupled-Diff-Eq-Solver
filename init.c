// init.c
#include <stdio.h> 
#include <stdlib.h> 
#include <math.h> 
#include "params.h"  // PARAM_DATA
#include "init.h" 
#include "vector_mtx.h"
#include "forces.h"


void ReadInParams(char *input_file)
{
	double xd; // scanning doubles (variables)
	int xi; // scanning for integers
	int nidx; //to provide indexing
	double *q_i; // vector for q

	FILE *input; // pointer file

	input = fopen(input_file, "r"); // open file to read

	fscanf(input, "%d", &xi); //read in number of differential equations
	PARAM_DATA.num_eq = xi;

	nidx = PARAM_DATA.num_eq; // to provide indexing
	q_i = vector_malloc(nidx); 	// allocate memory for initial coordinates vector

	// q
	for (int i=0; i<nidx; i++)
	{
		fscanf(input, "%lf", &xd);
		q_i[i] = xd;
	}

	PARAM_DATA.q_i = q_i; // put q_i into PARAM_DATA

	fscanf(input, "%lf", &xd);
	PARAM_DATA.t_i = xd;

	fscanf(input, "%lf", &xd);
	PARAM_DATA.t_f = xd;

	fscanf(input, "%lf", &xd);
	PARAM_DATA.h = xd;

	fscanf(input, "%lf", &xd);
	PARAM_DATA.mass1 = xd;

	fscanf(input, "%lf", &xd);
	PARAM_DATA.length1 = xd;

	fscanf(input, "%lf", &xd);
	PARAM_DATA.mass2 = xd;

	fscanf(input, "%lf", &xd);
	PARAM_DATA.length2 = xd;

	fscanf(input, "%lf", &xd);
	PARAM_DATA.prec_goal = xd;	
	
	fclose(input);

	return;
} // ReadInParams

void PrintParams(void)
{
	int nidx = PARAM_DATA.num_eq; 
	FILE *output;
	output = fopen("params.dat", "w"); // open file to write 
	{
		fprintf(output, "Number of coord: %d\n", PARAM_DATA.num_eq);

		fprintf(output, "Theta 1: %lf\n", PARAM_DATA.q_i[0]);

		fprintf(output, "Theta 2: %lf\n", PARAM_DATA.q_i[1]);

		fprintf(output, "Momentum 1: %lf\n", PARAM_DATA.q_i[2]);

		fprintf(output, "Momentum 2: %lf\n", PARAM_DATA.q_i[3]);

		fprintf(output, "Initial time: %lf\n", PARAM_DATA.t_i);

		fprintf(output, "Final time: %lf\n", PARAM_DATA.t_f);

		fprintf(output, "Initial step: %lf\n", PARAM_DATA.h);

		fprintf(output, "Mass 1: %lf\n", PARAM_DATA.mass1);

		fprintf(output, "Mass 2: %lf\n", PARAM_DATA.mass2);

		fprintf(output, "Length 1: %lf\n", PARAM_DATA.length1);

		fprintf(output, "Length 2: %lf\n", PARAM_DATA.length2);

		fprintf(output, "Tolerance: %lf\n", PARAM_DATA.prec_goal);

	} 
	fclose(output);

	return;
} // PrintParams

void InitializeNeq(double *q)
{
	int nidx = PARAM_DATA.num_eq;

	for (int i=0; i<nidx; i++) // fill up q with initial data
	{
		q[i] = PARAM_DATA.q_i[i];
	} // i-loop

	PARAM_DATA.QVelos = (FuncPt *)malloc(sizeof(FuncPt)*nidx); 	// allocate memory to QVelos

	// in this problem, we have 4 generalized velocities
	PARAM_DATA.QVelos[0] = QVelo0;
	PARAM_DATA.QVelos[1] = QVelo1;
	PARAM_DATA.QVelos[2] = QVelo2;
	PARAM_DATA.QVelos[3] = QVelo3;

	return;
} // InitializeNeq






