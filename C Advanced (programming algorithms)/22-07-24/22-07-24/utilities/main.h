#ifndef UTILITIES__MAIN_H_INCLUDED
#define UTILITIES__MAIN_H_INCLUDED
#define SIZE_ID 9
#define SIZE_BUFFER 1024


#define NOT_FOUNDED -1
#define ERROR 0
#define DONE 1
#define NAME_AUX_TXT "aux.txt"

int generateInformOfStudentById(char * namefile, char* txtreport, int id);
void createFinalName(char *namefinal,char *nametxt,int _id);
int askIdFromStdin();
#endif // UTILITIES__MAIN_H_INCLUDED
