#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Estructuras utilizadas.
typedef struct Nodo
{
    int posX;
    int posY;
    double valor;
    struct Nodo *sig;
} Nodo;

//Prototipos de Funciones.
Nodo * leerArchivo();
Nodo * crearNodo();


