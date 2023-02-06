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
        if (last - first < Delta && first - last < Delta) break;
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

// f^n(x, mu)
double fn(double x, double mu, int n) {
    for (int i = 0; i < n; i++) x = f(x, mu);
    return x;
}

// numeric differentiation using symmetric difference formula (order 1)
double fn_x(double x, double mu, int n) {
    return (fn(x + h, mu, n) - fn(x - h, mu, n)) / (2 * h);
}

// numeric differentiation using symmetric difference formula (order 1)
double fn_mu(double x, double mu, int n) {
    return (fn(x, mu + h, n) - fn(x, mu - h, n)) / (2 * h);
}

// numeric differentiation using symmetric difference formula (order 2)
double fn_xx(double x, double mu, int n) {
    return (fn(x + h, mu, n) - 2 * fn(x, mu, n) + fn(x - h, mu, n)) / (h * h);
}

// numeric differentiation for mixed derivatives
double fn_xmu(double x, double mu, int n) {
    return (fn(x + h, mu + h, n) - fn(x - h, mu + h, n) - fn(x + h, mu - h, n) + fn(x - h, mu - h, n)) / (4 * h * h);
}

// f(x, mu) = x
double Fx_power2(double x, double mu, int n) {
    return fn(x, mu, n) - x;
}

// diff(f(x, mu), x) = -1
double Fy_power2(double x, double mu, int n) {
    return fn_x(x, mu, n) + 1;
}

// f(x, mu) = x
double Fx(double x, double mu, int n) {
    return fn(x, mu, n) - x;
}

// diff(f(x, mu), x) = 1
double Fy(double x, double mu, int n) {
    return fn_x(x, mu, n) - 1;
}

double* newton(double F(double, double, int), double dF(double, double, int),double x0, double mu0, int n) {
    const int MAX_ITER = 100;
    int iter = 0;
    double x = x0, mu = mu0;
    double x_aux, mu_aux;
    double d, deval;
    double d11, d12, d21, d22;  // differential matrix
    double det;
    // functions of newton: F = (Fx, Fy).
    do {
        d11 = fn_x(x, mu, n);
        d12 = fn_mu(x, mu, n);
        d21 = fn_xx(x, mu, n);
        d22 = fn_xmu(x, mu, n);
        det = d11 * d22 - d12 * d21;
        x_aux = x - (d22 * F(x, mu, n) - d12 * dF(x, mu, n)) / det;
        mu_aux = mu - (-d21 * F(x, mu, n) + d11 * dF(x, mu, n)) / det;
        d = MAX(fabs(x - x_aux), fabs(mu - mu_aux));
        x = x_aux;
        mu = mu_aux;
        deval = MAX(fabs(F(x, mu, n)), fabs(dF(x, mu, n)));
        iter++;
    } while (iter < MAX_ITER && MAX(d, deval) > EPS);
    double* v = (double*)malloc(2 * sizeof(double));
    v[0] = x;
    v[1] = mu;
    return v;
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
    const double Step = 0.000002;
    int i = MaxPer;
    double mu = MuInit;
    while (i >= 3) {
        while (mu < EOInterval) {
            double s = 0.7;
            mu += Step;
            for (int j = 0; j < Iteracions; j++) s = f(s, mu);

            if (fabs(s - fn(s,mu,i)) < EPS) {
                printf("PERIODE %i: %c = %lf\n", i, 230, *(newton(Fx, Fy, s, mu, i) + 1));
                break;
            }
        }
        i -= 2;
    }
}
