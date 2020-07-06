// Vector matrix header
#ifndef VECTOR_MTX_H
#define VECTOR_MTX_H


double *vector_malloc(int nmax);  //allocate memory to vector
double **mtx_malloc(int mmax, int nmax);  //allocate memory to matrix
void mtx_free(double **mtx, int mmax); //free up matrix
void Vector_Copy(double *a, double *b, int nmax); // copy a to b
int *int_vector_malloc(int nmax); // integer vector allocation
void Vector_APlusScaledBtoA(double *a, double *b, double c, int nmax); //a+b*c
void Vector_Clear(double *a, int nmax); // clears vector
double Vector_Distance(double *a, double *b, int num_elems); //get magnitude of difference

#endif 