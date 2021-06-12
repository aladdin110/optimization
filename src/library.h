
#ifndef OPTIMIZATION_LIBRARY_H
#define OPTIMIZATION_LIBRARY_H

#define LINDO_HEADER "/home/aladdin/Main/Programms/LAPI-LINUX-64x86-13.0/lindoapi/include/lindo.h"
#define LINDO_LICENSE "/home/aladdin/Main/Programms/LAPI-LINUX-64x86-13.0/lindoapi/license/lndapi130.lic"



#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include LINDO_HEADER



double preciser(double x);

//fonction objective
double J(double *rtilde, int *lambda);

#endif //OPTIMIZATION_LIBRARY_H
