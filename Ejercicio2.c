#include <stdio.h>
#include <omp.h>

#define N 1000000

int main() {
    double start_time, run_time;
    int i, sum = 0;

    start_time = omp_get_wtime();

    #pragma omp parallel for reduction(+:sum)
    for (i = 1; i <= N; i++) {
        sum += i;
    }

    run_time = omp_get_wtime() - start_time;

    printf("Suma de los primeros %d números naturales: %d\n", N, sum);
    printf("Tiempo de ejecución: %f segundos\n", run_time);

    return 0;
}