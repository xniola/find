#ifndef MYSTRUCT_H
#define MYSTRUCT_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h> 
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

/*Informazioni di una parola in un insieme di file*/
typedef struct wordInfo{
    char* name; // nome della parola
    struct fileInfo* fileInfo;
    struct wordInfo* next;
}wordInfo;


/*Rappresenta l'informazione dell'insieme dei file*/
typedef struct fileInfo{
    char* file_path; // path del file
    int occurrences; // occorrenze della parola
    struct wordPosition* positions; // posizioni della parola nel file
    struct fileInfo* next;
}fileInfo;


/*Le posizioni di una parola in un file*/
typedef struct wordPosition{
    int line;
    int posChar;
    struct wordPosition* next;
}wordPosition;


typedef struct entryFiles{
    char* pathOfFile;
    struct entryFiles* next;
}entryFiles;


typedef struct entryWords{
    char* word;
    struct entryWords* next;
}entryWords;

void printEntryWords(entryWords* entryWords);
void printEntryFile(entryFiles* entryFiles);

/*Salva su listFile tutti i files contenuti in una directory ricorsivamente*/
void analyzePathRecursively(entryFiles** listFile, char* path);

/*Salva su listFile solo i files regolari contenuti in una directory*/
void analyzeRegularFiles(entryFiles** listFile, char* path);

/* Metodi di inizializzazione delle strutture create*/
void initEntryFile(entryFiles* entryF);
void initWordInfo(wordInfo* wInfo);
void initFileInfo(fileInfo* fInfo);
void initWordPosition(wordPosition* wPosition);
void initEntryWords(entryWords* entryWords);

/* Metodi di verifica se le strutture sono vuote: ritornano 1 se sono vuote, 0 altrimenti*/
int isWordInfoEmpty(wordInfo** wInfo);
int isFileInfoEmpty(fileInfo** fInfo);
int isWordPositionEmpty(wordPosition** wPosition);
int isEntryFileEmpty(entryFiles** entryF);
int isEntryWordsEmpty(entryWords** entryWords);

/* Aggiunta di informazione alla fine della struttura creata*/
void appendPosition( wordPosition** head, int newLine, int newChar);
void appendWordInfo( wordInfo** head,char* newName, fileInfo* newFileInfo);
void appendFileInfo( fileInfo** head, char* file,int newOccorrenze, wordPosition* wPosition);
void appendEntry(entryFiles** listFile, char* newEntry);
void appendEntryWords(entryWords** entryWords, char* newWord);

/*Inserimento di un informazione in una posizione specifica*/
void insertFileInfoAt(wordInfo* wInfo,char* name,fileInfo* fInfo);

wordInfo* contains(wordInfo *head,char* value);

/* cerca tutte le occorrenze di un pattern specifico su tutti i file*/
int getTotalOccurrences(wordInfo wInfo,char* nodeName);

void printWordInfo(wordInfo* wInfo);

/*Conta la size della struttura dati*/
int countWordInfoSize(wordInfo* wInfo);
int countEntryFileSize(entryFiles* entry);
int countEntryWordsSize(entryWords* entryWords);

/*Verifica se il path dato sia una directory*/
int isDirectory(char *path);

void populateEntryFile(entryFiles** entry, char* path);
void populateEntryWords(entryWords** entryWord,char* inputFile);
void processWordInfoVerbose(wordInfo** current, entryWords* entryWords, entryFiles* entry);
void processWordInfo(wordInfo** current, entryWords* entryWords, entryFiles* entry);

char* parseWordByLastTwo(int isRecursive,char* word);

/*Rimuove tutte le entry dalla struttura che abbiano una certa estensione*/
void removeExtensions(entryFiles** entry, char* ext);

#endif