#pragma once

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define pi 3.14159265358979323846
#define h 1e-7
#define EPS 1e-10

#define N 100
#define Ndrop 20000
#define muN 4000
#define Delta 1e-8
#define muStart 0.94
#define muEnd 0.95

/* A */
//#define f(x, mu) ((mu) * (x) * (1 - (x)))
//#define df(x, mu) ((mu) * (1 - 2 * (x)))
//#define EOInterval 4
//#define MuInit 3.56
//#define MuFI 3

/* B */
//#define f(x, mu) ((mu) * (x) * (1 - (x)) / (1 + (x)))
//#define df(x, mu) ((mu) * (1 - 2 * (x)))
//#define EOInterval (3 + 2 * sqrt(2))
//#define MuInit 5.4
//#define MuFI 4

/* C */
//#define f(x, mu) ((mu) * (x) * (1 - (x) * (x)))
//#define df(x, mu) ((mu) * (1 - 2 * (x)))
//#define EOInterval (3 * sqrt(3) / 2)
//#define MuInit 2.35
//#define MuFI 2

/* D */
#define f(x, mu) ((mu) * cos(pi * (x)))
#define df(x, mu) ((mu) * (1 - 2 * (x)))
#define EOInterval 1
#define MuInit 0.66
#define MuFI 0.4

double* orbit(double x0, double mu);
double** orbits(double x0);
double fn(double x, double mu, int n);

/* ROUTINES */

void OrbitsPlotGenerator();
void MuFinder();
void OddPeriodOrbits();