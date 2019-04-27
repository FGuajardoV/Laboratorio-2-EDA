#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Estructuras utilizadas.
typedef struct
{
    int posX;
    int posY;
    double valor;
} Nodo;

typedef struct lista
{
    Nodo nodo;
    lista *sgte;
} Lista ;


//Prototipos de Funciones.
Lista * leerArchivo();


