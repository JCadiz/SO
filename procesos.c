#include <stdio.h> 
#include <stdlib.h>
#include <string.h> // isalpha, isupper
#include <ctype.h> // strcspn
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define LONGITUD_ALFABETO 26
#define INICIO_ALFABETO_MAYUSCULAS 65
#define INICIO_ALFABETO_MINUSCULAS 97

#define MAXIMA_LONGITUD_CADENA 5000

#define MOD(i, n) (i % n + n) % n // Calcular módulo positivo, gracias a

const char *alfabetoMinusculas = "abcdefghijklmnopqrstuvwxyz",
           *alfabetoMayusculas = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

void cifradoCesar(char *destino, int posiciones, char path[], int pid, int inicio, int fin, int longitud);
void descifradoCesar(char *destino, int posiciones, char path[], int pid, int inicio, int fin, int longitud);
void cifradoMurcielago(char path[], int pid);
void descifradoMurcielago(char path[], int pid);
// Obtener el valor entero de un carácter:
int ord(char c); // https://parzibyte.me/blog/2018/12/11/ord-chr-c/

//Funcion para cifrado cesar
void cifradoCesar(char *destino, int rotaciones, char path[], int pid, int inicio, int fin,int longitud){

    FILE *archivo, *archivo2;
    int tam=0;
    tam = fin - inicio;
    char mensaje[longitud], auxmensaje[tam];
    char guardar;
    
    archivo = fopen(path, "r");
    
    if (archivo != NULL){
        while(!feof(archivo)){
            fgets(mensaje, MAXIMA_LONGITUD_CADENA, archivo);

            printf("El mensaje original es: \n%s\n", mensaje);
            printf("\n");
        }
    }
    fclose(archivo);

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

    printf("El mensaje cifrado Cesar es: \n%s\n", destino);

    archivo2 = fopen("Cifrado.txt", "w");

     if (archivo2 != NULL){
        fprintf(archivo2, "\n%s", destino);

        fclose(archivo2);
    }

}

// cifrar murcielago en las ramas
void cifradoMurcielago(char path[], int pid){

    FILE *archivo, *archivo2;

    char mensaje[MAXIMA_LONGITUD_CADENA];
    
    archivo = fopen(path, "r");
    
    if (archivo != NULL){
        while(!feof(archivo)){
            fgets(mensaje, MAXIMA_LONGITUD_CADENA, archivo);

            printf("El mensaje original es: \n%s\n", mensaje);
            printf("\n");
        }
    }

    fclose(archivo);

    for (int i=0; i<=100; i++) {
    
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

    printf("El mensaje cifrado con Murcielago y Cesar es: \n%s\n", mensaje);

    archivo2 = fopen("Cifrado.txt", "w");

     if (archivo2 != NULL){
        fprintf(archivo2, "\n%s", mensaje);

        fclose(archivo2);
    }
}

//Funcion para Descifrar el archivo
void descifradoCesar(char *destino, int rotaciones, char path[], int pid, int inicio, int fin, int longitud){
    
    FILE *archivo3, *archivo4;

    char mensaje[MAXIMA_LONGITUD_CADENA];
    
    archivo3 = fopen(path, "r");
    archivo4= fopen("Descifrado.txt", "w");
    
    if (archivo3 != NULL){
        while(!feof(archivo3)){
            fgets(mensaje, MAXIMA_LONGITUD_CADENA, archivo3);
            printf("El mensaje original es: \n%s\n", mensaje);
            printf("\n");
        }
    }

    fclose(archivo3);

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
    
     printf("Texto Descrifrado: \n%s\n", destino);

     if (archivo4 != NULL){
        fprintf(archivo4, "\n%s", destino);

        fclose(archivo4);
    }

}
// descrifrar murcielago
void descifradoMurcielago(char path[], int pid){

    FILE *archivo3, *archivo4;

    char destino[MAXIMA_LONGITUD_CADENA];
    
    archivo3 = fopen(path, "r");
    archivo4= fopen("Descifrado.txt", "w");
    
    if (archivo3 != NULL){
        while(!feof(archivo3)){
            fgets(destino, MAXIMA_LONGITUD_CADENA, archivo3);
            printf("El mensaje original es: \n%s\n", destino);
            printf("\n");
        }
    }

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

    printf("Texto Descrifrado: \n%s\n", destino);

     if (archivo4 != NULL){
        fprintf(archivo4, "\n%s", destino);

        fclose(archivo4);
    }

}

int ord(char c) 
{
    return (int)c; 
}

int main(int argc, char *argv[]) {
    int i=1, opcion=0, longitud=0, inicio=0, fin=0, validar = 2;
    char mensajeCifrado[MAXIMA_LONGITUD_CADENA], mensajeDescifrado[MAXIMA_LONGITUD_CADENA];
    int nprocesos= atoi(argv[1]);
    int numeroh = nprocesos * nprocesos;
    int pidr = 0, pidh = 0; // tomar los pid de las ramas y hojas
    int aux=0; // auxiliar para recorrer vector de los inicios y fin de cada mensaje para las hojas 
    int begin[numeroh], end[numeroh]; // vector para guardar los inicios y fin de cada mensaje
    pid_t ramas[nprocesos], hojas[numeroh] ,wpid;
    FILE *main;

    char cod[MAXIMA_LONGITUD_CADENA];
    
    main = fopen("archivo.txt", "r");
    
    if (main != NULL){
        while(!feof(main)){
            fgets(cod, MAXIMA_LONGITUD_CADENA, main);
        }
        longitud = strlen(cod);
        //printf("la longitud de la mensaje es: %d\n",longitud);
        //printf("\n");
    }
    fclose(main);

    if (longitud % 2 == 0){
        //printf("el numero es par: %d\n",(longitud % 2));
        validar = 0; // es par
    }else {
        //printf("el numero es impar: %d\n",(longitud % 2));
        validar = 1; // es impar
    }
    
    //calculo de los inicios y final para cada hijo
    for (int k=0; k < numeroh; k++){
        if(validar == 1){ // es que la longitud del mensaje es impar
            if(k == (numeroh-1)){
                fin = longitud;
                inicio= k * (longitud / numeroh);
                //printf("inicio es: %d\n", inicio);
                //printf("final ultimo: %d\n", fin);
                //printf("\n");
                begin[k]=inicio;
                end[k]=fin;
            }else{
                fin = ((k+1) * (longitud / numeroh))-1;
                inicio= k * (longitud / numeroh);
                //printf("inicio es: %d\n", inicio);
                //printf("final es: %d\n", fin);
                //printf("\n");
                begin[k]=inicio;
                end[k]=fin;
            }
        }else{
            if(k == (numeroh-1)){
                fin = longitud;
                inicio= k * (longitud / numeroh);
                //printf("inicio es: %d\n", inicio);
                //printf("final ultimo: %d\n", fin);
                //printf("\n");
                begin[k]=inicio;
                end[k]=fin;
            }else{
                fin = ((k+1) * (longitud / numeroh))-1;
                inicio= k * (longitud / numeroh);
                //printf("inicio es: %d\n", inicio);
                //printf("final es: %d\n", fin);
                //printf("\n");
                begin[k]=inicio;
                end[k]=fin;
            }
        }
    }

    for (int j=0; j< nprocesos; j++){
        //hijos que seran las ramas
        if ( (ramas[j] = fork() ) == 0){
            //printf("Rama: soy el hijo %d, mi padre es %d\n",getpid(),getppid());

            pidr= getpid();
            
            for(int z =0; z< nprocesos; z ++){
                if ((hojas[z] = fork() ) == 0){ //hijos que seran hojas
                    //printf("hojas: soy el hijo %d, mi padre es %d\n",getpid(),getppid());
                    pidh =getpid();
                    cifradoCesar(mensajeCifrado, 2 , "archivo.txt", pidh, begin[aux], end[aux], longitud);
                    aux++;
                    exit(0);
                }
            }


            exit(0);
        }
        if (ramas[j] > 0){
            //estoy en el primer papa
            
        }
    }
    
    return 0;
}