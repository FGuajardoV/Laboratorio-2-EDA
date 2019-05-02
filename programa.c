#include "programa.h"

int main()
{
    Nodo * matrix;
    matrix = leerArchivo();

    printf ( "\n\n************************** Fin Programa *************************\n\n" );

}

Nodo * crearNodo(int x, int y)
{
    //Se pide el espacio de memoria para la estructura
	Nodo *nodo = ( Nodo * ) malloc ( sizeof ( Nodo ) );
	//Si la asignacion de memoria es exitosa, se inicializan las variables
	if ( nodo != NULL )
    {
	    nodo -> posX    =   x;
        nodo -> posY    =   y;
        nodo -> valor   =   0;
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
    Nodo * nuevoNodo;

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
        return nuevoNodo;
    }

    else
    {
        fscanf ( file, "%d %d\n", &largoMatriz, &potencia ); //printf("Largo matriz: %d, potencia: %d\n",largoMatriz, potencia);
        int i = 0, j = 0;
        nuevoNodo = crearNodo( i, j );
    }

    fclose ( file );
    return nuevoNodo;
}

//https://global.cainiao.com/detail.htm?mailNoList=12881800227000211904051001&spm=a3708.7860688.0.d01