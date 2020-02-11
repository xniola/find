#ifndef KMPALGO_H
#define KMPALGO_H

#include "myStruct.h"
#include "readwrite.h"

#include <stdlib.h>
#include <string.h>

/* Cerca una stringa <pat> in un testo <txt> */
void kmp_algo(char *pat, char *txt,wordInfo** wInfo);

#endif