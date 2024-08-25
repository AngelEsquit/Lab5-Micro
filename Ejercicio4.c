#include <stdio.h>
#include <omp.h>

#define N 1000000 // Tamaño del arreglo

int main() {
    // Inicializa las variables
    double start_time, run_time;
    int i, sum = 0;
    int variable1 = 0;
    int variable2 = 0;

    start_time = omp_get_wtime(); // Inicia el temporizador

    #pragma omp parallel for shared(variable1) private(variable2) // Realiza la suma en paralelo
    for (i = 1; i <= N; i++) {
        variable1 += i;
        variable2 += i;
    }

    run_time = omp_get_wtime() - start_time; // Detiene el temporizador

    printf("Suma de los primeros %d números naturales: %d\n", N, variable1);
    printf("Suma de los primeros %d números naturales: %d\n", N, variable2);
    printf("Tiempo de ejecución: %f segundos\n", run_time);

    return 0;
}