#include "programa.h"

int main()
{
    Nodo * matrix;
    matrix = leerArchivo();

    printf("Espacio usado en memoria por la matriz dispersa: %lu", sizeof ( matrix ) );

    printf ( "\n\n************************** Fin Programa *************************\n\n" );

}

Nodo * crearNodo ( int fila, int col, double valor )
{
    //Se pide el espacio de memoria para la estructura
	Nodo *nodo = ( Nodo * ) malloc ( sizeof ( Nodo ) );
	//Si la asignacion de memoria es exitosa, se inicializan las variables
	if ( nodo != NULL )
    {
	    nodo -> posFila =   fila;
        nodo -> posCol  =   col;
        nodo -> valor   =   valor;
		nodo -> sig     =   NULL;
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
    scanf( "%s", fileName );

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
                    
                if ( valor != 0 && Matriz == NULL )
                {
                    double auxValor = calcular_potencia ( valor, potencia );
                    Nodo * nuevoNodo = crearNodo ( i, j, auxValor );
                    Matriz = nuevoNodo;
                    auxiliar = Matriz;
                }

                else if ( valor != 0 )
                {
                    double auxValor = calcular_potencia ( valor, potencia );
                    Nodo * nuevoNodo = crearNodo ( i, j, auxValor );
                    auxiliar -> sig = nuevoNodo;
                    auxiliar = auxiliar -> sig;
            //printf("Valor ( %lf ) en (%d, %d)\n", auxiliar->valor, auxiliar->posFila, auxiliar->posCol); 
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