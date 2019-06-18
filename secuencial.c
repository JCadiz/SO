#include <stdio.h> 
#include <stdlib.h>
#include <string.h> // isalpha, isupper
#include <ctype.h> // strcspn
#include <sys/time.h> 
#include <math.h> 

#define LONGITUD_ALFABETO 26
#define INICIO_ALFABETO_MAYUSCULAS 65
#define INICIO_ALFABETO_MINUSCULAS 97

#define MAXIMA_LONGITUD_CADENA 5000

#define MOD(i, n) (i % n + n) % n // Calcular módulo positivo, gracias a

const char *alfabetoMinusculas = "abcdefghijklmnopqrstuvwxyz",
           *alfabetoMayusculas = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

void cifrado(char *destino, int posiciones, char path[]);
void descifrado(char *destino, int posiciones, char path[]);
// Obtener el valor entero de un carácter:
int ord(char c); // https://parzibyte.me/blog/2018/12/11/ord-chr-c/

int tomartiempo(){
    struct timeval t;
    int dt;
    gettimeofday(&t, (struct timezone*)0);
    dt = (t.tv_sec)*1000000 + t.tv_usec;
    return dt;
}

//Funcion para leer archivo
void cifrado(char *destino, int rotaciones, char path[]){

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

    printf("Texto Encriptado en Murcielago es: \n%s\n", mensaje);
    printf("\n");
    printf("Ahora se Cifra por el metodo Cesar \n");
    printf("\n");

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

    printf("El mensaje cifrado con Murcielago y Cesar es: \n%s\n", destino);

    archivo2 = fopen("Cifrado.txt", "w");

     if (archivo2 != NULL){
        fprintf(archivo2, "\n%s", destino);

        fclose(archivo2);
    }


}

//Funcion para Descifrar el archivo
void descifrado(char *destino, int rotaciones, char path[]){
    
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
    printf("El mensaje descifrado por Cesar es: \n%s\n",destino);
    printf("\n");
    printf("Ahora se descifrar por el metodo Murcielago \n");
    printf("\n");


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
    int i=1, opcion=0;
    int tiempoinicial, tiempofinal;
    char mensajeCifrado[MAXIMA_LONGITUD_CADENA], mensajeDescifrado[MAXIMA_LONGITUD_CADENA];

        switch (*argv[1])
        {
        case 'c':
            printf("Eligio Cifrar \n");
            printf("\n");
            tiempoinicial = tomartiempo();
            cifrado( mensajeCifrado, 2, "archivo.txt");
            tiempofinal = tomartiempo();
            printf("Tiempo de ejecucion: %8d", tiempofinal - tiempoinicial);

            printf("\n");
            break;
        case 'd':
            printf("Eligio Descifrar \n");
            printf("\n");
            tiempoinicial = tomartiempo();
            descifrado(mensajeDescifrado, 2,"Cifrado.txt");
            tiempofinal = tomartiempo();
            printf("Tiempo de ejecucion: %8d", tiempofinal - tiempoinicial);
            printf("\n");
            break;
        default:
            i=0;
            break;
        }

    return 0;
}