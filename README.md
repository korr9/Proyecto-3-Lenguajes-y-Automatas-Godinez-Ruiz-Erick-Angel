# Proyecto Módulo 3: Acelerador de Funciones 

Este proyecto demuestra cómo optimizar el rendimiento crítico de software mediante el uso de **Ensamblador Inline (Inline Assembly)** en arquitectura x86_64, comparando una implementación en lenguaje C puro frente a una solución optimizada directamente con instrucciones nativas de hardware del procesador.

---

Objetivo del Proyecto
Desarrollar un programa en C que compare el rendimiento de una función que cuenta los bits activos (Population Count) de un número de 64 bits implementada en C puro, contra una versión equivalente optimizada en ensamblador inline, midiendo sus tiempos de ejecución precisos con la librería `<time.h>`.

---

Problema Seleccionado
* **Opción A:** "Contador de Bits" (Population Count) 
* **Descripción:** Contar cuántos bits en `1` tiene un número entero sin signo de 64 bits (`unsigned long long`).
* **Volumen de Prueba:** 100 millones de iteraciones (`N = 100,000,000`).

---

Resultados de Rendimiento

A continuación se detallan los resultados obtenidos al ejecutar el benchmark en una simulación sin optimizaciones del compilador (`-O0`) para garantizar una comparación directa de hardware:

| Métrica | Versión en C Puro | Versión en Ensamblador Inline (`POPCNT`) |
| :--- | :---: | :---: |
| **Tiempo de Ejecución** | `23.4600 s` | `1.0620 s` |
| **Integridad de Datos** | Coincide (Éxito) | Coincide (Éxito) |
| **Factor de Mejora (Speedup)** | — | **22.09x más rápido** ⚡ |

Análisis de la Optimización
1. **Eliminación de Bucles:** La versión de C utiliza un ciclo `while` que procesa bit por bit de manera secuencial desplazando el número a la derecha hasta 64 veces. Esto introduce sobrecarga por cada salto condicional.
2. **Instrucción de Hardware Nativa:** La versión en ASM aprovecha la instrucción de hardware **`popcnt`** de la arquitectura x86_64, la cual ejecuta el conteo total de bits del registro de 64 bits en un único ciclo de reloj del procesador.

---

Requisitos y Compilación

El proyecto está diseñado bajo el estándar **C99** y requiere soporte de la instrucción de hardware `popcnt` en el procesador.

### Comando de Compilación (GCC)
Para compilar desactivando las optimizaciones nativas del compilador (`-O0`) y habilitando explícitamente el set de instrucciones extendido, ejecuta en tu terminal:

```bash
gcc -std=c99 -O0 -mpopcnt main.c -o acelerador
```

### Ejecución
En Windows (Símbolo del sistema):
```cmd
acelerador
