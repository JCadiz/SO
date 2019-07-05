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

void ReportePadre(char path[], char carpeta[],char reporte){
    FILE *report;
    struct stat statbuf2;
    char *ruta;
    printf("carpeta: %s\n", carpeta);
    //calcular la ruta
    ruta = path;
    strcat(ruta,"/");
    strcat(ruta,carpeta);
     printf("nombre ruta es: %s\n",ruta);

   /*  if(stat(ruta, &statbuf2)==-1){

    }
      
    if(statbuf2.st_mode & S_IFDIR){
        printf("nombre ruta es: %s\n",ruta);
    }*/
}

int main(int argc,char *argv[]){
    //declaracion de variables y struct
    DIR *d;
    struct stat statbuf;
    struct dirent dirEntry;
    char aux[4], archivoid[4], *reporte;
    int fd, charsRead;
    pid_t pid;
    FILE *reporteP; // reporte del padre
    // desabilito el manejador de signal para ctrl-c
    signal(SIGINT, SIG_IGN);
    //verificar que sea un archivo y que se le mande los argumentos al compilar.
    if (argc != 3){
        printf("Error en argumentos..\n");
        fprintf(stderr,"Usage : %s nombre de archivo \n", argv[0]);
        printf("Ejecutar de la siguiente forma --> ./els <output_file> <PATH>\n");
        exit(0);
    }
    //guardo el valor para el reporte final
    reporte = argv[1];
    //Verificar que sea un directorio
    if (stat(argv[2], &statbuf) == -1){
        fprintf(stderr, " No se pudo aplico el stat sobre el archivo %s: %s\n",argv[2], strerror(errno));
        exit(0);
    } 
    if(statbuf.st_mode & S_IFDIR){
        printf("%s es un directorio\n",argv[2]);
        printf("----- Datos del Directorio ----\n");
        printf("inode --> %ld\n",statbuf.st_ino);
        printf("Permisos : ");
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
        printf("\n");
        printf("id dispositivo --> %ld\n",statbuf.st_dev);
        printf("id dispositivo tipo bloque --> %ld\n",statbuf.st_rdev);
        printf("numero de enlaces --> %ld\n",statbuf.st_nlink);
        printf("usuario propetario --> %d\n",statbuf.st_uid);
        printf("id grupo --> %d\n",statbuf.st_gid);
        printf("tamano bytes --> %ld\n",statbuf.st_size);
        printf("fecha ultimo acceso --> %s\n",ctime(&statbuf.st_atim));
        printf("fecha ultima modificacion --> %s",ctime(&statbuf.st_mtim.tv_sec));
        printf("fecha current time --> %s",ctime(&statbuf.st_ctim.tv_sec));
        printf("tamano bloque E/S --> %ld\n",statbuf.st_blksize);
        printf("numero de bloques --> %ld\n",statbuf.st_blocks);
    }else{
        printf("%s no es un directorio\n",argv[2]);
    }

    fd = open(argv[2], O_RDONLY);

    if(fd == -1){
        perror("Error: ");
    }

    pid = fork();

    if (pid == 0){
        while(1){
            charsRead = syscall(SYS_getdents,fd,&dirEntry, sizeof(struct dirent));
            if (charsRead == -1){
                perror(" printdir: ");
                return -1;
            }
            if (charsRead ==0 ){
                break;
            }
            if((strcmp(dirEntry.d_name,".")!= 0) && ((dirEntry.d_name, "..") != 0)){
                // padre e hijo
                
                //creo el nombre con el que genero el txt
                //sprintf(aux,"%d",getpid());
                //strcat(archivoid, aux);
                //strncat(archivoid,".txt",4);
                //printf("archivoid: %s\n",archivoid);
                //printf("%s\n",dirEntry.d_name);
                ReportePadre(argv[2], dirEntry.d_name, reporte);
                //lseek(fd, dirEntry.d_off,L_SET);
            }
        }
    }else{
        wait(NULL);
    }

    
       
        

    return 0;
}