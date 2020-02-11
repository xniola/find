#include "../lib/myStruct.h"
#include "../lib/kmpalgo.h"

void initEntryFile(entryFiles* entryF){
    entryF->pathOfFile = "";
    entryF->next = NULL;
}

void initWordInfo(wordInfo* wInfo){
    wInfo->name = "";
    wInfo->fileInfo = NULL;
    wInfo->next = NULL;
}

void initFileInfo(fileInfo* fInfo){
    fInfo->file_path = "";
    fInfo->occurrences = 0;
    fInfo->positions = NULL;
    fInfo->next = NULL;
}

void initWordPosition(wordPosition* wPosition){
    wPosition->line = 0;
    wPosition->posChar = 0;
    wPosition->next = NULL;
}

void initEntryWords(entryWords* entryWords){
    entryWords->word = "";
    entryWords->next = NULL;
}

int isWordInfoEmpty(wordInfo** wInfo){
    if(strcmp((*wInfo)->name,"") == 0)
        return 1;
    else return 0;
}

int isFileInfoEmpty(fileInfo** fInfo){
    if(strcmp((*fInfo)->file_path,"") == 0)
        return 1;
    else return 0;
}

int isWordPositionEmpty(wordPosition** wPosition){
    if((*wPosition)->line == 0 && (*wPosition)->posChar == 0 && (*wPosition)->next == NULL)
       return 1;
    else return 0;
}

int isEntryFileEmpty(entryFiles** entryF){
    if(strcmp((*entryF)->pathOfFile,"") == 0 && (*entryF)->next == NULL)
        return 1;
    else return 0;
}

int isEntryWordsEmpty(entryWords** entryWords){
    if(strcmp((*entryWords)->word,"") == 0 && (*entryWords)->next == NULL)
        return 1;
    else return 0;
}


/* Data la reference alla testa della lista e i nuovi dati,
   lo appende alla fine della lista  */
void appendPosition(wordPosition** head, int newLine, int newChar)
{ 
    // alloco la nuova wordPosition
    struct wordPosition* newList = (struct wordPosition*) malloc(sizeof(struct wordPosition)); 
  
    struct wordPosition *last = *head;  // usato successivamente
   
    // inserisco i nuovi dati
    newList->line  = newLine;
    newList->posChar = newChar; 
  
    // imposto l'ultimo elemento della lista NULL
    newList->next = NULL; 
  
    //se la lista è vuota allora inserisco il node alla testa
    //if (*head == NULL)
    if(isWordPositionEmpty(head) == 1) 
    { 
       *head = newList; 
       return; 
    }

  
    // altrimenti vado avanti fino l'ultimo nodo
    while (last->next != NULL) 
        last = last->next; 
   
    // cambio il next dell'ultimo nodo
    last->next = newList; 
    return;     
} 


void appendWordInfo(wordInfo** head,char* newName, fileInfo* newFileInfo){

    // alloco la nuova wordInfo 
    struct wordInfo* newList = (struct wordInfo*) malloc(sizeof(struct wordInfo)); 
    
  
    struct wordInfo *last = *head;  // usato successivamente
   
    // inserisco i nuovi dati
    newList->name = newName;
    //printf("NEWLIST: %s\n",newList->name);
    newList->fileInfo = newFileInfo;
  
    // imposto l'ultimo elemento della lista NULL
    newList->next = NULL; 
  
    // se la lista è vuota allora inserisco il node alla testa
    //if (*head == NULL)
    if(isWordInfoEmpty(head) == 1) 
    { 
       *head = newList; 
       return; 
    }   
       
    // altrimenti vado avanti fino l'ultimo nodo
    while (last->next != NULL) 
        last = last->next; 
   
    // cambio il next dell'ultimo nodo
    last->next = newList;
     
    return;      
}

void appendFileInfo(fileInfo** head, char* file,int newOccorrenze,wordPosition* wPosition){
    // alloco la nuova fileInfo
    struct fileInfo* newList = (struct fileInfo*) malloc(sizeof(struct fileInfo)); 
  
    struct fileInfo *last = *head;  // usato successivamente
   
    // inserisco i nuovi dati
    newList->file_path  = file;
    newList->occurrences = newOccorrenze;
    newList->positions = wPosition;
    newList->next = NULL; 
  
    // se la lista è vuota allora inserisco il node alla testa
    //if (*head == NULL)
    if(isFileInfoEmpty(head) == 1) 
    { 
       *head = newList; 
       return; 
    }   
       
    // altrimenti vado avanti fino l'ultimo nodo
    while (last->next != NULL) 
        last = last->next; 
   
    // cambio il next dell'ultimo nodo
    last->next = newList; 
    return;  
}

void appendEntryWords(entryWords** head,char* newWord){
    // alloco la nuova entryWords
    struct entryWords* newList =  malloc(sizeof(struct entryWords)); 
  
    struct entryWords *last = *head;  // usato successivamente
   
    // inserisco i nuovi dati
    newList->word  = newWord; 
  
    // imposto l'ultimo elemento della lista NULL
    newList->next = NULL; 
  
    //se la lista è vuota allora inserisco il node alla testa
    //if (*head == NULL)
    if(isEntryWordsEmpty(head) == 1) { 
       *head = newList; 
       return; 
    }

  
    // altrimenti vado avanti fino l'ultimo nodo
    while (last->next != NULL) 
        last = last->next; 
   
    // cambio il next dell'ultimo nodo
    last->next = newList; 
    return;     
}

void insertFileInfoAt(wordInfo* wInfo,char* nameTag,fileInfo* fInfo){
    while(strcmp(wInfo->name,nameTag) != 0){
        wInfo = wInfo->next;
    }
    appendFileInfo(&wInfo->fileInfo,fInfo->file_path,fInfo->occurrences,fInfo->positions);
}


wordInfo* contains(wordInfo *head,char * value)
{
  while (head)
  {
    if (strcmp(head->name,value) == 0)
    {
      return head;
    }
    head = head -> next;
  }
  return NULL;
}


  void printWordInfo(wordInfo* wInfo){
      if(isWordInfoEmpty(&wInfo) == 1){
        printf("La struttura è vuota\n");
        return;
      }
      
      while(wInfo != NULL){
        printf("WORD %s\r\n",wInfo->name);
        printf("TOTAL OCCURRENCES %i\r\n",getTotalOccurrences(*wInfo,wInfo->name));
       while(wInfo->fileInfo != NULL){
        printf("FILE %s\r\n",wInfo->fileInfo->file_path);
        printf("Occorrenze: %i\n",wInfo->fileInfo->occurrences);
        printf("POSITION\r\n");
         while (wInfo->fileInfo->positions != NULL) { 
            printf("%i %i\r\n", wInfo->fileInfo->positions->line,
                                    wInfo->fileInfo->positions->posChar);
            wInfo->fileInfo->positions = wInfo->fileInfo->positions->next; 
         }
         wInfo->fileInfo = wInfo->fileInfo->next;
       }
    wInfo = wInfo->next;
    printf("\r\n");
  }
}

void printEntryWords(entryWords* entryWords){
    printf("Lista di parole:\n");
    while(entryWords != NULL){
        printf("%s\n",entryWords->word);
        entryWords = entryWords->next;
    }
    printf("FINE\n");
}

int countWordInfoSize(wordInfo* wInfo){
    int count = 0;

    if(isWordInfoEmpty(&wInfo) == 1)
        return count;
    
    while(wInfo != NULL){
        count++;
        wInfo = wInfo->next;
    }
    return count;
}

int countEntryWordsSize(entryWords* entryWords){
    int count = 0;

    if(isEntryWordsEmpty(&entryWords) == 1)
        return count;

    while (entryWords != NULL){
        count++;
        entryWords = entryWords->next;
    }
    return count;
}

void appendEntry(entryFiles** listFile, char* newEntry){
   
    struct entryFiles* new_node = (struct entryFiles*) malloc(sizeof(struct entryFiles)); 
    struct entryFiles *last = *listFile;  /* used in step 5*/
   
    new_node->pathOfFile = newEntry;
    new_node->next = NULL; 
  
    if (isEntryFileEmpty(listFile) == 1) { 
       *listFile = new_node; 
       return; 
    }   
       
    while (last->next != NULL) 
        last = last->next; 
   
    last->next = new_node; 
    return;     
}    



void printEntryFile(entryFiles* entryFiles){
    printf("Lista di files:\n");
    while(entryFiles != NULL){
        printf("%s\n",entryFiles->pathOfFile);
        entryFiles = entryFiles->next;
    }
    printf("Fine\n");
}


void analyzePathRecursively(entryFiles** listFile, char* path){
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (path)) != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0)
                continue;

            char *copy = (char *)malloc(strlen(path) + strlen(ent->d_name) + 2);
            strcpy(copy, path);
            if (copy[strlen(path) - 1] != '/')
                strcat(copy, "/");
            strcat(copy, ent->d_name);
              
            if(isDirectory(copy) == 1)
                analyzePathRecursively(listFile,copy);
            
            else appendEntry(listFile,copy);
        }
    closedir (dir);
    } else {
    perror (""); //non riesco ad aprire
    exit(0);
    }
}

void analyzeRegularFiles(entryFiles** listFile, char* path){
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (path)) != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0)
                continue;

            char *copy = (char *)malloc(strlen(path) + strlen(ent->d_name) + 2);
            strcpy(copy, path);
            if (copy[strlen(path) - 1] != '/')
                strcat(copy, "/");
            strcat(copy, ent->d_name);
              
            if(isDirectory(copy) == 1)
                continue;
            
            else appendEntry(listFile,copy);
        }
    closedir (dir);
    } else {
    perror (""); //non riesco ad aprire
    exit(0);
    }
}


int isDirectory(char *path){
    struct stat sb;
    if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode))
        return 1; //directory

    else return 0;
}

int countEntryFileSize(entryFiles* entry){
    int count = 0;

    if(isEntryFileEmpty(&entry))
        return count;
    
    while(entry != NULL){
        count++;
        entry = entry->next;
    }
    return count;
}

void processWordInfoVerbose(wordInfo** current, entryWords* entryWords, entryFiles* entry){
    entryFiles* eHead = entry;

   while(entryWords != NULL){
       printf("Inizio elaborazione parola: %s\n",entryWords->word);
      entry = eHead;
      while(entry != NULL){
       printf("Inizio elaborazione file: %s\n",entry->pathOfFile);
       clock_t begin = clock();
       kmp_algo(entryWords->word,entry->pathOfFile,current);
        clock_t end = clock();
        double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
       printf("Fine elaborazione file: %s (%f secondi)\n",entry->pathOfFile,time_spent);
       entry  = entry->next;
      }
      printf("Fine elaborazione parola: %s\n",entryWords->word);
      entryWords = entryWords->next;
   } 
}

void processWordInfo(wordInfo** current,entryWords* entryWords, entryFiles* entry){
    entryFiles* eHead = entry;

   while(entryWords != NULL){
      entry = eHead;
      while(entry != NULL){
       kmp_algo(entryWords->word,entry->pathOfFile,current);
       
         entry  = entry->next;
      }
      entryWords = entryWords->next;
   }  
}

void removeExtensions(entryFiles** entry, char* ext){ 
    // Prendo la testa del nodo
    struct entryFiles* temp = *entry, *prev; 
  
    // Verifico se la testa contiene l'estensione 
    while (temp != NULL && strstr(temp->pathOfFile,ext)) { 
        *entry = temp->next;   // Cambio la testa
        free(temp);            // Faccio la free della vecchia testa
        temp = *entry;         // Cambio temp
    } 
  
    // Elimino le occorrenze dopo la testa
    while (temp != NULL) { 
        // Cerco i nodi da eliminare e tengo traccia del nodo precedente 
        while (temp != NULL && strstr(temp->pathOfFile,ext)) { 
            prev = temp; 
            temp = temp->next; 
        } 
  
        // Se il nodo non è presente nella lista 
        if (temp == NULL) return; 
  
        // Stacco il nodo dalla linked list
        prev->next = temp->next; 
  
        free(temp);  //Faccio la free del nodo eliminato
  
        //Prossima iterazione 
        temp = prev->next; 
    } 
} 

void populateEntryFile(entryFiles** entry, char* path){
    for(int i = 1; i <= countlines(path) ; i++){
        int isTruncate = 0;
        int isRecursive = 0;
        char* line = read_nth_line(i,path);
        

        if(i<countlines(path)){
            isTruncate = 1; 
        }
        char* line_to_parse = parseWords(isTruncate,line); //elimino \n

        if(strstr(line_to_parse," r") != NULL){
            isRecursive = 1;
        }
        char* final_line = parseWordByLastTwo(isRecursive,line_to_parse); // elimino " r"
        
        if(isDirectory(final_line)){
            if(isRecursive == 1){
                analyzePathRecursively(entry,final_line);
            }
            else analyzeRegularFiles(entry,final_line);
        }
        else appendEntry(entry,final_line);
    }
}

void populateEntryWords(entryWords** entryWords,char* inputWords){
    int numRigheWords = countlines(inputWords);
      for(int j = 1; j<= numRigheWords; j++){
         int isPatTruncate = 0;
         char* pattern = read_nth_line(j,inputWords);
         if(j<numRigheWords){
            isPatTruncate = 1;
         }
         char* pat = parseWords(isPatTruncate,pattern);
         appendEntryWords(entryWords,pat);
         isPatTruncate = 0;
   }
}

char* deleteLastTwoChars(char** word){
   char* new = malloc(64);
   char buf[64];
   strcpy(buf,*word);
   buf[strlen(buf)-2] = '\0';
   strcpy(new,buf);
   return new;
}

char* parseWordByLastTwo(int isRecursive,char* word){
     char* new = malloc(32);
    
    if(isRecursive == 1)
        new = deleteLastTwoChars(&word);
    else 
        strcpy(new,word);

    return new;
}



int getTotalOccurrences(wordInfo wInfo,char* nodeName){
    int totalOccurrences = 0;

   while(strcmp(wInfo.name,nodeName) != 0){
       wInfo = *wInfo.next;
   }
        
    while(wInfo.fileInfo != NULL){
       totalOccurrences = totalOccurrences + wInfo.fileInfo->occurrences;
       wInfo.fileInfo = wInfo.fileInfo->next;
    }
    return totalOccurrences;
}