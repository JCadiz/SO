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

#define MAX 5000

void eliminar_core(char *file_name){ 
	char comando[50] = "rm ";
	//printf("\n%s\n", file_name); 
	if (strcmp(file_name, "CORE") == 0){ 
		printf("\nTE ENCONTRE!\n ");
		strcat(comando, file_name);
		system(comando);
	}else{
        //printf("\nNo es el archivo que buscaba\n ");
    }
}

void recorrer(DIR *d, char path[],char nombre[]){   

    struct dirent *actual = readdir(d);
    struct stat statbuf;
    char* ruta = (char *) malloc(strlen(path)* sizeof(char *) );
    char* contenido = (char *) malloc((strlen(path)*10)* sizeof(char *) );
    char* mensaje = (char *) malloc(strlen(path)* sizeof(char *) );
    FILE *file, *reporte, *hijo;
    char archivoid[10], aux[10],archivoid2[10], aux2[10], grupo[10], usuario[10], enlaces[10], bloques[10], size[10];
    pid_t pid;

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
                pid = fork();

                if(pid == 0){ // hijo
                    stat(ruta, &statbuf);

                    //path completo 
                    //printf("%s",ruta);
                    strcat(contenido , ruta);
                    strncat(contenido, " ", 1);
                    //permisos de usuario, grupo u otro

                    //printf(" ");
                //usuario
                    //printf((statbuf.st_mode & S_IFDIR)? "d":"-");
                    //printf((statbuf.st_mode & S_IRUSR)? "r": "-");
                    //printf((statbuf.st_mode & S_IWUSR)? "w":"-");
                    //printf((statbuf.st_mode & S_IXUSR)? "x":"-");
                    
                    if(statbuf.st_mode & S_IFDIR){
                        strncat(contenido, "d",1);
                    }else{
                        strncat(contenido, "-",1);
                    }
                    if(statbuf.st_mode & S_IRUSR){
                        strncat(contenido, "r",1);
                    }else{
                        strncat(contenido, "-",1);
                    }
                    if(statbuf.st_mode & S_IWUSR){
                        strncat(contenido, "w",1);
                    }else{
                        strncat(contenido, "-",1);
                    }
                    if(statbuf.st_mode & S_IWUSR){
                        strncat(contenido, "x",1);
                        strncat(contenido, " ",1);
                    }else{
                        strncat(contenido, "-",1);
                        strncat(contenido, " ",1);
                    }
                //grupo
                    //printf("-");
                    //printf((statbuf.st_mode & S_IRGRP)? "r":"-");
                    //printf((statbuf.st_mode & S_IWGRP)? "w":"-");
                    //printf((statbuf.st_mode & S_IXGRP)? "x":"-");

                    if(statbuf.st_mode & S_IRGRP){
                        strncat(contenido, "r",1);
                    }else{
                        strncat(contenido, "-",1);
                    }
                    if(statbuf.st_mode & S_IWGRP){
                        strncat(contenido, "w",1);
                    }else{
                        strncat(contenido, "-",1);
                    }
                    if(statbuf.st_mode & S_IXGRP){
                        strncat(contenido, "x",1);
                        strncat(contenido, " ",1);
                    }else{
                        strncat(contenido, "-",1);
                        strncat(contenido, " ",1);
                    }
                //otros
                    //printf("-");
                    //printf((statbuf.st_mode & S_IROTH)? "r":"-");
                    //printf((statbuf.st_mode & S_IWOTH)? "w":"-");
                    //printf((statbuf.st_mode & S_IXOTH)? "x":"-");

                    if(statbuf.st_mode & S_IROTH){
                        strncat(contenido, "r",1);
                    }else{
                        strncat(contenido, "-",1);
                    }
                    if(statbuf.st_mode & S_IWOTH){
                        strncat(contenido, "w",1);
                    }else{
                        strncat(contenido, "-",1);
                    }
                    if(statbuf.st_mode & S_IXOTH){
                        strncat(contenido, "x",1);
                        strncat(contenido, " ",1);
                    }else{
                        strncat(contenido, "-",1);
                        strncat(contenido, " ",1);
                    }

                //id de usario y grupo
                    //printf(" %d",statbuf.st_uid);
                    //printf(" %d",statbuf.st_gid);

                    sprintf(usuario,"%d",statbuf.st_uid);
                    sprintf(grupo,"%d",statbuf.st_gid);

                    strcat(contenido , usuario);
                    strncat(contenido, " ", 1);
                    strcat(contenido , grupo);
                    strncat(contenido, " ", 1);

                // fecha de acceso y modificacion
                    //printf(" %s",ctime(&statbuf.st_atim));
                    //printf(" %s",ctime(&statbuf.st_mtim.tv_sec)); 

                    strcat(contenido , ctime(&statbuf.st_atim));
                    strncat(contenido, " ", 1);
                    strcat(contenido , ctime(&statbuf.st_mtim.tv_sec));
                    strncat(contenido, " ", 1);

                //numero de enlaces y tamano de bloques
                    //printf("tamano bytes --> %ld\n",statbuf.st_size);
                    //printf(" %ld",statbuf.st_nlink);
                    //printf(" %ld\n",statbuf.st_blocks);

                    sprintf(size,"%ld",statbuf.st_size);
                    sprintf(enlaces,"%ld",statbuf.st_nlink);
                    sprintf(bloques,"%ld",statbuf.st_blocks);
                    strcat(contenido , size);
                    strncat(contenido, " ", 1);
                    strcat(contenido , enlaces);
                    strncat(contenido, " ", 1);
                    strcat(contenido , bloques);

                //creo la epresion para el PID.txt
                    sprintf(aux,"%d",getpid());
                    strcat(archivoid, aux);
                    strncat(archivoid, ".txt",10);

                    file = fopen(archivoid, "w");

                    if (file != NULL){
                        fprintf(file, "\n%s", contenido);

                        fclose(file);
                    }
                    
                    recorrer(siguiente, ruta, nombre);

                    exit(0);
                }else { //padre 
                    int status;
                    waitpid(pid, &status, 0);
                /* 
                //genero la expresion para abrir el txt de mi hijo
                    sprintf(aux2,"%d",pid);
                    strcat(archivoid2, aux2);
                    strncat(archivoid2, ".txt",10);

                    hijo = fopen(archivoid2, "r");
                
                    if (hijo != NULL){
                        while(!feof(hijo)){
                            fgets(mensaje, MAX, hijo);
                            printf("%s\n", mensaje);
                            //printf("\n");
                        }
                    }
                    fclose(hijo);

                    reporte = fopen(nombre, "w");

                    if (file != NULL){
                        fprintf(reporte, "\n%s", mensaje);

                        fclose(reporte);
                    }
                    */
                }   
            }else{
                //es archivo
                //printf("es un archivo\n");

                eliminar_core(actual->d_name); 
            }
        }

        actual = readdir(d);
    }

    closedir(d);

}

int main(int argc,char *argv[]){
    char *path, *nombre;
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
    nombre = argv[1];
    
    

    recorrer(d, path , nombre);    
    
}
