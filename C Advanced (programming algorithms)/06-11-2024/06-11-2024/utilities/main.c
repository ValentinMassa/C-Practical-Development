#include "./main.h"
#include "../Btree/main.h"
#include "../list/main.h"
#include "../structs.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


#define isalpha(x) ((x)>= 'A' && (x)<='Z'?1:0)
#define islower(x) ((x)>= 'a' && (x)<='z'?1:0)
#define isletter(x) (isalpha(x)||islower(x)?1:0)
#define toupper(x) ( islower(x)? ((x) - 'a' + 'A'): (x))

void convertwordToUpper(char* cad);
int compeareCads(const void* a, const void *b);
void updateTword(void*a, void*b, unsigned sa, unsigned sb);
int ProcessLine(char* buffer, tree *wordsTree);
void printWordsAndEcho(void*datatree, void*data, unsigned sizedatatree, unsigned sizedata);
int ProcessBook(char* namebook, tlist * _list);
int compeareEcho(const void* a, const void*b);
void printIntoList(void*datatree, void*data, unsigned sizedatatree, unsigned sizedata);

void menu(char* namebook)
{
    t_word auxtword;
    int result = -1;
    char aux[2];
    tlist words;

    createList(&words);

    ProcessBook(namebook, &words);

    sortList(&words, compeareEcho);
    puts("> Welcome to the book app analyzer");

    while(result != 0)
    {
        puts("> Choose an option");
        puts("Watch a list of repeating words");
        puts("      1. Upward");
        puts("      2. downWard");
        puts("3. Most repetead word");
        puts("4. Less repetead word");
        printf("0. exit");
        printf("\nWrite an option(0 to 4): ");
        fflush(stdin);
        fgets(aux, 2, stdin);
        fflush(stdin);
        result = atoi(aux);

        switch (result){
            case 0:{
                puts("Leaving.....");
                break;
            }
            case 1:{
                walkList(&words, NULL, 0, printWordsAndEcho);
                break;
            }
            case 2:{
                invertList(&words);
                walkList(&words, NULL, 0, printWordsAndEcho);
                sortList(&words, compeareEcho);
                break;
            }
            case 3:{
                showLast(&words, &auxtword, sizeof(t_word));
                printWordsAndEcho(&auxtword, NULL, sizeof(auxtword), 0);
                break;
            }

            case 4:{

                showFirst(&words, &auxtword, sizeof(t_word));
                printWordsAndEcho(&auxtword, NULL, sizeof(auxtword), 0);
                break;
            }
            default: {
                puts("> Invalid option");
                break;
            }
        }
    }
    deleteList(&words);
    return;
}


int ProcessBook(char* namebook, tlist * _list)
{
    int result;
    char buffer[MAX_BUFFER];
    FILE* fp = fopen(namebook, "rt");
    tree wordsTree;

    createTree(&wordsTree);

    while(fgets(buffer, MAX_BUFFER, fp) != NULL)
    {
        if(*buffer == '\n')continue;
        result = ProcessLine(buffer, &wordsTree);
        if(!result)
        {
            deleteTree(&wordsTree);
            fclose(fp);
            return 0;
        }
    }

    walkTreeInOrder(&wordsTree, _list, 0,printIntoList);

    deleteTree(&wordsTree);
    fclose(fp);
    return 1;
}

void printWordsAndEcho(void*datatree, void*data, unsigned sizedatatree, unsigned sizedata)
{
    t_word * ai = (t_word*) datatree;
    printf("%-25s | %04u \n", ai->word, ai->echo);
    return;
}

void printIntoList(void*datatree, void*data, unsigned sizedatatree, unsigned sizedata)
{
    t_word * ai = (t_word*) datatree;
    tlist * list = (tlist*)data;

    insertIntoList(list, ai, sizeof(t_word));

    return;
}



int ProcessLine(char* buffer, tree *wordsTree)
{
    char* pointer;
    t_word wordaux;

    pointer = strchr(buffer, '\n');


    if(!pointer)
    {
        pointer = strchr(buffer, '\0');
        if(!pointer)return 0;
    }
    else *pointer = '\0';

    pointer = strchr(buffer, '\0');
    pointer --;


    while(pointer >= buffer){
        while( !isletter(*pointer) &&pointer >= buffer )
        {
            pointer --;
        }
        if(buffer == pointer)continue;

        *(pointer + 1) = '\0';

        while(isletter(*pointer) &&  pointer >= buffer )
        {
            pointer --;
        }
        if(buffer != pointer)strcpy(wordaux.word, (pointer + 1));
        else strcpy(wordaux.word, (pointer));

        wordaux.echo = 1;

        convertwordToUpper(wordaux.word);
        if(!insertIntoTree(wordsTree, &wordaux, sizeof(wordaux),compeareCads,updateTword))
            return 0;
    }
    return 1;
}

int compeareCads(const void* a, const void*b)
{
    t_word * ai = (t_word*) a;
    t_word * bi = (t_word*) b;

    return strcmp(bi->word, ai->word);
}

int compeareEcho(const void* a, const void*b)
{
    t_word * ai = (t_word*) a;
    t_word * bi = (t_word*) b;

    return (int)ai->echo - (int)bi->echo ;
}

void updateTword(void*a, void*b, unsigned sa, unsigned sb)
{
    t_word * ai = (t_word*) a;

    ai->echo += 1;
    return;
}

void convertwordToUpper(char* cad)
{
    char *pointer = cad;
    while(*pointer != '\0')
    {
        *pointer = toupper(*pointer);
        pointer++;
    }
    return;
}



