#include "Header.h"

double* orbit(double x0, double mu) {
    double* array = (double*)calloc(N + 1, sizeof(double));
    array[0] = mu;
    double last = x0;
    last = fn(last, mu, Ndrop);
    array[1] = last;
    for (int i = 2; i < N; i++) {
        last = f(last, mu);
        if (fabs(last - array[1]) < Delta) break;
        array[i] = last;
    }
    return array;
}

double** orbits(double x0) {
    double muStep = (muEnd - muStart) / (double)muN;

    double** matrix = (double**)calloc(muN + 1, sizeof(double*));

    for (int mu = 0; mu <= muN; mu++) matrix[mu] = orbit(x0, muStart + mu * muStep);
    
    return matrix;
}

double fn(double x, double mu, int n) {
    for (int i = 0; i < n; i++) x = f(x, mu);
    return x;
}

/* ROUTINES */

void OrbitsPlotGenerator() {
    
    char name[100] = "..\\DataFiles\\";
    scanf("%s", name + 13);

    double x0 = 0.7;
    double** data = orbits(x0);
    
    FILE* fp = fopen(name, "w");
    if (!fp) return;
    for (int i = 0; i < muN; i++) {
        for (int j = 1; j < N; j++) {
            if (!data[i][j])break;
            fprintf(fp, "%.15f %.15f\n", data[i][0], data[i][j]);
        }

    }
    fclose(fp);
}

void MuFinder() {
    const int k_MAX = 12, Iteracions = 200000, StepExp = 7;
    const double delta = 0.00000025, step = 0.0001, Presition=1e-10;
    double mu0 = MuFI, mu[k_MAX], lambda[k_MAX];
    for (int k = 0; k < k_MAX; k++) {

        double s = fn(0.7, mu0, Iteracions);
        while (fabs(s - fn(s, mu0, (int)pow(2, k))) < delta && mu0 < EOInterval) {
            if (k < 5)mu0 += step;
            else mu0 += 0.1 * pow(StepExp, -k);
            s = fn(s, mu0, Iteracions);
        }
        double xi;
        if (k < 5)xi = mu0 - step;
        else xi = mu0 - 0.1 * pow(StepExp, -k);
        double xf = mu0;
        while (fabs(xf - xi) > Presition) {
            double x = (xi + xf) / 2;
            s = fn(s, x, Iteracions);
            if (fabs(fn(s, x, (int)pow(2, k)) - s) > delta) xf = x;
            else xi = x;
        }

        mu[k] = xi;
        if (k > 1) lambda[k] = (mu[k - 1] - mu[k - 2]) / (mu[k] - mu[k - 1]);
        else lambda[k] = NAN;

        printf("%c_%i = %.10f\t%c_%i = %.10f\n", 230, k + 1, mu[k], 231, k + 1, lambda[k]);
    }
}

void OddPeriodOrbits() {
    const int MaxPer = 11, Iteracions = 10000;
    const double Step = 0.000001, Presition = 1e-10;
    int i = MaxPer;
    double mu = MuInit;
    while (i >= 3) {
        double s = 0.7;
        while (mu < EOInterval && fabs(s - fn(s, mu, i)) > EPS) {
            mu += Step;
            s = fn(s, mu, Iteracions);
        }
        double xi = mu - Step;
        double xf = mu;
        while (fabs(xf - xi) > Presition) {
            double x = (xi + xf) / 2;
            double s = fn(0.7, x, Iteracions);
            if (fabs(fn(s, x, i) - s) < Delta) xf = x;
            else xi = x;
        }
        printf("PERIODE %i: %c = %.10f\n", i, 230, xi);
        i -= 2;
    }
}
