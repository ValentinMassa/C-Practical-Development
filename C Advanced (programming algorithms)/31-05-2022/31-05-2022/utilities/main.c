#include "../queue/main.h"
#include "../stack/main.h"
#include "./main.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define isSpace(x)( (x) == ' '?1:0)
#define isLetter(x)( (( (x) >= 'a' && (x) <= 'z' )||( (x) >= 'A' && (x) <= 'Z' ) )?1:0)
#define isTheEnd(x)( (x) == '\0' || (x) == '\n'?1:0 )
#define isUpper(x)(( (x) >= 'A' && (x) <= 'Z' )?1:0)
#define isLower(x)(( (x) >= 'a' && (x) <= 'z' )?1:0)

int moveLetterForTheABCwithOffset(char *letter, int offset, char  min, char  max );
int processLine(char * buffer  , FILE* file_aux);
int loadWordInStackAndQueue(char *buffer, sQueue * words, Stack* backwords);
int addLineInBuffer(char *buffer, sQueue * words, Stack* backwords);
int cadsize(char* cad);
void EnfoscateWord(char* aux_word, int offset);

int processTxt(char * nametxt, char* auxTxt)
{
    char buffer[SIZE_MAX_BUFFER];
    FILE* file_txt, *file_aux;
    int band = 0;


    file_txt = fopen(nametxt, "r");
    file_aux = fopen(auxTxt, "w");

    while( fgets(buffer, sizeof(buffer), file_txt ) !=  NULL )
    {
        if(cadsize(buffer)<=0)continue;
        if(!processLine(buffer ,file_aux))
        {
            band = 1;
            break;
        }
        fprintf(file_aux, "%s\n",buffer);
    }

    fclose(file_txt);
    fclose(file_aux);
    if(band){
        puts(">ERROR, CANNOT PROCESS THE FILE");
        remove(auxTxt);
        return 0;
    }
    remove(nametxt);
    rename(auxTxt, nametxt);
    puts(">ALL DONE!");
    return 1;
}
int processLine(char * buffer, FILE* file_aux)
{
    sQueue words;
    Stack backwords;
    char * pointer = buffer;
    createQueue(&words);
    createStack(&backwords);

    while((*pointer != '\n' && *pointer != '\0') && pointer < pointer + SIZE_MAX_BUFFER)
    {
        pointer ++;
    }
    *pointer = '\0';

    if(!loadWordInStackAndQueue(buffer, &words, &backwords))
    {
        destroyStack(&backwords);
        destructQueue(&words);
        return 0;
    }
    if(!addLineInBuffer(buffer, &words, &backwords))
    {
        destroyStack(&backwords);
        destructQueue(&words);
        return 0;

    }
    return 1;

}

int addLineInBuffer(char *buffer, sQueue * words, Stack* backwords)
{
    char* iterator, *punt;

    char aux_word[SIZE_MAX_BUFFER];
    char aux_word_backword[SIZE_MAX_BUFFER];
    int offset;

    punt = iterator = buffer;


    while( !isTheEnd(*punt) )
    {
        while(!isLetter(*punt) && !isTheEnd(*punt) )punt ++;

        iterator = punt;

        while(isLetter(*iterator)&& !isTheEnd(*iterator))
            iterator ++;

        if(isTheEnd(*iterator) && isTheEnd(*punt))continue;

        if(!getQueueElement(words, aux_word, SIZE_MAX_BUFFER))return 0;
        if(!popElement(backwords, aux_word_backword, SIZE_MAX_BUFFER)) return 0;

        offset = cadsize(aux_word_backword) * (-1);

        EnfoscateWord(aux_word, offset);

        memcpy(punt, aux_word, cadsize(aux_word) );

        punt = iterator;

    }
    return 1;

}

void EnfoscateWord(char* aux_word, int offset)
{
    char* pointer = aux_word;

    while(!isTheEnd(*pointer)){
            if(isUpper(*pointer))
                moveLetterForTheABCwithOffset(pointer, offset, 'A', 'Z' );
            if(isLower(*pointer))
                moveLetterForTheABCwithOffset(pointer, offset, 'a', 'z' );
            pointer++;
        }
}

int moveLetterForTheABCwithOffset(char *letter, int offset, char  min, char  max )
{
    if(offset >= 0)
        return 0;

    if( (*letter) - 1 >= min)
    {
        (*letter) = (*letter)  - 1;
        offset ++;
        return moveLetterForTheABCwithOffset( letter, offset, min, max);
    }
    if((*letter) == min){
        (*letter) = max;
        offset ++;
        return moveLetterForTheABCwithOffset(letter, offset, min, max);
    }
    return 1;

}

int loadWordInStackAndQueue(char *buffer, sQueue * words, Stack* backwords)
{
    char* iterator, *punt;
    char word_auxiliar[SIZE_MAX_BUFFER];
    int size;

    punt = iterator = buffer;
    while(!isTheEnd(*punt))
    {
        while(!isLetter(*punt) && !isTheEnd(*punt))
        {
            punt ++;
        }

        iterator = punt;

        while( isLetter(*iterator) && !isTheEnd(*iterator))
        {
            iterator ++;
        }
        if( isTheEnd(*iterator) && isTheEnd(*punt))break;

        memcpy(word_auxiliar, punt, iterator - punt );
        *(word_auxiliar + (iterator - punt)) = '\0';

        size = cadsize(word_auxiliar);

        if(!putElementInQueue(words, word_auxiliar, (size + 1) ))return 0;

        if(!pushElemnt(backwords, word_auxiliar ,(size + 1)))return 0;
        punt = iterator;
    }
    return 1;
}

int cadsize(char* cad)
{
    char* punt = cad;
    int cont = 0;

    while( !isTheEnd(*punt))
    {
       cont++;
       punt ++;
    }
    return cont;

}
