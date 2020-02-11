#include "../lib/parseArguments.h"

int searchOption(int argc, char* argv[], char* longOption,char* shortOption){

    for(int i = 0; i<argc; i++){
    if(strcmp(argv[i],longOption) == 0 || strcmp(argv[i],shortOption) == 0)
        return i;
    }

    return -1;
}