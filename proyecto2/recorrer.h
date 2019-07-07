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

void eliminar_coreP(char core[], char path[]);
void eliminar_core(char core[], char path[], char archivo[]);
void recorrer(DIR *d, char path[],char nombre[]);
void recorrer_sinFile(DIR *d, char path[]);