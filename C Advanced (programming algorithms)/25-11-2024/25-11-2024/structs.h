#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED

typedef struct{
    unsigned code_subject;
    char course_code[7];
    unsigned final_note;
}t_subject;

typedef struct{
    t_subject subjetc[50];
    unsigned amount_subjetcs;
}t_subjects;

typedef struct{
    unsigned id;
    char last_name[21];
    char name[21];
    char code_carreer[4];
    t_subjects subjects;
}t_student;




#endif // STRUCTS_H_INCLUDED
