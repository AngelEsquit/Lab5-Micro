/*
 * Archivo: Ejercicio_5A.c
 * Descripción: Este programa cuenta cuántas veces aparece un valor específico 
 * ('key') en un arreglo de números aleatorios.
 * 
 * Funcionalidad:
 * - Genera un arreglo de tamaño N con valores aleatorios.
 * - Inserta manualmente el valor 'key' en tres posiciones específicas del arreglo.
 * - Cuenta cuántas veces aparece 'key' en el arreglo usando una función llamada count_key().
 * - Imprime el número de apariciones de 'key' en el arreglo.
 * 
 * Referencia:
 * Chandra, . R. et al. Parallel Programming in OpenMP
 *
 * Fecha modificación: 08-16-2024
 */

// gcc -fopenmp -o 5 Ejercicio_5A.c
// ./5
 
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 131072 // Tamaño del arreglo
#define THRESHOLD 10000  // Umbral para cambiar a conteo secuencial

long count_key(long *a, long start, long end, long key) {
    long count = 0;
    
    printf("Hilo %d: Contando desde %ld hasta %ld\n", omp_get_thread_num(), start, end);

    // Si el tamaño de la tarea es menor o igual al THRESHOLD, realiza el conteo secuencial
    if (end - start <= THRESHOLD) {
        for (long i = start; i < end; i++) {
            if (a[i] == key) count++;
        }
    } else { // Divide la tarea en dos partes y crea tareas para contarlas en paralelo
        long mid = (start + end) / 2;
        long count_left = 0, count_right = 0;

        #pragma omp task shared(count_left) // Crea una tarea para contar la mitad izquierda
        count_left = count_key(a, start, mid, key);

        #pragma omp task shared(count_right) // Crea una tarea para contar la mitad derecha
        count_right = count_key(a, mid, end, key);

        #pragma omp taskwait // Espera a que ambas tareas terminen
        count = count_left + count_right; // Suma los conteos de ambas mitades
    }
    
    return count; // Retorna el conteo total
}

int main() {
    long a[N], key = 42, nkey = 0;

    // Inicializa el arreglo con valores aleatorios
    for (long i = 0; i < N; i++) a[i] = rand() % N;

    // Asigna algunos valores específicos de 'key' para asegurarse de que existan en el arreglo
    a[N % 43] = key; 
    a[N % 73] = key; 
    a[N % 3] = key;

    // Configura el entorno de OpenMP
    omp_set_num_threads(12); // Configura el número de hilos
    #pragma omp parallel
    {
        #pragma omp single
        nkey = count_key(a, 0, N, key);  // Llama a la función de conteo en paralelo
    }

    printf("Numero de veces que 'key' aparece paralelamente: %ld\n", nkey);

    return 0;
}