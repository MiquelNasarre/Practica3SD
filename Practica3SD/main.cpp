#include "Header.h"

int main() {
    printf("Escriu el nom del fitxer on vols que es guardin els punts (.dat): ");
    OrbitsPlotGenerator();
    printf("El fitxer queda guardat a la carpeta de DataFiles del projecte, utilitza gnuplot per pintar-lo!");
    printf("\n\nAquestes son les primeres %c_k's (la precisio augmenta amb la k)\n\n",230);
    MuFinder();
    printf("\nAqui tenim les ultimes orbites periodiques impars\n\n");
    OddPeriodOrbits();
    

    return 0;
}

