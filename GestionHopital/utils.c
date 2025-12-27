#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"

void viderBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void pause_ecran() {
    printf("\nAppuyez sur Entrée pour continuer...");
    viderBuffer();
    getchar();
}

void obtenirDateHeureActuelle(char* date, char* heure) {
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    
    sprintf(date, "%02d/%02d/%04d", 
            tm_info->tm_mday, 
            tm_info->tm_mon + 1, 
            tm_info->tm_year + 1900);
    
    sprintf(heure, "%02d:%02d", 
            tm_info->tm_hour, 
            tm_info->tm_min);
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}