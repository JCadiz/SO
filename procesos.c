#include <stdio.h> 
#include <stdlib.h>
#include <string.h> // isalpha, isupper
#include <ctype.h> // strcspn
#include <sys/types.h>
#include <signal.h>
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
    char mensaje[longitud];
    char guardar[tam];
    int cont=0;
    char archivoid[4]="", aux[4];
    //sleep(5);
    //printf(" lo que tiene pid %d\n",pid);
    sprintf(aux,"%d",pid);
    strcat(archivoid, aux);
    strncat(archivoid,".txt",5);
    //printf("%s\n",archivoid);
    //archivoid= NULL;
    
    archivo = fopen(path, "r");
    fseek(archivo,inicio, SEEK_CUR);
    if (archivo != NULL){
        while(!feof(archivo)){
            fgets(mensaje, MAXIMA_LONGITUD_CADENA, archivo);
            //printf("El mensaje original es: \n%s\n", mensaje);
            //printf("\n");
        }
    }
    fclose(archivo);

    //printf("inicio: %d\n",inicio);
    //printf("fin: %d\n",fin);
    
    //escribo en guardar los caracteres que le toca a cada hoja
    for (int j=0; j <= fin; j++){
        
        guardar[j]= mensaje[j];
     
    }

    printf("lo que tiene guardar es: %s\n",guardar);

    // cifrado cesar aqui
    int i = 0;
    while (guardar[i]) {
        char caracterActual = guardar[i];
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

    //printf("El mensaje cifrado en los hojas es: \n%s\n", destino);

    archivo2 = fopen(archivoid, "w");

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

/*void incrementar (){
    aux2++;
}*/

int main(int argc, char *argv[]) {

    int i=1, opcion=0, longitud=0, inicio=0, fin=0, validar = 2, partes = 0, cont=0;
    char mensajeCifrado[MAXIMA_LONGITUD_CADENA], mensajeDescifrado[MAXIMA_LONGITUD_CADENA];
    int nprocesos= atoi(argv[1]);
    int numeroh = nprocesos * nprocesos;
    int pidr = 0, pidh = 0; // tomar los pid de las ramas y hojas
    int *aux2=0; // auxiliar para recorrer vector de los inicios y fin de cada mensaje para las hojas 
    pid_t pid;
    FILE *main ;    

    char cod[MAXIMA_LONGITUD_CADENA];
    //glob_var = mmap(NULL, sizeof *glob_var, PROT_READ | PROT_WRITE, 
                    //MAP_SHARED | MAP_ANON, -1, 0);
    

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

    partes = longitud / numeroh;
    
    for(int j=0; j < nprocesos; j++){
        for(int k=0; k < nprocesos; k++){
            if(cont == numeroh-1){
                inicio = partes * cont;
                fin = longitud; 
                cont++;
            }else{
                inicio = partes * cont;
                fin = (partes * (cont+1)) - 1; 
                cont++;
            }
            //printf("cont : %d\n",cont);

            pid= fork();

            if ( pid == 0){
                pidh=getpid();
                cifradoCesar(mensajeCifrado, 2 , "archivo.txt", pidh, inicio, fin, longitud);
                //exit(0);
            }else {
                //wait(NULL);
                exit(0);
            }
        }
        // aqui hago cifrado murcielago
    }
    
    return 0;
}