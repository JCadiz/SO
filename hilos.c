#include <stdio.h> 
#include <stdlib.h>
#include <string.h> // isalpha, isupper
#include <ctype.h> // strcspn
#include <sys/types.h>
#include <sys/mman.h>
#include <pthread.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>

#define LONGITUD_ALFABETO 26
#define INICIO_ALFABETO_MAYUSCULAS 65
#define INICIO_ALFABETO_MINUSCULAS 97

#define MAXIMA_LONGITUD_CADENA 5000

#define MOD(i, n) (i % n + n) % n // Calcular módulo positivo, gracias a

static int *glob_var; 
const char *alfabetoMinusculas = "abcdefghijklmnopqrstuvwxyz",
           *alfabetoMayusculas = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

//declaracion del struct
struct param{
        int rotaciones;
        char *path;
        int idhilo;
        int begin;
        int end;
        int longitud;
    };
    typedef struct param struct1;

struct descifrar{
        int rotaciones;
        int idhilo;
    };
    typedef struct descifrar struct2;

int ord(char c); // https://parzibyte.me/blog/2018/12/11/ord-chr-c/


int tomartiempo(){
    struct timeval t;
    int dt;
    gettimeofday(&t, (struct timezone*)0);
    dt = ((t.tv_sec)*1000000 + t.tv_usec);
    return dt;
}

//Funcion para cifrado cesar
void cifrado(void* argumento){

    struct1 *b;
    b=(struct1*)argumento;

    FILE *archivo, *archivo2;
    int tam=0;
    tam = (b->end) - (b->begin);
    char mensaje[b->longitud], destino[b->longitud],auxmensaje[tam];
    char guardar[tam];
    int cont=0;
    char archivoid[15], aux[15];

    sprintf(aux,"%d",b->idhilo);
    strcat(archivoid, aux);
    strncat(archivoid, ".txt",15);
    //printf("%s\n",archivoid);
    
    archivo = fopen(b->path, "r");
    fseek(archivo,b->begin, SEEK_CUR);
    if (archivo != NULL){
        while(!feof(archivo)){
            fgets(mensaje, MAXIMA_LONGITUD_CADENA, archivo);
            //printf("El mensaje original es: \n%s\n", mensaje);
            //printf("\n");
        }
    }
    fclose(archivo);

    //printf("inicio: %d\n", b->begin);
    //printf("fin: %d\n", b->end);

    //escribo en guardar los caracteres que le toca a cada hoja
    for (int j=0; j < b->end; j++){
        if(j <= b->end){
            guardar[j]= mensaje[j];
        } 
    }
    //printf("loque tiene guardar es \n%s\n",guardar);

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
                                b->rotaciones) %
                                LONGITUD_ALFABETO];
        } else {

        destino[i] =
            alfabetoMinusculas[(posicionOriginal - INICIO_ALFABETO_MINUSCULAS +
                                b->rotaciones) %
                                LONGITUD_ALFABETO];
        }
        i++;
    }

    printf("El mensaje cifrado con cesar es: \n%s\n", destino);

    // ahora cifrado murcielago

    for (int i=0; i<=100; i++) {
    
        switch (destino[i]) {
            {
                case 'm':
                destino[i]= 48;
                break;
            }
            {
                case 'u':
                destino[i]= 49;
                break;
            }
            {
                case 'r':
                destino[i]= 50;
                break;
            }
            {
                case 'c':
                destino[i]= 51;
                break;
            }
            {
                case 'i':
                destino[i]= 52;
                break;
            }
            {
                case 'e':
                destino[i]= 53;
                break;
            }
            {
                case 'l':
                destino[i]= 54;
                break;
            }
            {
                case 'a':
                destino[i]= 55;
                break;
            }
            {
                case 'g':
                destino[i]= 56;
                break;
            }
            {
                case 'o':
                destino[i]= 57;
                break;
            }
            default:
            destino[i]= destino[i];
        }
    }

    archivo2 = fopen(archivoid, "w");

     if (archivo2 != NULL){
        fprintf(archivo2, "\n%s", destino);

        fclose(archivo2);
    }

    pthread_exit(NULL);
}

// cifrar murcielago en las ramas

//Funcion para Descifrar el archivo
void descifrado(void *argumento2){
    struct1 *b;
    b=(struct1*)argumento2;
    FILE *archivo3, *archivo4;
    char archivoid[15], aux[15];
    char mensaje[MAXIMA_LONGITUD_CADENA], destino[MAXIMA_LONGITUD_CADENA],auxmensaje[MAXIMA_LONGITUD_CADENA];
    int longitud=0;

    archivo3 = fopen(archivoid, "r");
        if (archivo3 != NULL){
            while(!feof(archivo3)){
                fgets(mensaje, MAXIMA_LONGITUD_CADENA, archivo3);
                printf("El mensaje a descifrar es: \n%s\n", mensaje);
                printf("\n");
            }
            longitud = strlen(mensaje);
        }
        fclose(archivo3);

    //aqui descifro murcielago
    for (int i=0; i<=longitud; i++) {
    
        switch (mensaje[i]) {
            {
                case '0':
                mensaje[i]= 109;
                break;
            }
            {
                case '1':
                mensaje[i]= 117;
                break;
            }
            {
                case '2':
                mensaje[i]= 114;
                break;
            }
            {
                case '3':
                mensaje[i]= 99;
                break;
            }
            {
                case '4':
                mensaje[i]= 105;
                break;
            }
            {
                case '5':
                mensaje[i]= 101;
                break;
            }
            {
                case '6':
                mensaje[i]= 108;
                break;
            }
            {
                case '7':
                mensaje[i]= 97;
                break;
            }
            {
                case '8':
                mensaje[i]= 103;
                break;
            }
            {
                case '9':
                mensaje[i]= 111;
                break;
            }
            default:
            mensaje[i]= mensaje[i];
        }
    }

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
            posicionOriginal - INICIO_ALFABETO_MAYUSCULAS - b->rotaciones,
            LONGITUD_ALFABETO)];
        } else {
        destino[i] = alfabetoMinusculas[MOD(
            posicionOriginal - INICIO_ALFABETO_MINUSCULAS - b->rotaciones,
            LONGITUD_ALFABETO)];
        }
        i++;
    }
    
     printf("Texto Descrifrado: \n%s\n", destino);
     archivo4 = fopen(archivoid, "w");
     if (archivo3 != NULL){
        fprintf(archivo4, "\n%s", destino);

        fclose(archivo4);
    }

    pthread_exit(NULL);

}

int ord(char c) 
{
    return (int)c; 
}

int main(int argc, char *argv[]) {
    int i=1, longitud=0, inicio=0, fin=0, validar = 2, thread, h, thread2;
    int nhilos= atoi(argv[2]);
    pthread_t hilos[nhilos], tid[nhilos],hilod[nhilos];
    FILE *main;
    char cod[MAXIMA_LONGITUD_CADENA], aux3[15],txt[15],encriptado[MAXIMA_LONGITUD_CADENA];
    char aux2[MAXIMA_LONGITUD_CADENA];
    struct1 *a;
    a=(struct1 *)malloc(sizeof(struct1));
    struct2 *c;
    c=(struct2 *)malloc(sizeof(struct2));
    int tiempoinicial, tiempofinal;

   
    switch (*argv[1])
        {
        case 'c':
            tiempoinicial = tomartiempo();
            printf("Metodo Hilos de Cifrado\n");
            printf("\n");

            main = fopen("archivo.txt", "r");

            if (main != NULL){
                while(!feof(main)){
                    fgets(cod, MAXIMA_LONGITUD_CADENA, main);
                }
                longitud = strlen(cod);
            }
            fclose(main);

            // creacion de los n hilos y su cifrado.
            for(int t=0; t < nhilos; t++){
                // calculo de los inicos y fin
                if(t == (nhilos-1)){
                    fin = longitud;
                    inicio= t * (longitud / nhilos);
                }else{
                    fin = ((t+1) * (longitud / nhilos))-1;
                    inicio= t * (longitud / nhilos);
                }   

                //id del hilo
                tid[t] = t;

                // pasar los valores al struct 
                a->rotaciones = 2;
                a->path="archivo.txt";
                a->idhilo = tid[t];
                a->begin = inicio;
                a->end = fin;
                a->longitud = longitud;
                
                thread = pthread_create(&hilos[t],NULL,(void*)cifrado, (void *) a);
                sleep(5);
                if (thread) {
                    printf("Error, %d\n",thread);
                    exit(-1);
                }
                printf("Creado thread %d, con ID=%ld\n",t,hilos[t]);
                
            }
            
            tiempofinal = tomartiempo();
            printf("Tiempo de ejecucion: %8d", tiempofinal - tiempoinicial);
            // concateno los txt generados
        
            /*for(int i=0; i < nhilos; i++){
                sprintf(aux3,"%ld",tid[i]);
                strcat(txt, aux3);
                strncat(txt, ".txt",15);

                printf("voy aqui");
                
                generado = fopen(txt , "r");

                if (generado != NULL){
                    while(!feof(generado)){
                        fgets(aux2, MAXIMA_LONGITUD_CADENA, generado);
                        //printf("El mensaje original es: \n%s\n", mensaje);
                        //printf("\n");
                    }
                }
                fclose(generado);
                

                strcat(encriptado, aux2);
            }

            cifrado = fopen("cifrado.txt", "w");

            if (cifrado != NULL){
                fprintf(cifrado, "\n%s", encriptado);

                fclose(cifrado);
            }
            
            //printf("%s\n",archivoid);
            */

            printf("\n");
            break;
        case 'd':
            tiempoinicial = tomartiempo();
            printf("Metodo Hilos de Descifrado\n");
            printf("\n");
         
            // creacion de los n hilos y su descifrado.
            for(int z=0; z < nhilos; z++){
                //id del hilo
                tid[z] = z;

                //pasar los valores al struct 
                c->rotaciones = 2;
                c->idhilo = tid[z];
                printf("estoy aqui antes de crear hilo");
                
                thread2 = pthread_create(&hilod[z],NULL,(void*)descifrado, (void *) c);
                sleep(5);
                if (thread2) {
                    printf("Error, %d\n",thread);
                    exit(-1);
                }
                printf("Creado thread %d, con ID=%ld\n",z,hilos[z]);
                
            }

            printf("\n");
            tiempofinal = tomartiempo();
            printf("Tiempo de ejecucion: %8d", tiempofinal - tiempoinicial);
            break;
        default:
            i=0;
            break;
        }
        
    


        
        
    return 0;
}