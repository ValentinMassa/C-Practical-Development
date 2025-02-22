#include "./main.h"
#include "../structs.h"
#include <stdio.h>

void createTxt(char* nameFIle)
{
    FILE* fp;
    int i, j;
    t_student students[25] = {
            {44510875, "MASSA", "VALENTIN", "INF", {{{1111, "20231C", 5}, {1112, "20232C", 2}, {1151, "20241C", 9}, {1411, "20242C", 10}, {4631, "20221C", 5}}, 5}},
            {34642753, "HERNESTO", "DIAZ", "ELE", {{{1113, "20231C", 3}, {1112, "20232C", 8}}, 2}},
            {31234567, "PEREZ", "JUAN", "MEC", {{{1210, "20211C", 7}, {1211, "20212C", 6}, {1212, "20221C", 9}}, 3}},
            {28945678, "LOPEZ", "CARLA", "CIV", {{{1310, "20221C", 8}, {1311, "20222C", 7}}, 2}},
            {36789123, "GOMEZ", "LUCAS", "INF", {{{1111, "20231C", 6}, {1112, "20232C", 9}, {1151, "20241C", 10}}, 3}},
            {42345678, "RODRIGUEZ", "MARTIN", "ELE", {{{1410, "20231C", 7}, {1411, "20232C", 8}, {1412, "20241C", 9}}, 3}},
            {37894567, "FERNANDEZ", "MARIA", "MEC", {{{1211, "20211C", 6}, {1212, "20212C", 5}, {1213, "20221C", 8}}, 3}},
            {41234568, "GARCIA", "NICOLAS", "CIV", {{{1311, "20221C", 9}, {1312, "20222C", 7}}, 2}},
            {45891234, "TORRES", "SOFIA", "INF", {{{1111, "20231C", 5}, {1112, "20232C", 8}}, 2}},
            {36789012, "RAMIREZ", "PABLO", "ELE", {{{1410, "20231C", 9}, {1411, "20232C", 10}}, 2}},
            {31234569, "SUAREZ", "LUCIANO", "MEC", {{{1210, "20211C", 6}, {1211, "20212C", 8}}, 2}},
            {28945679, "MARTINEZ", "DIEGO", "CIV", {{{1310, "20221C", 5}, {1311, "20222C", 6}}, 2}},
            {37894568, "HERRERA", "JULIETA", "INF", {{{1113, "20231C", 7}, {1112, "20232C", 5}}, 2}},
            {42345679, "AGUILAR", "FEDERICO", "ELE", {{{1411, "20231C", 8}, {1412, "20232C", 9}}, 2}},
            {31234570, "ALVAREZ", "GABRIEL", "MEC", {{{1212, "20211C", 9}, {1213, "20212C", 10}}, 2}},
            {28945680, "FERRARI", "NATALIA", "CIV", {{{1311, "20221C", 6}, {1312, "20222C", 7}}, 2}},
            {37894569, "BENITEZ", "ESTEBAN", "INF", {{{1111, "20231C", 7}, {1112, "20232C", 8}}, 2}},
            {42345680, "MORENO", "SERGIO", "ELE", {{{1410, "20231C", 6}, {1411, "20232C", 9}}, 2}},
            {31234571, "GUTIERREZ", "ALEJANDRO", "MEC", {{{1211, "20211C", 5}, {1212, "20212C", 6}}, 2}},
            {28945681, "SANDOVAL", "MARINA", "CIV", {{{1310, "20221C", 9}, {1311, "20222C", 8}}, 2}},
            {37894570, "CASTRO", "MATEO", "INF", {{{1113, "20231C", 8}, {1112, "20232C", 6}}, 2}},
            {42345681, "VEGA", "EZEQUIEL", "ELE", {{{1411, "20231C", 7}, {1412, "20232C", 5}}, 2}},
            {31234572, "PONCE", "FABIAN", "MEC", {{{1212, "20211C", 9}, {1213, "20212C", 10}}, 2}},
            {28945682, "LOZANO", "RAUL", "CIV", {{{1311, "20221C", 5}, {1312, "20222C", 7}}, 2}},
            {37894571, "NAVARRO", "TOMAS", "INF", {{{1111, "20231C", 6}, {1112, "20232C", 8}}, 2}}
    };

    fp = fopen(nameFIle, "w");

    for(i= 0; i<25; i++)
    {
        fprintf(fp, "%d%-20s%-20s%3s", students[i].id, students[i].last_name, students[i].name, students[i].code_carreer);
            for(j= 0; j <students[i].subjects.amount_subjetcs ; j++)
            {
                fprintf(fp, "%4d%-6s%02d", students[i].subjects.subjetc[j].code_subject, students[i].subjects.subjetc[j].course_code, students[i].subjects.subjetc[j].final_note);
            }
        fprintf(fp, "%02d\n", students[i].subjects.amount_subjetcs);
    }

    fclose(fp);
}



