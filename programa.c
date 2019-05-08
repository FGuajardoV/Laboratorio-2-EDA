#include "programa.h"

int main()
{
    Nodo * matrix;
    unsigned long tamano;

    matrix = leerArchivo();

    printf ("\nMatriz resultante es: \n\n");

    mostrar_arreglo ( matrix );

    unsigned long tamano = sizeof ( matrix ) * matrix -> tamanoMatriz * matrix -> tamanoMatriz;

    printf ( "\nEl tamano en memoria de la matriz dispersa: %lu bytes", calcular_tamano ( matrix ) );
    printf ( "\nEl tamano en memoria de la matriz completa habria sido: %lu bytes", tamano );

    printf ( "\n\n************************** Fin Programa *************************\n\n" );

    liberar_memoria ( matrix );
}

//Funcion encargada de crear un tipo de Dato Nodo para poder almacenar los valores que se 
//obtienen a traves de la lectura de datos del archivo
Nodo * crearNodo ( int fila, int col, double valor )
{
    //Se pide el espacio de memoria para la estructura
	Nodo * nodo = ( Nodo * ) malloc ( sizeof ( Nodo ) );

	//Si la asignacion de memoria es exitosa, se inicializan las variables
	if ( nodo != NULL )
    {
	    nodo -> posFila         =   fila;
        nodo -> posCol          =   col;
        nodo -> valor           =   valor;
        nodo -> tamanoMatriz    =   0;
		nodo -> sig             =   NULL;
		return nodo;
	}

	//En caso contrario se retorna nulo
	else
    {
		return NULL;
	}
}

Nodo * leerArchivo()
{
    FILE * file;
    char fileName[ 256 ];
    int largoMatriz, potencia;  
    Nodo * Matriz;
    int i, j;

    printf ( "\n\n************************ Inicio Programa ************************\n\n" );

    printf ( "Ingrese nombre del archivo contenedor de la matriz: "); 
    scanf ( "%s", fileName );

    // se abre el archivo en modo lectura
    file = fopen ( fileName, "r" );

    //Se verifica si es que el archivo existe dentro del directorio, si es que este no se
    //encuentra mostrara un mensaje de error en pantalla para guiar al usuario.
    if ( file == NULL)
    {
        perror ( "Error al intentar de abrir el archivo... " );
        printf ( "\n\n************************** Fin Programa *************************\n\n" );
        exit ( EXIT_FAILURE );
    }

    else
    {
        fscanf ( file, "%d %d\n", &largoMatriz, &potencia );
        double valor;
        Nodo * auxiliar;

        for ( i = 0; i < largoMatriz; i++ )
        {
            for ( j = 0; j < largoMatriz; j++ )
            {
                //Se almacenan en double, si no encuentra un double sale del for por el break.
                //Pero el puntero del archivo se sigue moviendo.
                if ( !fscanf ( file, "%lf", &valor ) )
                    break;
                    
                else if ( valor != 0 && Matriz == NULL )
                {
                    double auxValor = calcular_potencia ( valor, potencia );
                    Nodo * nuevoNodo = crearNodo ( i, j, auxValor );
                    nuevoNodo -> tamanoMatriz = largoMatriz;
                    Matriz = nuevoNodo;
                    auxiliar = Matriz;
                }

                else if ( valor != 0 )
                {
                    double auxValor = calcular_potencia ( valor, potencia );
                    Nodo * nuevoNodo = crearNodo ( i, j, auxValor );
                    auxiliar -> sig = nuevoNodo;
                    auxiliar = auxiliar -> sig;
                }
            }
        }
    }

    fclose ( file );
    return Matriz;
}

double calcular_potencia ( double valor, int potencia )
{
    double resultado = 1;

    for ( int i = 1; i <= potencia; i++)
        resultado *= valor;

    return resultado;
}

void mostrar_arreglo ( Nodo * matriz )
{
    Nodo * auxiliar;
    int largoMatriz, fila, columna;
    double valorNeutro;

    auxiliar = matriz;
    largoMatriz = auxiliar -> tamanoMatriz;
    valorNeutro = 0;
    fila = 0;

    while ( fila < largoMatriz )
    {
        columna = 0;

        if ( auxiliar -> posFila == fila )
        {
            while ( columna < largoMatriz )
            {
                if ( auxiliar -> posCol == columna )
                {
                    printf("%f ", auxiliar -> valor );

                    if ( auxiliar -> sig != NULL)
                        auxiliar = auxiliar -> sig;
                }
                else
                    printf("%f ", valorNeutro);

                columna++;
            }
            printf("\n");
        }

        fila++;
    } 

}

void liberar_memoria ( Nodo * matriz )
{
    while ( matriz != NULL)
    {
        Nodo * auxiliar = matriz -> sig;
        free ( matriz );
        matriz = auxiliar;
    }
}

unsigned long calcular_tamano ( Nodo * matriz )
{
    Nodo * aux = matriz;
    unsigned long resultado = 0;

    resultado = sizeof ( aux );

    while ( aux != NULL)
    {
        resultado += sizeof ( aux );
        aux = aux -> sig;
    }

    return resultado;
}