#define _GNU_SOURCE
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <sys/dir.h>
#include <sys/syscall.h>
#include <malloc.h>

void recorrer(DIR *d, char path[]){   

    struct dirent *actual = readdir(d);
    struct stat statbuf;
    char* ruta = (char *) malloc(strlen(path)* sizeof(char *) );;

    while(actual != NULL){

        if((strcmp(actual->d_name, ".") != 0) && (strcmp(actual->d_name, "..") != 0)){

           //creo la ruta para que busque la siguiente vez 
            strcpy(ruta, path);
            strcat(ruta, "/");
            strcat(ruta, actual->d_name);

            //printf("\n%s\n", actual->d_name);
            DIR *siguiente = opendir(ruta); //Intenta abrirlo como un directorio

            if(siguiente != NULL){
                //es directorio
                stat(ruta, &statbuf);

                //path completo 
                printf("%s",ruta);

                //permisos de usuario, grupo u otro
                printf(" ");
                printf((statbuf.st_mode & S_IFDIR)? "d":"-");
                printf((statbuf.st_mode & S_IRUSR)? "r": "-");
                printf((statbuf.st_mode & S_IWUSR)? "w":"-");
                printf((statbuf.st_mode & S_IXUSR)? "x":"-");
                printf("-");
                printf((statbuf.st_mode & S_IRGRP)? "r":"-");
                printf((statbuf.st_mode & S_IWGRP)? "w":"-");
                printf((statbuf.st_mode & S_IXGRP)? "x":"-");
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
                printf(" %ld",statbuf.st_nlink);
                printf(" %ld\n",statbuf.st_blocks);

                recorrer(siguiente, ruta);
            }else{
                //es archivo
                //printf("es un archivo\n");
            }
        }

        actual = readdir(d);
    }

    closedir(d);

}

int main(int argc,char *argv[]){
    char *path;
    DIR *d;

    // desabilito el manejador de signal para ctrl-c
    signal(SIGINT, SIG_IGN);
    //verificar que sea un archivo y que se le mande los argumentos al compilar.
    if (argc != 3){
        printf("Error en argumentos..\n");
        printf("O Ejecutar de la siguiente forma --> ./els <output_file> <PATH>\n");
        exit(0);
    }

    d = opendir(argv[2]);
    path= argv[2];
    
    

    recorrer(d, path);    
    
}
