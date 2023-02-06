#pragma once

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX(X, Y) (((X) < (Y)) ? (Y) : (X))  // maximum of two values
#define MIN(X, Y) (((X) > (Y)) ? (Y) : (X))  // minimum of two values

#define pi 3.14159265358979323846
#define h 1e-7
#define EPS 1e-10

#define N 2000
#define Ndrop 20000
#define muN 2000
#define Delta 1e-8
#define muStart 2.3022826
#define muEnd 2.3022836

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
#define f(x, mu) ((mu) * (x) * (1 - (x) * (x)))
#define df(x, mu) ((mu) * (1 - 2 * (x)))
#define EOInterval (3 * sqrt(3) / 2)
#define MuInit 2.35
#define MuFI 2

/* D */
//#define f(x, mu) ((mu) * cos(pi * (x)))
//#define df(x, mu) ((mu) * (1 - 2 * (x)))
//#define EOInterval 1
//#define MuInit 0.6
//#define MuFI 0.4

double* orbit(double x0, double mu);
double** orbits(double x0);
double fn(double x, double mu, int n);
double dfn(double x, double mu, int n);
double fn_x(double x, double mu, int n);
double fn_mu(double x, double mu, int n);
double fn_xx(double x, double mu, int n);
double fn_xmu(double x, double mu, int n);
double Fx_power2(double x, double mu, int n);
double Fy_power2(double x, double mu, int n);
double Fx(double x, double mu, int n);
double Fy(double x, double mu, int n);
double* newton(double F(double, double, int), double dF(double, double, int), double x0, double mu0, int n);

/* ROUTINES */

void OrbitsPlotGenerator();
void MuFinder();
void OddPeriodOrbits();