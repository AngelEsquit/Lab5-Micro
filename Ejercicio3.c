//Escribe un programa en C que ejecute tres funciones diferentes en paralelo usando la directiva #pragma omp sections. Cada sección debe ejecutar una función distinta, por ejemplo, una que calcule el factorial de un número, otra que genere la serie de Fibonacci, y otra que encuentre el máximo en un arreglo, operaciones matemáticas no simples. Asegúrate de que cada función sea independiente y no tenga dependencias con las otras.

#include <stdio.h>
#include <omp.h>

#define N 1000000

int factorial(int n) {
    int i, fact = 1;

    for (i = 1; i <= n; i++) {
        fact *= i;
    }

    return fact;
}

int fibonacci(int n) {
    if (n <= 1) {
        return n;
    }

    return fibonacci(n - 1) + fibonacci(n - 2);
}

int max(int arr[], int n) {
    int i, max = arr[0];

    for (i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    return max;
}

int main() {
    double start_time, run_time;
    int fact, fib, max_val;
    int arr[N];
    int i;

    for (i = 0; i < N; i++) {
        arr[i] = i;
    }

    start_time = omp_get_wtime();

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            fact = factorial(10);
        }

        #pragma omp section
        {
            fib = fibonacci(10);
        }

        #pragma omp section
        {
            max_val = max(arr, N);
        }
    }

    run_time = omp_get_wtime() - start_time;

    printf("Factorial de 10: %d\n", fact);
    printf("Fibonacci de 10: %d\n", fib);
    printf("Máximo en el arreglo: %d\n", max_val);
    printf("Tiempo de ejecución: %f segundos\n", run_time);

    return 0;
}