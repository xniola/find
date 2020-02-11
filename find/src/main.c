#include "../lib/myStruct.h"
#include "../lib/kmpalgo.h"
#include "../lib/readwrite.h"
#include "../lib/parseArguments.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h> 


void parsePositions(int initialLine, int finalLine, int* fileFlag, char* reportFile, char* file, char* word){
   for(int i = initialLine; i<= finalLine; i++){
         char* line = read_nth_line(i,reportFile);
         if(strstr(line,"FILE ") != NULL){
            if(strstr(line+5,file) != NULL){
                  *fileFlag = 1;
                  i = i+3;
                  if(strstr(read_nth_line(i,reportFile),"0 0") != NULL)
                     printf("La parola %s non occorre mai nel file indicato\n",word);
                  else{
                  int flag = 0;
                  printf("Posizioni della parola '%s' nel file %s:\n",word,file);
                  while(flag == 0){
                     if(strcmp(read_nth_line(i,reportFile),"\r\n") == 0 || strstr(read_nth_line(i,reportFile),"FILE") != NULL){
                        flag = 1;
                     }else{
                     
                     printf("%s",read_nth_line(i,reportFile));
                     i = i+1;
                     }
                  }
                  }
            }
         }
   }
}

/*Individua il numero di riga nel dove occorre la word e il numero di riga finale delle sue info associate*/
void parseReportFile(int* initialLine, int* finalLine, char* reportFile, char* word){
   for(int i = 1; i<=countlines(reportFile); i++){
        char* line = read_nth_line(i,reportFile);
        if(strstr(line,word) != NULL){
         // la word richiesta è contenuta nel file.
         *initialLine = i;
         break;
        }
   }
   int flag = 0; // indica che un'ultima riga è stata trovata
   for(int i = *initialLine+1; i<=countlines(reportFile);i++){
      char* line = read_nth_line(i,reportFile);
      if(*initialLine != 0 && strstr(line, "WORD ") != NULL){
         // ultima riga delle informazioni relative alla parola cercata
         flag = 1;
         *finalLine = i;
         break;
      }
    }
    if(flag == 0){
       *finalLine = countlines(reportFile);
    }
}

void printOccurrences(int* initialLine, int* finalLine, char* reportFile, char* word,int occ){
   int flag = 0; // indica se almeno un file è stato trovato
   for(int i = *initialLine; i<*finalLine; i++){
        char* line = read_nth_line(i,reportFile);
        if(strstr(line,"Occorrenze: ")!= NULL){
           // leggo il numero scritto in questa riga
           char* occurrences = line;
           occurrences = occurrences+12;
           char* trunc = truncateLastChar(&occurrences);
           int num = atoi(occurrences);
           if(num >= occ){
           // se il numero letto è maggiore o uguale a quello richiesto allora lo stampo
           flag = 1;
           char* file = read_nth_line(i-1,reportFile);
           printf("FILE: %s",file+5);
           }
        }
     }
     if(flag == 0){
        printf("Nessun file contiene la parola '%s' per un numero di volte pari a %i\n",word,occ);
     }
}



int main (int argc, char* argv[]) {

   //flag delle opzioni
   int output = 0;
   int exclude = 0;
   int verbose = 0;
   int listOfFile = 0;
   int listOfPositions = 0;

   wordInfo* current = malloc(sizeof(wordInfo));
   initWordInfo(current);
   entryFiles* entry = malloc(sizeof(entryFiles));
   initEntryFile(entry);
   entryWords* entryWords = malloc(sizeof(entryWords));
   initEntryWords(entryWords);

   if(searchOption(argc,argv,"--output","-o") != -1)
      output = 1;
   
   if(searchOption(argc,argv,"--exclude","-e") != -1)
      exclude = 1;
   
   if(searchOption(argc,argv,"--verbose","-v") != -1)
      verbose = 1;

   if(searchOption(argc,argv,"--report","--report") != -1 && (argc == 6 || argc == 5))
      listOfFile = 1;

   if(searchOption(argc,argv,"--file","--file") != -1)
      listOfPositions = 1;

   char* outputFile = argv[searchOption(argc,argv,"--output","-o")+1];
   char* inputFile = argv[4]; //es. parameters/inputFile.txt
   char* inputWords = argv[2]; // es. parameters/inputWords.txt

  
 //generazione del report
  if(listOfFile == 0 && listOfPositions == 0){ 
   populateEntryWords(&entryWords,inputWords);
   
   if(exclude == 1){
      populateEntryFile(&entry,inputFile);
      removeExtensions(&entry,argv[searchOption(argc,argv,"--exclude","-e")+1]);
      }
   else
      populateEntryFile(&entry,inputFile);

   
   if(verbose == 1)
      processWordInfoVerbose(&current,entryWords,entry);
   else
      processWordInfo(&current,entryWords,entry);

   if(output == 1)
      writeReport(outputFile,current);
   else
      printWordInfo(current);
  }

  // analisi dei report
  else{
     if(argc == 5){ // stampa la lista dei file con occorrenza di default 1
     int initialLine = 0;
     int finalLine = 0;
     char* reportFile = argv[2];
     char* word = argv[4];
     parseReportFile(&initialLine,&finalLine,reportFile,word); // ora ho riga iniziale e finale
     printOccurrences(&initialLine,&finalLine,reportFile,word,1);
     }
     if(argc == 6){ //stampa la lista dei file con occorrenza indicata a linea di comando
     char* occurrences = argv[5];
     char* word = argv[4];
     char* reportFile = argv[2];
     int occ = atoi(occurrences);
     int initialLine = 0;
     int finalLine = 0;
     parseReportFile(&initialLine,&finalLine,reportFile,word); // ora ho riga iniziale e finale
     if(initialLine == 0)
      printf("La parola '%s' non è presente nel file indicato\n",word);
     else
      printOccurrences(&initialLine,&finalLine,reportFile,word,occ);
     }
     
     //stampa la lista delle posizioni
     else{ // find --report|-r <reportfile> --show <word> --file <file>
      char* reportFile = argv[2];
      char* word = argv[4];
      char* file = argv[6];
      int initialLine = 0;
      int finalLine = 0;
      int fileFlag = 0;
      parseReportFile(&initialLine,&finalLine,reportFile,word);
      if(initialLine == 0)
         printf("La parola %s non esiste nel report file indicato\n",word);
      else{
         parsePositions(initialLine,finalLine,&fileFlag,reportFile,file,word);
         if(fileFlag == 0)
            printf("Il file indicato non esiste\n");
      }
      }
     }
  
   free(current);
   free(entryWords);
   free(entry);
   output = 0;
   exclude = 0;
   verbose = 0;
   listOfFile = 0;
   listOfPositions = 0;
   return 0;
   
}
