#ifndef STRUCTS_H_
#define STRUCTS_H_


typedef struct
{
    unsigned ID;
    unsigned posRegister;
}t_students_idx;

typedef struct{
    unsigned ID;
    char name[21];
    char last_name[21];
    char borndate[11];
    char signDate[11];
    unsigned char logical_status; //1: active, 0: non active
}t_students;

#endif // STRUCTS_H_
