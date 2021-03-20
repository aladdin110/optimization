//
// Created by aladdin on 3/20/21.
//

#ifndef OPTIMIZATION_LIBRARY_H
#define OPTIMIZATION_LIBRARY_H
#include <stdio.h>
/*--------data--------*/
double data[4][11] = {{0,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1},//betai
                       {0,4,4,4,4,4,4,4,4,4,4},//ki
                       {0,0.1,0.2,0.3,0.15,0.1,0.25,0.05,0.27,0.12,0.18},//pi
                       {0,0.8,0.6,0.7,0.9,0.85,0.65,0.75,0.95,0.85,0.92}};//ri
int n = 10;
int d = 1;
int cP = 1;
int cI = 2;

double andes = 0.95;//an**des
/*-------functions-----*/
void printdata(double data[4][10]);
double Ni(double data[4][10], int i, int d);
double Mi(double data[4][10], int i, double andes, int n);
int landai(int landai);//landai appartient a {0,1}

#endif //OPTIMIZATION_LIBRARY_H
