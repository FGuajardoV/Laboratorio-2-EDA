 // Libreria que incluye el TDA usado y las cabezeras de las funciones.
#include "programa.h"

// Funcion principal del programa.
int main()
{
    Nodo * matrix;
    int tamano;

    matrix = leerArchivo();

    printf ("\nMatriz resultante es: \n\n");

    mostrar_arreglo ( matrix );

    // Corresponde al tamano del double = 8 bytes, int = 2 bytes. Puesto que en el nodo
    //se posee un double (valor), 3 int (posFila, posCol, tamanoMatriz) se procede de la forma.
    // Suponiendo que se almacenara la matriz completa, necesitamos la cantidad total de elementos
    //contando los 0.
    tamano = ( 8 + ( 3 * 2 ) ) * matrix -> tamanoMatriz * matrix -> tamanoMatriz;

    printf ( "\nEl tamano en memoria de la matriz dispersa: %d bytes", calcular_tamano ( matrix ) );
    printf ( "\nEl tamano en memoria de la matriz completa habria sido: %d bytes", tamano );

    printf ( "\n\n************************** Fin Programa *************************\n\n" );

    liberar_memoria ( matrix );
}

// Funcion encargada de crear un tipo de Dato Nodo para poder almacenar los valores que se 
//obtienen a traves de la lectura de datos del archivo.
Nodo * crearNodo ( int fila, int col, double valor )
{
    // Se pide el espacio de memoria para la estructura.
	Nodo * nodo = ( Nodo * ) malloc ( sizeof ( Nodo ) );

	// Si la asignacion de memoria es exitosa, se inicializan las variables.
	if ( nodo != NULL )
    {
	    nodo -> posFila         =   fila;
        nodo -> posCol          =   col;
        nodo -> valor           =   valor;
        nodo -> tamanoMatriz    =   0;
		nodo -> sig             =   NULL;
		return nodo;
	}

	// En caso contrario se retorna nulo.
	else
    {
		return NULL;
	}
}

// Funcion que se encarga de leer el archivo de texto plano donde se encuentra la matriz almacenada
//y ejecutando, en el momento, la potencia del numero en matriz para solo almacenar el resultado.
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

    // Se abre el archivo en modo lectura.
    file = fopen ( fileName, "r" );

    // Se verifica si es que el archivo existe dentro del directorio, si es que este no se
    //encuentra mostrara un mensaje de error en pantalla para guiar al usuario.
    if ( file == NULL)
    {
        perror ( "Error al intentar de abrir el archivo... " );
        printf ( "\n\n************************** Fin Programa *************************\n\n" );
        exit ( EXIT_FAILURE );
    }

    else
    {
        // Leemos la primera linea del archivo y almacenamos los datos que nos especificaran el 
        //tamano del arreglo y la potencia que se debe de aplicar.
        fscanf ( file, "%d %d\n", &largoMatriz, &potencia );
        double valor;
        Nodo * auxiliar;

        for ( i = 0; i < largoMatriz; i++ )
        {
            for ( j = 0; j < largoMatriz; j++ )
            {
                // Se almacenan en double, si no encuentra un double sale del for por el break.
                // Pero el puntero del archivo se sigue moviendo.
                if ( !fscanf ( file, "%lf", &valor ) )
                    break;
                    
                // Si el valor es distinto a cero, pero no existe aun el arreglo de nodos, se creara
                //uno para poder comenzar a trabajar.   
                else if ( valor != 0 && Matriz == NULL )
                {
                    // se calcula potencia
                    double auxValor = calcular_potencia ( valor, potencia );
                    // Crea el nodo para almacenar datos, guardando la posicion donde se encontro el
                    //dato.
                    Nodo * nuevoNodo = crearNodo ( i, j, auxValor );
                    // El nodo cabezera, sera el unico que almacenara el tamano de la matriz.
                    nuevoNodo -> tamanoMatriz = largoMatriz; 
                    Matriz = nuevoNodo;
                    // Para guardar el nodo cabezera, se trabajara en un auxiliar.
                    auxiliar = Matriz; 
                }
                // Si el valor es distinto a cero, pero ya existe un arreglo de nodos, solo agregara
                //el siguiente.
                else if ( valor != 0 )
                {
                    double auxValor = calcular_potencia ( valor, potencia );
                    Nodo * nuevoNodo = crearNodo ( i, j, auxValor );
                    auxiliar -> sig = nuevoNodo;
                    // Auxiliar pasa a ser el nodo creado para poder enlazar el resto de la matriz.
                    auxiliar = auxiliar -> sig;
                }
            }
        }
    }
    // liberamos memoria.
    fclose ( file );
    return Matriz;
}

// Funcion que retornara la potencia de un valor. 
double calcular_potencia ( double valor, int potencia )
{
    double resultado = 1;

    for ( int i = 1; i <= potencia; i++)
        resultado *= valor;

    return resultado;
}

// Usando las posiciones del Nodo, se mostrara en pantalla la matriz dispersa con los 
//ceros correspondientes.
void mostrar_arreglo ( Nodo * matriz )
{
    Nodo * auxiliar;
    int largoMatriz, fila, columna;
    double valorNeutro;

    // Usamos un auxiliar para no perder el nodo cabezera de la lista enlazada.
    auxiliar = matriz;
    largoMatriz = auxiliar -> tamanoMatriz;
    valorNeutro = 0;
    fila = 0;

    // Recorremos las "filas" de la lista enlazada.
    while ( fila < largoMatriz )
    {
        columna = 0;

        // Si ya no hay elementos en esta fila, se salta el recorrido de columnas.
        if ( auxiliar -> posFila == fila )
        {
            // Se recorren las "columnas" de la lista enlazada.
            while ( columna < largoMatriz )
            {
                // Si el elemento existe dentro de la lista ( coordenadas fila, columna ) se procede
                //a mostrar el elemento en pantalla, sino, se agregara un cero en su lugar.
                if ( auxiliar -> posCol == columna )
                {
                    printf("%f ", auxiliar -> valor );
                    
                    // Se dejecuta este if para prevenir el analizar un nodo en estado NULL.
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

// Funcion que libera la memoria de la lista enlazada, nodo por nodo.
void liberar_memoria ( Nodo * matriz )
{
    while ( matriz != NULL)
    {
        // Usamos un auxiliar para no perder el siguiente nodo de la lista enlazada.
        Nodo * auxiliar = matriz -> sig;
        free ( matriz );
        matriz = auxiliar;
    }
}

// Funcion que retorna el tamano en bytes de una lista enlazada simple.
int calcular_tamano ( Nodo * matriz )
{
    // Usamos un auxiliar para no perder el nodo cabezera de la lista enlazada.
    Nodo * aux = matriz;
    int resultado = 0, size;

    // Corresponde al tamano del double = 8 bytes, int = 2 bytes. Puesto que en el nodo
    //se posee un double (valor), 3 int (posFila, posCol, tamanoMatriz) se procede de la forma.
    size = 8 + ( 3 * 2 ); 

    while ( aux != NULL)
    {
        resultado += size;
        aux = aux -> sig;
    }

    return resultado;
}