// forces.c
#include <stdio.h> 
#include <stdlib.h> 
#include <math.h> 
#include "params.h" 
#include "forces.h"

//Problem-specific

// q[0] = theta_1
// q[1] = theta_2
// q[2] = p_1
// q[3] = p_2

// d theta_1 /dt, 1rst equation for double pendulum
double QVelo0(double *q, double t, int num_elems)
{
	double f;
	double theta_1, theta_2, p_1, p_2, l_1, l_2, m_1, m_2;
	double cos12, Mtot;

	Translate(q, &theta_1, &theta_2, &p_1, &p_2, &m_1, &m_2, &l_1, &l_2); //get readables

	cos12 = cos(theta_1 - theta_2);
	Mtot = m_1 + m_2;

	// get dtheta1/dt
	f = l_2*p_1 - l_1*p_2*cos12;
	f /= l_1*l_1*l_2*(Mtot - m_2*cos12*cos12);

	return f;

} //QVelo0

// d theta_2 /dt
double QVelo1(double *q, double t, int num_elems)
{
	double f;
	double theta_1, theta_2, p_1, p_2, l_1, l_2, m_1, m_2;
	double cos12, Mtot;

	Translate(q, &theta_1, &theta_2, &p_1, &p_2, &m_1, &m_2, &l_1, &l_2); 	// get readables

	cos12 = cos(theta_1 - theta_2);
	Mtot = m_1 + m_2;

	// get dtheta1/dt
	f = l_1*Mtot*p_2 - l_2*m_2*p_1*cos12;
	f /= l_1*l_2*l_2*m_2*(Mtot - m_2*cos12*cos12);

	return f;

} //QVelo1

// d p_1 /dt
double QVelo2(double *q, double t, int num_elems)
{
	double f;
	double theta_1, theta_2, p_1, p_2, l_1, l_2, m_1, m_2;
	double cos12, sin12, Mtot;
	double f_1, f_2, f_3; //3 terms in sum
	double g = 9.8; //gravitational acceleration

	Translate(q, &theta_1, &theta_2, &p_1, &p_2, &m_1, &m_2, &l_1, &l_2); // get readables

	cos12 = cos(theta_1 - theta_2);
	sin12 = sin(theta_1 - theta_2);
	Mtot = m_1 + m_2;

	// implement
	f_1 = p_1*p_2*sin12;
	f_1 /= l_1*l_2*(Mtot - m_2*cos12*cos12);
	
	f_2 = (l_2/l_1)*p_1*p_1 + (l_1/l_2)*(Mtot/m_2)*p_2*p_2 -2*p_1*p_2*cos12;
	f_2 /= l_2*l_1*pow((Mtot - m_2*cos12*cos12),2);
	f_2 *= m_2*cos12*sin12;

	f_3 = Mtot*g*l_1*sin(theta_1);

	f = -1.*f_1 + f_2 - f_3;

	return f;

} //QVelo2

// d p_2 /dt
double QVelo3(double *q, double t, int num_elems)
{
	// declare variables
	double f;
	double theta_1, theta_2, p_1, p_2, l_1, l_2, m_1, m_2;
	double cos12, sin12, Mtot;
	double f_1, f_2, f_3; //3 terms in sum
	double g = 9.8;

	Translate(q, &theta_1, &theta_2, &p_1, &p_2, &m_1, &m_2, &l_1, &l_2); // translate into readables

	cos12 = cos(theta_1 - theta_2);
	Mtot = m_1 + m_2;

	// get terms in sum
	f_1 = p_1*p_2*sin12;
	f_1 /= l_1*l_2*(Mtot - m_2*cos12*cos12);
	
	f_2 = (l_2/l_1)*p_1*p_1 + (l_1/l_2)*(Mtot/m_2)*p_2*p_2 - 2*p_1*p_2*cos12;
	f_2 /= l_2*l_1*pow((Mtot - m_2*cos12*cos12),2);
	f_2 *= m_2*cos12*sin12;

	f_3 = m_2*g*l_2*sin(theta_2);

	f = f_1 - f_2 - f_3;

	return f;

} //QVelo3

void Translate(double *q, double *theta_1, double *theta_2, 
	double *p_1, double *p_2, double *m_1, double *m_2, 
	double *l_1, double *l_2)
{
	*theta_1 = q[0];
	*theta_2 = q[1];
	*p_1 = q[2];
	*p_2 = q[3];

	*m_1 = PARAM_DATA.mass1;
	*m_2 = PARAM_DATA.mass2;
	*l_1 = PARAM_DATA.length1;
	*l_2 = PARAM_DATA.length2;

	return;
} // Translate

double TotalEnergy(double *q)
{
	// declare variables
	double g = 9.8;
	double H;
	double theta_1, theta_2, p_1, p_2, l_1, l_2, m_1, m_2;
	double cos12, Mtot;
	double f_1, f_2, f_3;

	Translate(q, &theta_1, &theta_2, &p_1, &p_2, &m_1, &m_2, &l_1, &l_2); 	// translate into readables

	cos12 = cos(theta_1 - theta_2);
	Mtot = m_1 + m_2;

	// compute terms
	f_1 = (l_2/l_1)*p_1*p_1 + (l_1/l_2)*(Mtot/m_2)*p_2*p_2 - 2*p_1*p_2*cos12;
	f_1 /= 2*l_2*l_1*(Mtot - m_2*cos12*cos12);

	f_2 = Mtot*g*l_1*cos(theta_1);

	f_3 = m_2*g*l_2*cos(theta_2);

	H = f_1 - f_2 - f_3;

	return H;
} // TotalEnergy
















