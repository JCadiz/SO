#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> // strcspn
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <ctype.h> // strcspn
#include <math.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

#define LONGITUD_ALFABETO 26
#define INICIO_ALFABETO_MAYUSCULAS 65
#define INICIO_ALFABETO_MINUSCULAS 97

#define MAXIMA_LONGITUD_CADENA 999999

#define MOD(i, n) (i % n + n) % n // Calcular módulo positivo, gracias a

static int *glob_var; 
const char *alfabetoMinusculas = "abcdefghijklmnopqrstuvwxyz",
           *alfabetoMayusculas = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

char cifrado(char *destino, int posiciones, char mensaje[], int pid);
void descifrado(char *destino, int posiciones, char mensaje[], int pid);
// Obtener el valor entero de un carácter:
int ord(char c);

char cifrado(char *destino, int rotaciones, char mensaje[], int pid){

    FILE *file;
    char archivoid[5], aux[5];

    sprintf(aux,"%d",pid);
    strcat(archivoid, aux);
    strncat(archivoid,".txt",5);
    //printf("%s\n",archivoid);

    for (int i=0; i<= strlen(mensaje); i++) {
    
        switch (mensaje[i]) {
            {
                case 'm':
                mensaje[i]= 48;
                break;
            }
            {
                case 'u':
                mensaje[i]= 49;
                break;
            }
            {
                case 'r':
                mensaje[i]= 50;
                break;
            }
            {
                case 'c':
                mensaje[i]= 51;
                break;
            }
            {
                case 'i':
                mensaje[i]= 52;
                break;
            }
            {
                case 'e':
                mensaje[i]= 53;
                break;
            }
            {
                case 'l':
                mensaje[i]= 54;
                break;
            }
            {
                case 'a':
                mensaje[i]= 55;
                break;
            }
            {
                case 'g':
                mensaje[i]= 56;
                break;
            }
            {
                case 'o':
                mensaje[i]= 57;
                break;
            }
            default:
            mensaje[i]= mensaje[i];
        }
    }
    
    //printf("Texto Encriptado en Murcielago es: \n%s\n", mensaje);
    //printf("\n");
    //printf("Ahora se Cifra por el metodo Cesar \n");
    //printf("\n");
    
    // cifrado cesar aqui

    int i = 0;
    while (mensaje[i]) {
        char caracterActual = mensaje[i];
        int posicionOriginal = ord(caracterActual);
        if (!isalpha(caracterActual)) {
        destino[i] = caracterActual;
        i++;
        continue; // Ir a la siguiente iteración; por eso arriba aumentamos a i
        }
        if (isupper(caracterActual)) {
        destino[i] =
            alfabetoMayusculas[(posicionOriginal - INICIO_ALFABETO_MAYUSCULAS +
                                rotaciones) %
                                LONGITUD_ALFABETO];
        } else {

        destino[i] =
            alfabetoMinusculas[(posicionOriginal - INICIO_ALFABETO_MINUSCULAS +
                                rotaciones) %
                                LONGITUD_ALFABETO];
        }
        i++;
    }

    //printf("El mensaje cifrado con Murcielago y Cesar es: \n%s\n", destino);

    file = fopen(archivoid, "w");

     if (file != NULL){
        fprintf(file, "\n%s", destino);

        fclose(file);
    }

 }

//Funcion para Descifrar el archivo
void descifrado(char *destino, int rotaciones, char mensaje[], int pid){
    
    FILE *file;
    char archivoid[5], aux[5];

    sprintf(aux,"%d",pid);
    strcat(archivoid, aux);
    strncat(archivoid,".txt",5);
    //printf("%s\n",archivoid);
   

    //Primero descifrar con metodo Cesar

    int i = 0;
    while (mensaje[i]) {
        char caracterActual = mensaje[i];
        int posicionOriginal = ord(caracterActual);
        if (!isalpha(caracterActual)) {
        destino[i] = caracterActual;
        i++;
        continue; // Ir a la siguiente iteración; por eso arriba aumentamos a i
        }
        if (isupper(caracterActual)) {
        destino[i] = alfabetoMayusculas[MOD(
            posicionOriginal - INICIO_ALFABETO_MAYUSCULAS - rotaciones,
            LONGITUD_ALFABETO)];
        } else {
        destino[i] = alfabetoMinusculas[MOD(
            posicionOriginal - INICIO_ALFABETO_MINUSCULAS - rotaciones,
            LONGITUD_ALFABETO)];
        }
        i++;
    }
    /* 
    printf("El mensaje descifrado por Cesar es: \n%s\n",destino);
    printf("\n");
    printf("Ahora se descifrar por el metodo Murcielago \n");
    printf("\n");
    */

    for (int i=0; i<=100; i++) {
    
        switch (destino[i]) {
            {
                case '0':
                destino[i]= 109;
                break;
            }
            {
                case '1':
                destino[i]= 117;
                break;
            }
            {
                case '2':
                destino[i]= 114;
                break;
            }
            {
                case '3':
                destino[i]= 99;
                break;
            }
            {
                case '4':
                destino[i]= 105;
                break;
            }
            {
                case '5':
                destino[i]= 101;
                break;
            }
            {
                case '6':
                destino[i]= 108;
                break;
            }
            {
                case '7':
                destino[i]= 97;
                break;
            }
            {
                case '8':
                destino[i]= 103;
                break;
            }
            {
                case '9':
                destino[i]= 111;
                break;
            }
            default:
            destino[i]= destino[i];
        }
    }

     //printf("Texto Descrifrado: \n%s\n", destino);

     file = fopen(archivoid, "w");

     if (file != NULL){
        fprintf(file, "\n%s", destino);

        fclose(file);
    }

}

int ord(char c) {
    return (int)c; 
}

int main(int argc, char *argv[]){
    int fd[2], n , fd2[2], fd3[2],fd4[2], longitud, i=0, j= 0, getid[2];
    char mensaje[MAXIMA_LONGITUD_CADENA],Cifrado[MAXIMA_LONGITUD_CADENA],Descifrado[MAXIMA_LONGITUD_CADENA];
    char line[MAXIMA_LONGITUD_CADENA], mensa[MAXIMA_LONGITUD_CADENA], dest[MAXIMA_LONGITUD_CADENA];
    char *archivo, aux[MAXIMA_LONGITUD_CADENA], aux2[5] ,archid[5], aux3[5] ,archid2[5], auxmensa[MAXIMA_LONGITUD_CADENA];
    char final[MAXIMA_LONGITUD_CADENA], final2[MAXIMA_LONGITUD_CADENA];
    FILE *main, *files1,*files2, *end;

    // verificacion que se envie los argumentos correctos
    if (argc != 3) {
        printf("Error en argumentos..\n");
        printf("Ejecutar de la siguiente forma --> ./pipes [opcion] archivo");
        exit(0);
    }
    archivo=argv[2];
    //printf("archivo: %s", archivo);

    main = fopen(archivo, "r");
    
    if (main != NULL){
        while(!feof(main)){
            fgets(mensaje, MAXIMA_LONGITUD_CADENA, main);
        }
    }else { //error no abrio el archivo
        printf("Error archivo no existe = %d\n", errno);
        perror("main");
        exit(0);
    }
    fclose(main);
    
    longitud = strlen(mensaje)+1;
            
    //guardar la mitad del mensaje para cada fd
    while(i<= longitud){
        if(i <= (longitud/2) ){
            aux[i] = mensaje[i];
        }else {
            mensa[j] = mensaje[i];
            j++; 
        }
        i++;
    }
    
    switch (*argv[1]){
        case 'c':
            printf("           Eligio Cifrar             \n");
            printf("\n");

            // creacion de los padre con dos hijos
            pipe(fd);
            pipe(fd2);
            pipe(fd3);
            pipe(fd4);
            printf("Padre = %d\n", getpid());
            
            if(fork()){
                //cierro fd de lectura y escribo el fd
                close(fd[0]);
                write(fd[1], aux, strlen(aux)+1);
                // creo el segundo hijo
                if(fork() == 0){
                    //cierro el fd que no uso
                    close(fd[1]);
                    close(fd[0]);
                    close(fd4[1]);
                    close(fd4[0]);
                    // cierro el fd2 de escritura, porque es de donde leo del padre
                    close(fd2[1]);

                    //leo del padre
                    printf("Hijo %d lee del pipe : ", getpid());
                    n = read(fd2[0], line, longitud);
                    line[n]=0;
                    printf("%s\n", line);
                    cifrado(Cifrado, 2, line, getpid());

                    // cierro fd3 de lectura porque el hijo escribe
                    close(fd3[0]);

                    // ya cifre ahora escribo en fd3 lo que cifre
                    sprintf(aux2,"%d",getpid());
                    strcat(archid, aux2);
                    strncat(archid,".txt",5);

                    files1 = fopen(archid, "r");
    
                    if (files1 != NULL){
                        while(!feof(files1)){
                            fgets(auxmensa, MAXIMA_LONGITUD_CADENA, files1);
                        }
                    }
                    fclose(files1);
                    write(fd3[1],auxmensa, strlen(auxmensa)+1);
                    
                    exit(0);
                }else { // cierro los files descriptor que no uso
                    close(fd2[0]);
                    close(fd3[1]);

                    write(fd2[1], mensa, strlen(mensa)+1);
                    //espero por el hijo
                    wait(NULL);
            
                    // el padre lee del hijo
                    printf("padre %d lee del pipe del hijo: ", getpid());
                    n = read(fd3[0], line, longitud);
                    line[n]=0;
                    printf("%s\n", line);
                    
                    strcat(final, line);

                }
                wait(NULL);     
                // el padre lee del hijo
                printf("padre %d lee del pipe del hijo: ", getpid());
                n = read(fd4[0], line, longitud);
                line[n]=0;
                printf("%s\n", line);

                // genero el txt final
                strcat(final2, line);              
            }else{
                //cierro el fd de escritura y los que no uso
                close(fd[1]);
                close(fd2[0]);
                close(fd2[1]);
                close(fd3[0]);
                close(fd3[1]);

                printf("Hijo 2 %d lee del pipe : ", getppid());
                n = read(fd[0], line, longitud);
                line[n]=0;
                printf("%s\n", line);
                cifrado(Cifrado, 2, line, getpid());

                // cierro fd3 de lectura porque el hijo escribe
                    close(fd4[0]);

                    // ya cifre ahora escribo en fd3 lo que cifre
                    sprintf(aux3,"%d",getpid());
                    strcat(archid2, aux3);
                    strncat(archid2,".txt",5);

                    files2 = fopen(archid2, "r");
    
                    if (files2 != NULL){
                        while(!feof(files2)){
                            fgets(dest, MAXIMA_LONGITUD_CADENA, files2);
                        }
                    }
                    fclose(files2);
                    write(fd4[1],dest, strlen(dest)+1);
                    
                exit(0);
            }
            // genero el txt final
            strcat(final2, final);
            printf("resultado: %s\n", final2);

                end = fopen("cifrado.txt", "w");

                if (end != NULL){
                    fprintf(end, "\n%s", final2);

                    fclose(end);
                }
            break;
        case 'd':
            printf("          Eligio Descifrar         \n");
            
            pipe(fd);
            pipe(fd2);
            pipe(fd3);
            pipe(fd4);
            printf("Padre = %d\n", getpid());
            
            if(fork()){
                //cierro fd de lectura y escribo el fd
                close(fd[0]);
                write(fd[1], aux, strlen(aux)+1);
                // creo el segundo hijo
                if(fork() == 0){
                    //cierro el fd que no uso
                    close(fd[1]);
                    close(fd[0]);
                    close(fd4[1]);
                    close(fd4[0]);
                    // cierro el fd2 de escritura, porque es de donde leo del padre
                    close(fd2[1]);

                    //leo del padre
                    printf("Hijo %d lee del pipe : ", getpid());
                    n = read(fd2[0], line, longitud);
                    line[n]=0;
                    printf("%s\n", line);
                    descifrado(Descifrado, 2, line, getpid());

                    // cierro fd3 de lectura porque el hijo escribe
                    close(fd3[0]);

                    // ya cifre ahora escribo en fd3 lo que cifre
                    sprintf(aux2,"%d",getpid());
                    strcat(archid, aux2);
                    strncat(archid,".txt",5);

                    files1 = fopen(archid, "r");
    
                    if (files1 != NULL){
                        while(!feof(files1)){
                            fgets(auxmensa, MAXIMA_LONGITUD_CADENA, files1);
                        }
                    }
                    fclose(files1);
                    write(fd3[1],auxmensa, strlen(auxmensa)+1);
                    
                    exit(0);
                }else { // cierro los files descriptor que no uso
                    close(fd2[0]);
                    close(fd3[1]);

                    write(fd2[1], mensa, strlen(mensa)+1);
                    //espero por el hijo
                    wait(NULL);
            
                    // el padre lee del hijo
                    printf("padre %d lee del pipe del hijo: ", getpid());
                    n = read(fd3[0], line, longitud);
                    line[n]=0;
                    printf("%s\n", line);
                    
                    strcat(final, line);

                }
                wait(NULL);     
                // el padre lee del hijo
                printf("padre %d lee del pipe del hijo: ", getpid());
                n = read(fd4[0], line, longitud);
                line[n]=0;
                printf("%s\n", line);

                // genero el txt final
                strcat(final2, line);              
            }else{
                //cierro el fd de escritura y los que no uso
                close(fd[1]);
                close(fd2[0]);
                close(fd2[1]);
                close(fd3[0]);
                close(fd3[1]);

                printf("Hijo 2 %d lee del pipe : ", getppid());
                n = read(fd[0], line, longitud);
                line[n]=0;
                printf("%s\n", line);
                descifrado(Descifrado, 2, line, getpid());

                // cierro fd3 de lectura porque el hijo escribe
                    close(fd4[0]);

                    // ya cifre ahora escribo en fd3 lo que cifre
                    sprintf(aux3,"%d",getpid());
                    strcat(archid2, aux3);
                    strncat(archid2,".txt",5);

                    files2 = fopen(archid2, "r");
    
                    if (files2 != NULL){
                        while(!feof(files2)){
                            fgets(dest, MAXIMA_LONGITUD_CADENA, files2);
                        }
                    }
                    fclose(files2);
                    write(fd4[1],dest, strlen(dest)+1);
                    
                exit(0);
            }
            // genero el txt final
            strcat(final2, final);
            printf("resultado: %s\n", final2);

                end = fopen("descifrado.txt", "w");

                if (end != NULL){
                    fprintf(end, "\n%s", final2);

                    fclose(end);
                }
            break;
        default:
            break;
        }

    return 0;
}