#ifndef READWRITE_H
#define READWRITE_H

#include "myStruct.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*Legge la n-esima riga passata come parametro dal file passato come parametro*/
char* read_nth_line(int n, char* path);

/*legge il file passato come parametro e ritorna il testo*/
char* read_file(char *path);

/*Conta le righe totali di un file*/
int countlines(char* path);

/*scrive su output file le informazioni di wordInfo*/
void writeReport(char* outputFile, wordInfo* wInfo);

char* parseWords(int isTruncate, char* word);

char* truncateLastChar(char** word);
#endif