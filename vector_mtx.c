// vector_mtx.c

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "vector_mtx.h"

//FROM PREVIOUS ASSIGNMENT
// vector memory alloc
double *vector_malloc(int nmax) 
{
    double *vec; 
    vec = (double*)malloc(sizeof(double)*nmax); // allocate memory
    // initialize 
    for (int i=0; i<nmax; i++)
    {
        vec[i] = 0.0;
    }
    return vec;
} //def

double **mtx_malloc(int mmax, int nmax) 
{
    double **mtx; //pointer to pointer
    mtx = (double**)malloc(sizeof(double*)*mmax); //allocate memory 
    for (int i=0; i<mmax; i++) //loop through rows of matrix
    {
        mtx[i] = (double*)malloc(sizeof(double)*nmax); //allocate memory for each row
    } 
    //initialize
    for(int i=0; i<mmax; i++)
    {
        for(int j=0; j<nmax; j++)
        {
            mtx[i][j] = 0.0;
        } // j-loop
    } // i-loop
    return mtx;
} //def

// matrix memory de-allocation
void mtx_free(double **mtx, int mmax) 
{
    for (int i=0; i<mmax; i++)
    {
        free(mtx[i]); //free rows
    }
    free(mtx); // free pointers to rows
} //def

// copy vector a to b
void Vector_Copy(double *a, double *b, int nmax) 
{
    for (int i=0; i<nmax; i++)
    {
        b[i] = a[i]; // 
    }
} //def

// like vect_malloc but with integers
int *int_vector_malloc(int nmax) 
{
    int *integer;
    integer = (int*)malloc(sizeof(int)*nmax);
    // initialize 
    for (int i=0; i<nmax; i++)
    {
        integer[i] = 0;
    }
    return integer;
} //def

void Vector_APlusScaledBtoA(double *a, double *b, double c, int nmax)
{
    for (int i = 0; i < nmax; ++i)
    {
        a[i] = a[i] +c*b[i];
    }
    return;
} // Vector_APlusScaledBtoA

void Vector_Clear(double *a, int nmax)
{
    for (int i = 0; i < nmax; ++i)
    {
        a[i] = 0;
    }
    return;
} // Vector_Clear

double Vector_Distance(double *a, double *b, int num_elems)
{
    double sum, dist, diff;
    sum = 0.; // initialize at 0
    for (int i = 0; i < num_elems; i++)
    {
        diff = a[i] - b[i];
        sum += pow(diff, 2); // sum over components
    }
    dist = pow(sum, 0.5);
    return dist;
} // Vector_Distance




