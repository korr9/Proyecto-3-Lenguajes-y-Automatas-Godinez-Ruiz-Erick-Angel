#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 100000000 // 100 millones de iteraciones

// VERSIÓN EN C PURO (NO MODIFICAR)
int contar_bits_c(unsigned long long n) {
    int count = 0;
    while (n) {
        count += n & 1;
        n >>= 1;
    }
    return count;
}

// VERSIÓN EN ENSAMBLADOR INLINE (CORREGIDA CON EL MODIFICADOR DE REGISTRO %q0)
int contar_bits_asm(unsigned long long n) {
    unsigned long long count = 0; // Cambiado a 64 bits para alinearse con la arquitectura
    
    __asm__ __volatile__ (
        "popcnt %1, %0"   // El compilador asocia correctamente ambos operandos como QWORD (64 bits)
        : "=r" (count)    // %0 es el operando de salida (count)
        : "r" (n)         // %1 es el operando de entrada (n)
        :                 // Clobber vacío
    );
    
    return (int)count;
}

int main() {
    // Semilla para números aleatorios
    srand(42);
    
    // Crear arreglo de números aleatorios
    unsigned long long *arr = (unsigned long long*)malloc(N * sizeof(unsigned long long));
    if (arr == NULL) {
        printf("Error al asignar memoria.\n");
        return 1;
    }

    for (int i = 0; i < N; i++) {
        arr[i] = ((unsigned long long)rand() << 32) | rand();
    }
    
    // Medir tiempo en C
    clock_t inicio = clock();
    long long total_c = 0;
    for (int i = 0; i < N; i++) {
        total_c += contar_bits_c(arr[i]);
    }
    clock_t fin = clock();
    double tiempo_c = (double)(fin - inicio) / CLOCKS_PER_SEC;
    
    // Medir tiempo en ASM
    inicio = clock();
    long long total_asm = 0;
    for (int i = 0; i < N; i++) {
        total_asm += contar_bits_asm(arr[i]);
    }
    fin = clock();
    double tiempo_asm = (double)(fin - inicio) / CLOCKS_PER_SEC;
    
    // Verificar que los resultados son iguales
    printf("Total en C:   %lld\n", total_c);
    printf("Total en ASM: %lld\n", total_asm);
    
    if (total_c == total_asm) {
        printf("✔️ Los resultados coinciden.\n");
    } else {
        printf("❌ ERROR: Los resultados NO coinciden.\n");
    }
    
    // Mostrar tiempos
    printf("\nTiempo en C:   %.4f s\n", tiempo_c);
    printf("Tiempo en ASM: %.4f s\n", tiempo_asm);
    printf("Mejora: %.2fx\n", tiempo_c / tiempo_asm);
    
    free(arr);
    return 0;
}
