#include "Header.h"

double* orbit(double x0, double mu) {
    double* array = (double*)calloc(N + 1, sizeof(double));
    array[0] = mu;
    double last = x0;
    for (int i = 0; i < Ndrop; i++) last = f(last, mu);
    double first = last;
    array[1] = first;
    for (int i = 2; i < N; i++) {
        last = f(last, mu);
        if (fabs(last - first) < Delta) break;
        array[i] = last;
    }
    return array;
}

double** orbits(double x0) {
    // double muStart = 2.9;
    // double muEnd = 3.99;
    double muStep = (muEnd - muStart) / (double)muN;

    double** matrix = (double**)calloc(muN + 1, sizeof(double*));

    for (int mu = 0; mu <= muN; mu++) {
        matrix[mu] = orbit(x0, muStart + mu * muStep);
    }
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
    const int k_MAX = 12, Iteracions = 10000, StepExp = 7;
    const double delta = 0.0000005, step = 0.0001;
    double mu0 = MuFI, mu[k_MAX], lambda[k_MAX];
    for (int k = 0; k < k_MAX; k++) {

        double s = fn(0.7, mu0, Iteracions);
        while (fabs(s - fn(s, mu0, (int)pow(2, k))) < delta && mu0 < EOInterval) {
            if (k < 5)mu0 += step;
            else mu0 += 0.1 * pow(StepExp, -k);
            s = fn(s, mu0, Iteracions);
        }
        if (k < 5)mu0 += step;
        else mu0 += 0.1 * pow(StepExp, -k);
        s = fn(s, mu0, Iteracions);
        int k0 = k;
        if (k0 < 5)k0 = 5;
        while (k0 <= k_MAX) {
            while (fabs(s - fn(s, mu0, (int)pow(2, k))) < delta && mu0 < EOInterval) {
                mu0 += 0.1 * pow(StepExp, -k0);
                s = fn(s, mu0, Iteracions);
            }
            mu0 -= 0.1 * pow(StepExp, -k0);
            s = fn(s, mu0, Iteracions);
            k0++;
        }
        mu[k] = mu0;
        if (k > 1) lambda[k] = (mu[k - 1] - mu[k - 2]) / (mu[k] - mu[k - 1]);
        else lambda[k] = NAN;

        printf("%c_%i = %.8f\t%c_%i = %.8f\n", 230, k + 1, mu[k], 231, k + 1, lambda[k]);
    }
}

void OddPeriodOrbits() {
    const int MaxPer = 11, Iteracions = 5000;
    const double Step = 0.000001, CloserStep = 0.000000001;
    int i = MaxPer;
    double mu = MuInit;
    while (i >= 3) {
        double s = 0.7;
        while (mu < EOInterval && fabs(s - fn(s, mu, i)) > EPS) {
            mu += Step;
            for (int j = 0; j < Iteracions; j++) s = f(s, mu);
        }
        mu -= Step;
        for (int j = 0; j < Iteracions; j++) s = f(s, mu);
        while (mu < EOInterval && fabs(s - fn(s, mu, i)) > EPS) {
            mu += CloserStep;
            for (int j = 0; j < Iteracions; j++) s = f(s, mu);
        }
        printf("PERIODE %i: %c = %.8f\n", i, 230, mu);
        i -= 2;
    }
}
