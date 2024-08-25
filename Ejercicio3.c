#include <stdio.h>
#include <omp.h>

#define N 1000000

int factorial(int n) { // Función para calcular el factorial de un número
    int i, fact = 1;

    for (i = 1; i <= n; i++) {
        fact *= i;
    }

    return fact;
}

int fibonacci(int n) { // Función para calcular el n-ésimo término de la serie de Fibonacci
    if (n <= 1) {
        return n;
    }

    return fibonacci(n - 1) + fibonacci(n - 2);
}

int max(int arr[], int n) { // Función para encontrar el valor máximo en un arreglo
    int i, max = arr[0];

    for (i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    return max;
}

int main() {
    // Inicializa las variables
    double start_time, run_time;
    int fact, fib, max_val;
    int arr[N];
    int i;

    for (i = 0; i < N; i++) { // Inicializa el arreglo con valores del 0 al N-1
        arr[i] = i;
    }

    start_time = omp_get_wtime(); // Inicia el temporizador

    #pragma omp parallel sections // Ejecuta las secciones en paralelo
    {
        #pragma omp section // Sección para calcular el factorial de 10
        {
            fact = factorial(10);
        }

        #pragma omp section // Sección para calcular el término 10 de la serie de Fibonacci
        {
            fib = fibonacci(10);
        }

        #pragma omp section // Sección para encontrar el valor máximo en el arreglo
        {
            max_val = max(arr, N);
        }
    }

    run_time = omp_get_wtime() - start_time; // Detiene el temporizador

    printf("Factorial de 10: %d\n", fact);
    printf("Fibonacci de 10: %d\n", fib);
    printf("Máximo en el arreglo: %d\n", max_val);
    printf("Tiempo de ejecución: %f segundos\n", run_time);

    return 0;
}