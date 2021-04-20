//
// Created by aladdin on 3/20/21.
//

#ifndef OPTIMIZATION_LIBRARY_H
#define OPTIMIZATION_LIBRARY_H
#include <stdio.h>
#include <stdlib.h>
/*--------data--------*/

/*
//vecteur N
double *N();

//vecteur M
double *M();

//vecteur a
double *a(double M[10], double N [10]);

//vecteur b
double *b(double M[10], double N [10]);

//vecteur c
double *c(double M[10], double N [10]);

//vecteur e
double *e(double M[10], double N [10]);

//borne inferieur de ri~ definie dans (10)
double borneInf_10(double a[10], double b[10], int i);

//borne superieur de ri~ definie dans (10)
double borneSup_10(double c[10], double e[10], int i);

//vecteur p~
double *ptilde(double rtilde[10],double a[10]);

//vecteur q
double *q(int lambda[10]);

//vecteur d~
double *dtilde(double q[10], int lambda[10]);

//borne inferieur de ri~ definie dans (7)
double borneInf_7(double a[10], double rtilde[10], double b[10], int i);

//borne superieur de ri~ definie dans (7)
double borneSup_7(double a[10], double rtilde[10], double b[10], int i);
*/


//fonction objective
double J(double *rtilde, int *lambda);

#endif //OPTIMIZATION_LIBRARY_H
