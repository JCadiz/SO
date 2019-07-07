#include "recorrer.h"

//eliminar el archivo CORE e impirmir por pantalla
void eliminar_coreP(char core[], char path[]){ 
	char comando[50] = "rm ";
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

		strcat(comando, core);
		system(comando);
	}else{
        //printf("\nNo es el archivo que buscaba\n ");
    }
}

//eliminar el archivo CORE e guarda en reporte.txt
void eliminar_core(char core[], char path[], char archivo[]){ 
	char comando[50] = "rm ";
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
		strcat(comando, core);
		system(comando);

    //guardo en reporte.txt el valor de contenido 
        reporte = fopen(archivo, "w");

        if (reporte != NULL){
            fprintf(reporte, "\n%s", contenido);

            fclose(reporte);
        }

	}else{
        //printf("\nNo es el archivo que buscaba\n ");
    }
}

void recorrer(DIR *d, char path[],char nombre[]){   

    struct dirent *actual = readdir(d);
    struct stat statbuf;
    char* ruta = (char *) malloc(strlen(path)* sizeof(char *) );
    char* contenido = (char *) malloc((strlen(path)*100)* sizeof(char *) );
    char* mensaje = (char *) malloc((strlen(path)*1000)* sizeof(char *) );
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
                    strcat(contenido , ctime(&statbuf.st_atim));
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

                eliminar_core(actual->d_name, path, nombre); 
            }
        }

        actual = readdir(d);
    }

    closedir(d);

}

void recorrer_sinFile(DIR *d, char path[]){

    struct dirent *actual = readdir(d);
    struct stat statbuf;
    char* ruta = (char *) malloc(strlen(path)* sizeof(char *) );
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
                    printf(" %s",ctime(&statbuf.st_atim));
                    printf(" %s",ctime(&statbuf.st_mtim.tv_sec)); 

                //numero de enlaces y tamano de bloques
                    printf(" %ld",statbuf.st_size);
                    printf(" %ld",statbuf.st_nlink);
                    printf(" %ld\n",statbuf.st_blocks);

                    recorrer_sinFile(siguiente, ruta);

                    exit(0);
                }else { //padre 
                    wait(NULL);
                }   
            }else{
                //es archivo
                //printf("es un archivo\n");

                eliminar_coreP(actual->d_name, path); 
            }
        }

        actual = readdir(d);
    }

    closedir(d);
}
