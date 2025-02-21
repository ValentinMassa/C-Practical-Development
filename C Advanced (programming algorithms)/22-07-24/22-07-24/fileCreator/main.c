#include "./main.h"
#include "../structs/main.h"
#include <stdio.h>



void binCreator(const char* fname)
{
    FILE* fp;
    idx_Academics aux[] =
    {
        {41234567, "COMPUTING", "2020", '1', '7'},
        {41234567, "MATHS", "2021", '2', '8'},
        {41234567, "ECONOMICS", "2023", '2', '9'},
        {42345678, "PHILOSOPHY", "2021", '2', '7'},
        {42345678, "ART", "2022", '1', '8'},
        {42345678, "MUSIC", "2023", '2', '6'},
        {44510875, "CHEMISTRY", "2021", '1', '6'},
        {44510875, "PHYSICS", "2022", '2', '8'},
        {44510875, "MATHS", "2023", '1', '7'},
        {45712345, "BUSINESS", "2022", '2', '6'},
        {45712345, "LITERATURE", "2023", '1', '8'},
        {45987654, "ECONOMICS", "2020", '1', '5'},
        {45987654, "GEOGRAPHY", "2022", '1', '2'},
        {45987654, "LITERATURE", "2023", '2', '9'},
        {46789012, "ARCHITECTURE", "2020", '2', '7'},
        {46789012, "LAW", "2021", '1', '9'},
        {46789012, "ECONOMICS", "2022", '2', '6'},
        {47891234, "MEDICINE", "2020", '2', '7'},
        {47891234, "ENGINEERING", "2021", '1', '9'},
        {47891234, "PSYCHOLOGY", "2023", '1', '8'}
    };

    fp = fopen(fname, "wb");
    fwrite(&aux, sizeof(idx_Academics), sizeof(aux)/sizeof(idx_Academics), fp);
    fclose(fp);
}
