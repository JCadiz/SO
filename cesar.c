#include <stdio.h>  // printf
#include <stdlib.h>
#include <ctype.h>  // isalpha, isupper
#include <string.h> // strcspn
#define LONGITUD_ALFABETO 26
#define INICIO_ALFABETO_MAYUSCULAS 65
#define INICIO_ALFABETO_MINUSCULAS 97
// Puedes ampliarlo si gustas, recuerda poner uno más aparte de la cantidad que
// escaneas
#define MAXIMA_LONGITUD_CADENA 5000
#define MOD(i, n) (i % n + n) % n // Calcular módulo positivo, gracias a

const char *alfabetoMinusculas = "abcdefghijklmnopqrstuvwxyz",
           *alfabetoMayusculas = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

void cifrar(char *destino, int posiciones, char path[]);
void descifrar(char *destino, int posiciones, char path[]);
// Obtener el valor entero de un carácter:
int ord(char c); // https://parzibyte.me/blog/2018/12/11/ord-chr-c/

void cifrar(char *destino, int rotaciones,char path[]) {

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

  /*Recorrer cadena*/
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

  printf("El mensaje cifrado es: \n%s\n", destino);

    archivo2 = fopen("CifradoCesar.txt", "w");

     if (archivo2 != NULL){
        fprintf(archivo2, "\n%s", destino);

        fclose(archivo2);
    }
}

void descifrar(char *destino, int rotaciones, char path[]) {

    FILE *archivo3, *archivo4;

    char mensaje[MAXIMA_LONGITUD_CADENA];
    
    archivo3 = fopen(path, "r");
    
    if (archivo3 != NULL){
        while(!feof(archivo3)){
            fgets(mensaje, MAXIMA_LONGITUD_CADENA, archivo3);

            printf("El mensaje original es: \n%s\n", mensaje);
            printf("\n");
        }
    }
  /*Recorrer cadena*/
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


  printf("El mensaje descifrado es: \n%s\n", destino);

    archivo4 = fopen("DesifradoCesar.txt", "w");

     if (archivo4 != NULL){
        fprintf(archivo4, "\n%s", destino);

        fclose(archivo4);
    }
}

int ord(char c) 
{
    return (int)c; 
}

int main(void) {
  // El original, el cifrado y luego el descifrado
  char mensajeCifrado[MAXIMA_LONGITUD_CADENA], mensajeDescifrado[MAXIMA_LONGITUD_CADENA];
  
  //descifrar(mensajeCifrado, mensajeDescifrado, 2);

  //printf("El mensaje descifrado es: \n%s\n", mensajeDescifrado);

  int i=1, opcion=0;

    while (i != 0){
        printf("Cifrado Cesar \n");
        printf("\n");
        printf("1. Crifrar \n");
        printf("2. Descrifrar \n");
        printf("3. terminar \n");
        scanf("%d", &opcion);
        printf("\n");

        switch (opcion)
        {
        case 1:
            printf("Eligio Cifrar \n");
            printf("\n");
            cifrar( mensajeCifrado, 2, "archivo.txt");
            printf("\n");
            break;
        case 2:
            printf("Eligio Descifrar \n");
            printf("\n");
            descifrar(mensajeDescifrado, 2,"CifradoCesar.txt");
            printf("\n");
            break;
        default:
            i=0;
            break;
        }
        
    }

  return 0;
}

