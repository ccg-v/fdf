#include "fdf.h"

void print_altitudes(t_map *map)
{
    int     line;
    int     column;
    int     X;
    int     Y;
    int     Z;

    line = 0;
    printf("\narray of altitudes:\n"); 
    line = 0;
    while (line < map->length)
    {
        column = 0;
        while (column < map->width)
        {
            printf("%3d", (int)map->mesh[line][column].z);
            X = (int)map->mesh[line][column].x;
            Y = (int)map->mesh[line][column].y;
            Z = (int)map->mesh[line][column].z;
            column++;
        }
        printf("\n");
        line++;
    }
}

void    print_coordenates(t_map *map)
{
    int     line;
    int     column;
    int     X;
    int     Y;
    int     Z;

    line = 0;
    while (line < map->length)
    {
        column = 0;
        while (column < map->width)
        {
            printf("(%2.2f, %2.2f, %2.2f) ", map->mesh[line][column].x, \
                map->mesh[line][column].y, map->mesh[line][column].z);
            X = (int)map->mesh[line][column].x;
            Y = (int)map->mesh[line][column].y;
            Z = (int)map->mesh[line][column].z;
            column++;
        }
        printf("\n");
        line++;
    }  
}