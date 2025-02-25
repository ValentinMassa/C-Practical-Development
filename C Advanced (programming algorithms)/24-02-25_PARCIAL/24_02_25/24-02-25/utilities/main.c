#include "./main.h"
#include "../Btree/main.h"
#include "../list/main.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define isalpha(x) ( (x)>= 'A' && (x)<='Z'?1:0)
#define islower(x) ( (x)>= 'a' && (x)<= 'z'?1:0)
#define isnumber(x) ( (x)>= '0' && (x)<= '9'?1:0)

#define isword(x) ((isalpha(x) || islower(x) || isnumber(x)) ? 1:0)

int UploadListFromTree(void*data, void*list);
void updateEcho (void*datat, void*data,unsigned sizedt, unsigned sized);
int wordsCmp(const void*a, const void* b);
void printWordsTree(void*datat, void*param);
int processFile(char* fname, unsigned maxline, tree * _t);
int processLine(char* buffer, tree * _t, t_next_line_continue * nextword);
int processABfile(char* fname, tree * a, tree * b);


int processFiles(char* fileA, char* fileB, char* fileAB, unsigned maxline ){

    tree wordsa, wordsb;

    createBTree(&wordsa);
    if(!processFile(fileA, maxline, &wordsa))
    {
        deleteBTree(&wordsa);
        return 0;
    }

    createBTree(&wordsb);
    if(!processFile(fileB, maxline, &wordsb))
    {
        deleteBTree(&wordsa);
        deleteBTree(&wordsb);
        return 0;
    }

    if(!processABfile(fileAB, &wordsa, &wordsb))
    {
        puts("> AN ERROR OCURRIED WHILE MAKING A-B");
        printf("> DELETEATING A-B file: %s\n", fileAB);
        remove(fileAB);
    }

    deleteBTree(&wordsa);
    deleteBTree(&wordsb);
    return 1;
}


int processABfile(char* fname, tree * a, tree * b)
{
    FILE *pfab;
    int result;
    sList afinal;
    t_word dataaux;

    pfab = fopen(fname, "wt");
    if(!pfab)return 0;

    createList(&afinal);
    if(!walkTreeInOrderLoadingSomething(a, &afinal, UploadListFromTree))
    {
        fclose(pfab);
        destroyList(&afinal);
        return 0;
    }

    fprintf(pfab, "%s\n", "A-B RESULT");
    puts("A-B RESULT:");
    while(deleteFirstList(&afinal, &dataaux, sizeof(t_word)) )
    {
        result = searchDataKeyNode(b, &dataaux, sizeof(t_word), wordsCmp);
        if(!result)
        {
            printf(" -%s\n", dataaux.word);
            fprintf(pfab,"%s\n", dataaux.word);
        }
    }
    fclose(pfab);
    destroyList(&afinal);
    return 1;
}





int processFile(char* fname, unsigned maxline, tree * _t)
{
    FILE *pf;
    char buffer[maxline];

    t_next_line_continue wordaux = {"", 0};


    pf = fopen(fname, "rt");
    if(!pf)return 0;

    while(fgets(buffer, maxline, pf ) != NULL)
    {
        if(*buffer == '\n' || *buffer == '\0' )continue;
        if(!processLine(buffer, _t, &wordaux))
        {
            fclose(pf);
            return 0;
        }
    }

    fclose(pf);
    return 1;
}

int processLine(char* buffer, tree * _t, t_next_line_continue * nextword){
    char* pointer, *beginning;
    t_word aux = {" ", 0};

    beginning = buffer;

    pointer = strchr(buffer, '\n');
    if(!pointer)
    {
        pointer = strchr(buffer, '\0');
        if(!pointer)return 0;
    }
    *pointer = '\0';
    pointer = strchr(buffer, '\0');

    if(nextword->flag == '1')
    {
        while( isword(*beginning) && beginning < pointer)
            beginning ++;

        if(beginning  != buffer)
        {
            *beginning = '\0';

            strcat(nextword->word, buffer);
            strcpy(aux.word, nextword->word);

            insertIntoBtree(_t, &aux, sizeof(aux), wordsCmp, updateEcho);

            nextword->flag = '0';
            strcpy(nextword->word, " ");
            beginning +=1;
        }
        else
        {
            strcpy(aux.word, nextword->word);
            insertIntoBtree(_t, &aux, sizeof(aux), wordsCmp, updateEcho);
        }

    }

    if(isword(*(pointer - 1)) && pointer > beginning)
       {
            pointer -= 1;
            while( isword(*pointer) && pointer > beginning)
                pointer --;

            if(pointer == beginning && isword(*pointer))
            {
                strcpy(nextword->word, (pointer));
                nextword->flag = '1';
                return 1;
            }
            else
            {
                strcpy(nextword->word, (pointer + 1));
                nextword->flag = '1';
            }
            *(pointer) = '\0';
       }

    while(pointer > beginning)
    {
        while( !isword(*pointer) && pointer > beginning)
            pointer --;

        *(pointer + 1) = '\0';

        while( isword(*pointer) && pointer > beginning)
            pointer --;

        if(pointer == beginning && isword(*pointer))
            strcpy(aux.word, pointer);
        else
            strcpy(aux.word, (pointer + 1));

        insertIntoBtree(_t, &aux, sizeof(aux), wordsCmp, updateEcho);

    }
    return 1;
}

int UploadListFromTree(void*data, void*list)
{
    return InsertIntoList((sList*)list, data, sizeof(t_word));
}


int wordsCmp(const void*a, const void* b)
{
    t_word * ai = (t_word *)a;
    t_word * bi = (t_word *)b;

    return strcmp( bi->word, ai->word);
}

void updateEcho (void*datat, void*data,unsigned sizedt, unsigned sized)
{
    t_word * ai = (t_word *)datat;

    ai->echo += 1;
    return;
}

void printWordsTree(void*datat, void*param)
{
    t_word * ai = (t_word *)datat;

    printf("%s\n", ai->word);
    return ;
}
