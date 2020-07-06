// evolve.c
#include <stdio.h> 
#include <stdlib.h> 
#include <math.h> 
#include "evolve.h" 
#include "forces.h" 
#include "params.h" 
#include "vector_mtx.h" 
#include "rk4.h" 

void EvolveNeq(double *q)
{
	double *q_next;
	double t_i, t_f, t_now, t_next, h;
	int num_eq;
	int count;
	double prec_goal, err;
	FuncPt *QVelos;
	FILE *output;

	t_i = PARAM_DATA.t_i;
	t_f = PARAM_DATA.t_f;


	if (t_f < t_i) 	// warn if t_i > t_f
	{
		fprintf(stderr, "Initial time larger than final time\n");
		exit(1); // exit
	}

	num_eq = PARAM_DATA.num_eq;
	prec_goal = PARAM_DATA.prec_goal;
	QVelos = PARAM_DATA.QVelos;

	q_next = vector_malloc(num_eq); // allocate space to q_next

	output = fopen("results.dat", "w"); // open file for writing

	t_now = t_i; // start time at initial time

	count = 0;

	// record steps until t_now = t_f
	do
	{
		RecordAStep(output, t_now, q, num_eq);
		h = PARAM_DATA.h;

		// AdaptiveRK4Step until meet precision goal (err > prec_goal)
		do
		{
			t_next = t_now + h;

			err = AdaptiveRK4Step(q, q_next, QVelos, t_now, &t_next, h, num_eq);

			count += 3; //move up count as much as AdaptiveRk4 moves it up

			h = EstimateNextH(err, prec_goal, h);

		} while (err > prec_goal);

		// set t_now to t_next since we have advanced an adaptive step
		t_now = t_next;

		Vector_Copy(q_next, q, num_eq); // copy q_next onto q

	} while (t_now <= t_f);

	RecordAStep(output, t_now, q, num_eq); 	// record final step

	fclose(output);

	printf("count: %d\n", count);

	return;
} // Evolve Neq

void RecordAStep(FILE *output, double t_now, double *q, int num_eq)
{
	fprintf(output, "%lf ", t_now);

	// record the angles and momenta
	double qs;
	for (int i = 0; i < num_eq; ++i)
	{
		if ((i == 0) || (i == 1)) 	// for q[0], q[1]: these are angles. get modulo 2pi
		{
			qs = GetAngle(q[i]);
		}
		else //for momentum, just equate
		{
			qs = q[i];
		}
		fprintf(output, "%lf ", qs);
	} // i-loop

	double l_1, l_2, theta_1, theta_2;
	double x_1, y_1, x_2, y_2;

	l_1 = PARAM_DATA.length1;
	l_2 = PARAM_DATA.length2;
	theta_1 = GetAngle(q[0]);
	theta_2 = GetAngle(q[1]);

	// position of mass 1
	x_1 = l_1*sin(theta_1);
	y_1 = -l_1*cos(theta_1);
	fprintf(output, "%lf ", x_1);
	fprintf(output, "%lf ", y_1);

	// position of mass 2
	x_2 = x_1 + l_2*sin(theta_2);
	y_2 = y_1 - l_2*cos(theta_2);
	fprintf(output, "%lf ", x_2);
	fprintf(output, "%lf ", y_2);

	// get total energy
	double energy;

	energy = TotalEnergy(q);

	// record energy
	fprintf(output, "%lf\n", energy);

	return;
} // RecordAStep

double GetAngle(double angle)
{
	double f,n;

	f = angle;
	n = floor(f/(2.0*PI));

	f -= 2.0*PI*n;

	return f;
} // GetAngle