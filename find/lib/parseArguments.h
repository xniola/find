#ifndef PARSEAGRUMENTS_H
#define PARSEARGUMENTS_H

#include <string.h>

/*Cerca se l'opzione <code>option<code> sia presente in argv*/ 
int searchOption(int argc, char* argv[], char* longOption,char* shortOption);


#endif