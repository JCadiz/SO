#include "recorrer.h"

//eliminar el archivo CORE e impirmir por pantalla
void eliminar_coreP(char core[], char path[]){ 
    struct stat statbuf;
    char* ruta = (char *) malloc(strlen(path)* sizeof(char *) );

    strcpy(ruta, path);
    strcat(ruta, "/");
    strcat(ruta, core); 

	if (strcmp(core, "CORE") == 0){ 
		printf("\nTE ENCONTRE!\n ");
        stat(ruta, &statbuf);
    //path completo 
        printf("%s",ruta);
        printf(" ");
    //fecha de modificacion
        printf(" %s",ctime(&statbuf.st_mtim.tv_sec));
    //numero de enlaces y tamano de bloques
        printf(" %ld",statbuf.st_size);
        printf(" %ld",statbuf.st_blocks);

		unlink(ruta);
	}else{
        //printf("\nNo es el archivo que buscaba\n ");
    }
}

//eliminar el archivo CORE e guarda en reporte.txt
void eliminar_core(char core[], char path[], char archivo[]){ 
    struct stat statbuf;
    char* ruta = (char *) malloc(strlen(path)* sizeof(char *) );
    char* contenido = (char *) malloc((strlen(path)*100)* sizeof(char *) );
    char bloques[10], size[10];
    FILE *reporte;

    strcpy(ruta, path);
    strcat(ruta, "/");
    strcat(ruta, core); 

	if (strcmp(core, "CORE") == 0){ 
		printf("\nTE ENCONTRE!\n ");
        stat(ruta, &statbuf);
    //path completo 
        strcat(contenido , ruta);
        strncat(contenido, " ", 1);
    //fecha de modificacion
        strcat(contenido , ctime(&statbuf.st_mtim.tv_sec));
        strncat(contenido, " ", 1);
    //numero de enlaces y tamano de bloques
        sprintf(size,"%ld",statbuf.st_size);
        sprintf(bloques,"%ld",statbuf.st_blocks);
        strcat(contenido , size);
        strncat(contenido, " ", 1);
        strcat(contenido , bloques);

    //elimino el archivo CORE
        unlink(ruta);
    //guardo en reporte.txt el valor de contenido 
        reporte = fopen(archivo, "a");

        if (reporte != NULL){
            fprintf(reporte, "%s\n", contenido);

            fclose(reporte);
        }

	}else{
        //printf("\nNo es el archivo que buscaba\n ");
    }
}

void recorrer(DIR *d, char path[], char archivoid[], char nombre[]){   

    struct dirent *actual = readdir(d);
    struct stat statbuf;
    char* ruta = (char *) malloc(strlen(path)* sizeof(char *) );
    char* contenido = (char *) malloc((strlen(path)*100)* sizeof(char *) );
    char grupo[10], usuario[10], enlaces[10], bloques[10], size[10];
    FILE *file, *reporte;

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
            
                // hijo
                stat(ruta, &statbuf);

                //path completo 
                strcat(contenido , ruta);
                strncat(contenido, " ", 1);

                //permisos de usuario, grupo u otro 
                //usuario
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
                    sprintf(usuario,"%d",statbuf.st_uid);
                    sprintf(grupo,"%d",statbuf.st_gid);

                    strcat(contenido , usuario);
                    strncat(contenido, " ", 1);
                    strcat(contenido , grupo);
                    strncat(contenido, " ", 1);

                // fecha de acceso y modificacion
                    strcat(contenido , ctime(&statbuf.st_atim.tv_sec));
                    strncat(contenido, " ", 1);
                    strcat(contenido , ctime(&statbuf.st_mtim.tv_sec));
                    strncat(contenido, " ", 1);

                //numero de enlaces y tamano de bloques
                    sprintf(size,"%ld",statbuf.st_size);
                    sprintf(enlaces,"%ld",statbuf.st_nlink);
                    sprintf(bloques,"%ld",statbuf.st_blocks);
                    strcat(contenido , size);
                    strncat(contenido, " ", 1);
                    strcat(contenido , enlaces);
                    strncat(contenido, " ", 1);
                    strcat(contenido , bloques);

                //escribo para el PID.txt
                   
                    file = fopen(archivoid, "a");

                    if (file != NULL){
                        fprintf(file, "%s\n", contenido);

                        fclose(file);
                    }

                    reporte = fopen(nombre, "a");

                    if (reporte != NULL){
                        fprintf(reporte, "\t\t%s   %ld   %ld\n", ruta, statbuf.st_nlink, statbuf.st_size);

                        fclose(reporte);
                    }
                    
                    recorrer(siguiente, ruta, archivoid, nombre);

            }else{
                //es archivo
                //printf("es un archivo\n");

                eliminar_core(actual->d_name, path, nombre); 
            }
        }

        actual = readdir(d);
    }

}

void recorrer_sinFile(DIR *d, char path[]){

    struct dirent *actual = readdir(d);
    struct stat statbuf;
    char* ruta = (char *) malloc(strlen(path)* sizeof(char *) );

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
                    printf(" %s",ctime(&statbuf.st_atim.tv_sec));
                    printf(" %s",ctime(&statbuf.st_mtim.tv_sec)); 

                //numero de enlaces y tamano de bloques
                    printf(" %ld",statbuf.st_size);
                    printf(" %ld",statbuf.st_nlink);
                    printf(" %ld\n",statbuf.st_blocks);

                    recorrer_sinFile(siguiente, ruta);

            }else{
                //es archivo
                //printf("es un archivo\n%s",actual->d_name);

                eliminar_coreP(actual->d_name, path); 
            }
        }

        actual = readdir(d);
    }

    closedir(d);
}
