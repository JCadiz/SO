#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include "recorrer.h"

int main(int argc,char *argv[]){
    char *path, *nombre, archivoid[5], aux[5];
    char ruta[strlen(argv[1])*10];
    struct dirent *actual;
    struct stat statbuf;
    FILE *reporte;
    DIR *d, *next;
    pid_t id;
    
    // desabilito el manejador de signal para ctrl-c
    signal(SIGINT, SIG_IGN);
    //verificar que sea un archivo y que se le mande los argumentos al compilar.
     if (argc == 2){
        printf("opcion de sin reporte por txt\n");
        d = opendir(argv[1]);
        path = argv[1];
        
        while ((actual = readdir (d)) != NULL){
            if((strcmp(actual->d_name, ".") != 0) && (strcmp(actual->d_name, "..") != 0)){
                if(actual != NULL){
                    //es un directorio y creo un hijo para cada directorio
                    id = fork();
                    if(id < 0){
                        printf("errno = %d\n", errno);
			            perror("main");
                    }else if (id == 0){ // es el hijo recorro esa carpeta
                        //calculo de la ruta

                        strcpy(ruta, path);
                        strcat(ruta, "/");
                        strcat(ruta, actual->d_name);

                        stat(path, &statbuf);

                    //path completo 
                        printf("%s",path);
                        printf(" ");

                    //permisos de usuario, grupo u otro
                    //usuario
                        printf((statbuf.st_mode & S_IFDIR)? "d":"-");
                        printf((statbuf.st_mode & S_IRUSR)? "r": "-");
                        printf((statbuf.st_mode & S_IWUSR)? "w":"-");
                        printf((statbuf.st_mode & S_IXUSR)? "x":"-");
                        
                    //grupo
                        printf("-");
                        printf((statbuf.st_mode & S_IRGRP)? "r":"-");
                        printf((statbuf.st_mode & S_IWGRP)? "w":"-");
                        printf((statbuf.st_mode & S_IXGRP)? "x":"-");

                    //otros
                        printf("-");
                        printf((statbuf.st_mode & S_IROTH)? "r":"-");
                        printf((statbuf.st_mode & S_IWOTH)? "w":"-");
                        printf((statbuf.st_mode & S_IXOTH)? "x":"-");

                    //id de usario y grupo
                        printf(" %d",statbuf.st_uid);
                        printf(" %d",statbuf.st_gid);

                    // fecha de acceso y modificacion
                        printf(" %s",ctime(&statbuf.st_atim));
                        printf(" %s",ctime(&statbuf.st_mtim.tv_sec)); 

                    //numero de enlaces y tamano de bloques
                        printf(" %ld",statbuf.st_size);
                        printf(" %ld",statbuf.st_nlink);
                        printf(" %ld\n",statbuf.st_blocks);

                        next = opendir(ruta);
                        //hago la funcion recursiva
                        recorrer_sinFile(next,ruta);

                        exit(0);
                    }else{
                        wait(NULL);

                    }
                }
            }
        } 
    }else if (argc == 3){
        printf("opcion con reporte por txt\n");
        d = opendir(argv[2]);
	    path= argv[2];
	    nombre = argv[1];

        reporte = fopen(nombre, "w");

        if(reporte != NULL ){
            fprintf(reporte, "PATH: %s\n", path);
            fclose(reporte);
        }

        while ((actual = readdir (d)) != NULL){
            if((strcmp(actual->d_name, ".") != 0) && (strcmp(actual->d_name, "..") != 0)){
                if(actual != NULL){
                    //es un directorio y creo un hijo para cada directorio
                    id = fork();
                    if(id < 0){
                        printf("errno = %d\n", errno);
			            perror("main");
                    }else if (id == 0){ // es el hijo recorro esa carpeta
                        //calculo de la ruta

                        strcpy(ruta, path);
                        strcat(ruta, "/");
                        strcat(ruta, actual->d_name);

                        sprintf(aux,"%d",getpid());
                        strcat(archivoid, aux);
                        strncat(archivoid, ".txt",5);
                        //printf("%s\n", archivoid);

                        next = opendir(ruta);
                        //hago la funcion recursiva
                        recorrer(next, ruta , archivoid, nombre);

                        exit(0);		
                    }else{
                        strcpy(ruta, path);
                        strcat(ruta, "/");
                        strcat(ruta, actual->d_name);

                        stat(path, &statbuf);

                        reporte = fopen(nombre, "a");

                        if(reporte != NULL ){
                            fprintf(reporte, "\t%s   %ld   %ld\n", ruta, statbuf.st_nlink, statbuf.st_size);
                            fclose(reporte);
                        }

                        wait(NULL);

                    }
                }else {
                    //archivo
                }
            }
        } 
	}else{
    	printf("Error en argumentos..\n");
        printf("Ejecutar de la siguiente forma --> ./els <PATH>\n");
        printf("O Ejecutar asi --> ./els <output_file.txt> <PATH>\n");
        exit(0);
	}
      
    return 0;
}
