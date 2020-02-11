#include "../lib/kmpalgo.h"

void failure_table(char *pat, int M, int *T);
 
/*Parametri:
-wInfo, la struttura nel quale salvare le informazioni elaborate
-pat, il pattern da cercare
-path, file regolare nel quale cercare
*/
void kmp_algo(char *pat, char *regular_file,wordInfo** current){
    char* txt = read_file(regular_file);
 
    wordInfo* wInfo = malloc(sizeof(wordInfo));
    initWordInfo(wInfo);

    fileInfo* fInfo = malloc(sizeof(fileInfo));
    initFileInfo(fInfo);

    wordPosition* wPosition = malloc(sizeof(wordPosition));
    initWordPosition(wPosition);

    int numOccorrenze = 0;

    int nbLine = 1; // riga attuale
    int lastnewLinePosition = 0; // posizione del carattere \n
    
    int M = strlen(pat);
    int N = strlen(txt);
 
    int *T = (int *)malloc(sizeof(int)*M);
    int j  = 0;  // indice di pat
 
    failure_table(pat, M, T);
 
    int i = 0; // usato per i loop
    while (i < N){
      if(txt[i] == '\n'){
        lastnewLinePosition = i;
        nbLine++;
      }

      if (pat[j] == txt[i]){
        j++;
        i++;
      }
 
      if (j == M){ 
        appendPosition(&wPosition, nbLine,(i-j)-lastnewLinePosition);
        numOccorrenze++;
        j = T[j-1];
      }
 
      // non-corrispondenza dopo j corrispondenze
      else if (i < N && pat[j] != txt[i]){
        if (j != 0)
         j = T[j-1];
        else
         i = i+1;
      }
    }
  
    appendFileInfo(&fInfo,regular_file,numOccorrenze, wPosition);
    appendWordInfo(&wInfo,pat,fInfo);

    if(contains(*current,wInfo->name) != NULL)
        insertFileInfoAt(contains(*current,wInfo->name),wInfo->name,wInfo->fileInfo);
    else
        appendWordInfo(current,wInfo->name,wInfo->fileInfo);
    
    free(T);
}
 


void failure_table(char *pat, int M, int *T){
    int len = 0;  
    int i;
 
    T[0] = 0; 
    i = 1;
 
    // calcola T[i] da 1 a M-1
    while (i < M){
       if (pat[i] == pat[len]){
         len++;
         T[i] = len;
         i++;
       }
       else {
         if (len != 0){
           len = T[len-1];
         }
         else // len uguale a 0
         {
           T[i] = 0;
           i++;
         }
       }
    }
}