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

    double** matrix = (double**)malloc(muN * sizeof(double*));

    for (int mu = 0; mu <= muN; mu++) {
        matrix[mu] = orbit(x0, muStart + mu * muStep);
    }
    return matrix;
}

/* ROUTINES */

void OrbitsPlotGenerator() {

    double x0 = 0.7;
    double** data = orbits(x0);
    char name[100] = "..\\DataFiles\\";

    scanf("%s", name + 13);

    FILE* fp = fopen(name, "w");
    if (!fp) return;
    for (int i = 0; i < muN; i++) {
        for (int j = 1; j < N; j++) {
            if (!data[i][j])break;
            fprintf(fp, "%lf %lf\n", data[i][0], data[i][j]);
        }

    }
    fclose(fp);
}