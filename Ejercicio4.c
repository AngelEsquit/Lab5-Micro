/* Escribe un programa en C que tenga un ciclo for donde se modifiquen dos variables de manera paralela usando #pragma omp parallel for. 
a.	Usa la cláusula shared para gestionar el acceso a la variable1 dentro del ciclo.
b.	Usa la cláusula private para gestionar el acceso a la variable2 dentro del ciclo. 
c.	Prueba con ambas cláusulas y explica las diferencias observadas en los resultados.
 */

#include <stdio.h>
#include <omp.h>

#define N 1000000

int main() {
    double start_time, run_time;
    int i, sum = 0;
    int variable1 = 0;
    int variable2 = 0;

    start_time = omp_get_wtime();

    #pragma omp parallel for shared(variable1) private(variable2)
    for (i = 1; i <= N; i++) {
        variable1 += i;
        variable2 += i;
    }

    run_time = omp_get_wtime() - start_time;

    printf("Suma de los primeros %d números naturales: %d\n", N, variable1);
    printf("Suma de los primeros %d números naturales: %d\n", N, variable2);
    printf("Tiempo de ejecución: %f segundos\n", run_time);

    return 0;
}