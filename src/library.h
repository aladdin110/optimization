
#ifndef OPTIMIZATION_LIBRARY_H
#define OPTIMIZATION_LIBRARY_H

#define LINDO_HEADER "/home/aladdin/Main/Programms/LAPI-LINUX-64x86-13.0/lindoapi/include/lindo.h"
#define LINDO_LICENSE "/home/aladdin/Main/Programms/LAPI-LINUX-64x86-13.0/lindoapi/license/lndapi130.lic"
#define m 2


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include LINDO_HEADER

double N(int i);
double M(int i);
double a(double M[10], double N[10], int i);
double b(double N[10], int i);
double c(double M[10], double N[10], int i);
double e(double M[10], int i);
double borneInf_10(double a[10], double b[10], int i);
double borneSup_10(double c[10], double e[10], int i);


double preciser(double x);

//fonction objective
double J(double *rtilde, int *lambda);

#endif //OPTIMIZATION_LIBRARY_H
