

#ifndef OPTIMIZATION_LIBRARY_H
#define OPTIMIZATION_LIBRARY_H
#include <stdio.h>
#include <stdlib.h>

double preciser(double x);

//fonction objective
double J(double *rtilde, int *lambda);

#endif //OPTIMIZATION_LIBRARY_H
