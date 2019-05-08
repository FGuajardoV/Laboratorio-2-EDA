#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Estructuras utilizadas.
typedef struct Nodo
{
    int posFila;
    int posCol;
    double valor;
    int tamanoMatriz;
    struct Nodo *sig;
} Nodo;

//Prototipos de Funciones.
Nodo * leerArchivo();

Nodo * crearNodo ( int, int, double );

double calcular_potencia ( double, int );

void mostrar_arreglo();

void liberar_memoria();

int calcular_tamano();
