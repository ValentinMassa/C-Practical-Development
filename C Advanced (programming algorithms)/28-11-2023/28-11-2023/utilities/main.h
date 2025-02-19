#ifndef UTILITIES__MAIN_H_INCLUDED
#define UTILITIES__MAIN_H_INCLUDED

#include "structsAndDefines.h"
#include <stdio.h>
typedef void(*show)(const void * data);

int processStock(char * namebin, char*nametxt, char *stockIsRequired, char * FOrdersDone);
void printBin(char * filename, unsigned tamData, show SHOW);
void showProducts(const void * data);
#endif // MAIN_H_INCLUDED
