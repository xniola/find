#include "../lib/readwrite.h"

char* read_nth_line(int n, char* path){
    FILE* file = fopen(path, "r");

    if(file == NULL){
        printf("Il file non esiste.\n");
    }
    
    char line[256];
    char* result = malloc(256);
    int i = 0;
    while (fgets(line, sizeof(line), file)) {
        i++;
        if(i == n ){
          strcat(result,line);
          return result; 
        }
    }
    fclose(file);
}


char* read_file(char *path){
    char *source = NULL;
    FILE *fp = fopen(path, "r");
    
        if(fp == NULL){
            printf("Il file non esiste\n");
            exit(0);
        }
        
            //Vado alla fine del file 
             if (fseek(fp, 0L, SEEK_END) == 0) {
                // Ottengo la dimensione del file
                 long bufsize = ftell(fp);
        if (bufsize == -1) {
            fprintf(stderr,"Il file non esiste");
            exit(0);
        }

        // Alloco un buffer dalla dimensione del file 
        source = malloc(sizeof(char) * (bufsize + 1));

        //Ritorno all'inizio del file 
        if (fseek(fp, 0L, SEEK_SET) != 0) {
            printf("Errore");
            exit(0);
         }

        //Leggo l'intero file e lo metto in memoria 
        size_t newLen = fread(source, sizeof(char), bufsize, fp);
        if ( ferror( fp ) != 0 ) {
            fputs("Errore durante la lettura del file", stderr);
        } else {
            source[newLen++] = '\0';
        }
    }
    return source;
    fclose(fp);

}

int countlines(char* path){
    FILE *file = fopen(path, "r");

    if(file == NULL){
        printf("Il file '%s' non esiste\n",path);
        exit(0);
    }

    int count = 1;
    for (char c = getc(file); c != EOF; c = getc(file)) 
        if (c == '\n')
        count++; 

   return count;
}


void writeReport(char* outputFile, wordInfo* wInfo){
    FILE *fout = fopen(outputFile, "a");

    if(fout == NULL){
        fprintf(stderr, "Il file di output non esiste\n");
    }
    
    while(wInfo != NULL){
        fprintf(fout,"WORD %s\r\n",wInfo->name);
        fprintf(fout,"TOTAL OCCURRENCES %i\r\n",getTotalOccurrences(*wInfo,wInfo->name));
       
       while(wInfo->fileInfo != NULL){
        fprintf(fout,"FILE %s\r\n",wInfo->fileInfo->file_path);
        fprintf(fout,"Occorrenze: %i\n",wInfo->fileInfo->occurrences);
        fprintf(fout,"POSITION\r\n");
         while (wInfo->fileInfo->positions != NULL) { 
            fprintf(fout,"%i %i\r\n", wInfo->fileInfo->positions->line,
                                    wInfo->fileInfo->positions->posChar);
            wInfo->fileInfo->positions = wInfo->fileInfo->positions->next; 
             
         }
         wInfo->fileInfo = wInfo->fileInfo->next;
       }
    wInfo = wInfo->next;
    fprintf(fout,"\r\n");
  }
fclose(fout);
}

char* truncateLastChar(char** word){
   char* new = malloc(64);
   char buf[64];
   strcpy(buf,*word);
   buf[strlen(buf)-1] = '\0';
   strcpy(new,buf);
   return new;
}

char* parseWords(int isTruncate, char* word){
    char* new = malloc(32);
    
    if(isTruncate == 1)
        new = truncateLastChar(&word);
    else 
        strcpy(new,word);

    return new;
}