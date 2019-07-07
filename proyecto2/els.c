#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include "recorrer.h"

int main(int argc,char *argv[]){
    char *path, *nombre;
    DIR *d;

    // desabilito el manejador de signal para ctrl-c
    signal(SIGINT, SIG_IGN);
    //verificar que sea un archivo y que se le mande los argumentos al compilar.
     if (argc == 2){
        printf("opcion de sin reporte por txt\n");
        d = opendir(argv[1]);
        path = argv[1];

        recorrer_sinFile(d,path);
    }else if (argc == 3){
        printf("opcion con reporte por txt\n");
        d = opendir(argv[2]);
	    path= argv[2];
	    nombre = argv[1];
        
	    recorrer(d, path , nombre);		
	}else{
    	printf("Error en argumentos..\n");
        printf("Ejecutar de la siguiente forma --> ./els <PATH>\n");
        printf("O Ejecutar asi --> ./els <output_file.txt> <PATH>\n");
        exit(0);
	}
      
    return 0;
}
