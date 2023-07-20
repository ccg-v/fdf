#include "fdf.h"

void print_altitudes(t_map *map)
{
    int     line;
    int     column;
    int     X;
    int     Y;
    int     Z;
    // int     height_lines;
    // int     width_columns;

    line = 0;
    // height_lines = map->length;
    // width_columns = map->width;
    printf("-------- array of altitudes --------\n"); 
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
    // int     height_lines;
    // int     width_columns;
    printf("------- array of coordenates -------\n"); 
    line = 0;
    while (line < map->length)
    {
        column = 0;
        while (column < map->width)
        {
            printf("(%2f, %2f, %2f) ", map->mesh[line][column].x, \
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