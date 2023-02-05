#pragma once

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define pi 3.14159265358979

#define N 200
#define Ndrop 20000
#define muN 2000
#define Delta 0.00000001
#define muStart 0
#define muEnd 1

#define f(x, mu) ((mu) * cos(pi * (x)))
//#define df(x, mu) ((mu) * (1 - 2 * (x)))

double* orbit(double x0, double mu);
double** orbits(double x0);

/* ROUTINES */

void OrbitsPlotGenerator();