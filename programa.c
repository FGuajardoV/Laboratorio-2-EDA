#include "programa.h"

int main()
{
    Lista * matrix;
    matrix = leerArchivo();

    printf ( "\n\n************************** Fin Programa *************************\n\n" );

}

Lista * leerArchivo()
{
    FILE * file;
    char fileName[ 256 ];
    int largoMatriz, potencia;  

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
        fscanf(file, "%i %i\n", &largoMatriz, &potencia);

        Nodo * nuevoNodo;
        nuevoNodo = ( Nodo * ) malloc ( sizeof ( Nodo ) );
    }

    fclose ( file );
    
}
