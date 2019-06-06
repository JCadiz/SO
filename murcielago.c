#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#define MAXIMA_LONGITUD_CADENA 5000

//Funcion para cifrar archivo
void cifrado(char path[]){

    FILE *archivo, *archivo2;

    char cadena[100];
    
    archivo = fopen(path, "r");
    
    if (archivo != NULL){
        while(!feof(archivo)){
            fgets(cadena, 100, archivo);

            printf("cadena: %s\n", cadena);
        }
    }

    fclose(archivo);

    for (int i=0; i<=100; i++) {
    
        switch (cadena[i]) {
            {
                case 'm':
                cadena[i]= 48;
                break;
            }
            {
                case 'u':
                cadena[i]= 49;
                break;
            }
            {
                case 'r':
                cadena[i]= 50;
                break;
            }
            {
                case 'c':
                cadena[i]= 51;
                break;
            }
            {
                case 'i':
                cadena[i]= 52;
                break;
            }
            {
                case 'e':
                cadena[i]= 53;
                break;
            }
            {
                case 'l':
                cadena[i]= 54;
                break;
            }
            {
                case 'a':
                cadena[i]= 55;
                break;
            }
            {
                case 'g':
                cadena[i]= 56;
                break;
            }
            {
                case 'o':
                cadena[i]= 57;
                break;
            }
            default:
            cadena[i]= cadena[i];
        }
    }

    printf("Texto Encriptado: \n%s\n", cadena);

    archivo2 = fopen("CifradoM.txt", "w");

     if (archivo2 != NULL){
        fprintf(archivo2, "\n%s", cadena);

        fclose(archivo2);
    }


}

//Funcion para descifrar archivo
void descifrado(char path[]){
    
    FILE *archivo3, *archivo4;

    char cadena2[100];
    
    archivo3 = fopen(path, "r");
    archivo4= fopen("DescifradoM.txt", "w");
    
    if (archivo3 != NULL){
        while(!feof(archivo3)){
            fgets(cadena2, 100, archivo3);

            printf("cadena: %s\n", cadena2);
        }
    }

    fclose(archivo3);

    for (int i=0; i<=100; i++) {
    
        switch (cadena2[i]) {
            {
                case '0':
                cadena2[i]= 109;
                break;
            }
            {
                case '1':
                cadena2[i]= 117;
                break;
            }
            {
                case '2':
                cadena2[i]= 114;
                break;
            }
            {
                case '3':
                cadena2[i]= 99;
                break;
            }
            {
                case '4':
                cadena2[i]= 105;
                break;
            }
            {
                case '5':
                cadena2[i]= 101;
                break;
            }
            {
                case '6':
                cadena2[i]= 108;
                break;
            }
            {
                case '7':
                cadena2[i]= 97;
                break;
            }
            {
                case '8':
                cadena2[i]= 103;
                break;
            }
            {
                case '9':
                cadena2[i]= 111;
                break;
            }
            default:
            cadena2[i]= cadena2[i];
        }
    }

     printf("Texto Descrifrado: \n%s\n", cadena2);

     if (archivo4 != NULL){
        fprintf(archivo4, "\n%s", cadena2);

        fclose(archivo4);
    }

}

int main(void) {
    int i=1, opcion=0;

    while (i != 0){
        printf("Cifrado Murcielago \n");
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
            cifrado("archivo.txt");
            printf("\n");
            break;
        case 2:
            printf("Eligio Descifrar \n");
            printf("\n");
            descifrado("CifradoM.txt");
            printf("\n");
            break;
        default:
            i=0;
            break;
        }
        
    }

    return 0;
}