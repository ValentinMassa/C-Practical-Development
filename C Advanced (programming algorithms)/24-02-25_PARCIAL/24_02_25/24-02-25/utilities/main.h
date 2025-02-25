#ifndef UTILITIES__MAIN_H_INCLUDED
#define UTILITIES__MAIN_H_INCLUDED


#define MAX_WORD 30

typedef struct {
    char word[MAX_WORD];
    unsigned echo;
}t_word;

typedef struct {
    char word[MAX_WORD];
    unsigned char flag;
}t_next_line_continue;

int processFiles(char* fileA, char* fileB, char* fileAB, unsigned maxline );



#endif // UTILITIES__MAIN_H_INCLUDED
