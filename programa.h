#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Estructuras utilizadas.
typedef struct Nodo
{
    int posFila;
    int posCol;
    double valor;
    struct Nodo *sig;
} Nodo;

//Prototipos de Funciones.
Nodo * leerArchivo();
Nodo * crearNodo( int, int, double );
double calcular_potencia( double, int );

