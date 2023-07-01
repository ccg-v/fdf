/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 19:32:01 by ccarrace          #+#    #+#             */
/*   Updated: 2023/07/01 00:57:25 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
    gcc -g -Wall -Wextra -Werror -I gnl/ ft_read_file.c get_next_line/get_next_line.c 
    get_next_line/get_next_line_utils.c ft_split.c ft_atoi.c
*/

#include "fdf.h"
#include "get_next_line/get_next_line.h"
#include <stdio.h>
#include <unistd.h>

static int	count_elements(const char *str, char c)
{
	int	i;
	int	num_elements;

	i = 0;
	num_elements = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i] != c && str[i] != '\n')
			num_elements++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (num_elements);
}
/*
static int get_map_length(char *file_name)
{
    int     fd;
    int     map_length;
    char    *line;

    fd = open(file_name, O_RDONLY, 0);
    map_length = -1;
    line = "";
    while(line != NULL)
    {
        line = get_next_line(fd);
        map_length++;
        free(line);
    }
    close(fd);
    return (map_length);
}
*/
/*
static int get_map_width(char *file_name)
{
    char    *line;
    int     fd;
    int     map_width;
    int     flag;
    
    fd = open(file_name, O_RDONLY, 0);
    line = "";
    flag = 0;
    while(line != NULL)
    {
        line = get_next_line(fd);
        if (flag == 0)
        {
            map_width = count_elements(line, ' ');
            flag = 1;
        }
        free(line);
    }
    close(fd);
    return (map_width);
}
*/
/*
static int get_map_width(char *file_name)
{
    char    *line;
    int     fd;
    int     map_width;
    
    fd = open(file_name, O_RDONLY, 0);
    line = get_next_line(fd);
    map_width = count_elements(line, ' ');
    free(line);
    close(fd);
    return (map_width);
}
*/

static void get_map_dimensions(char *file_name, t_map *map)
{
    int     fd;
    char    *line;
    int     flag;

    fd = open(file_name, O_RDONLY, 0);
    map->length = -1;
    map->width = 0;
    line = "";
    flag = 0;
    while(line != NULL)
    {
        line = get_next_line(fd);    
        if (flag == 0)
        {
            map->width = count_elements(line, ' ');
            flag = 1;
        }
        map->length++;
    }
    close(fd);
}
/*
void    map_memory_allocate(t_map *map)
{
    int i;
    
    map->height = malloc((map->length + 1) * sizeof(int *));
    i = 0;
    while (i < map->length)
    {
        map->height[i] = malloc((map->width + 1) * sizeof(int));
        i++;
    }
}
*/
t_map   **map_memory_allocate(t_map *map)
{
    t_map   **map_array;
    int     i;
    
    map_array = (t_map **)malloc((map->length + 1) * sizeof(t_map *));
    i = 0;
    while (i < map->length)
    {
        map_array[i] = (t_map *)malloc((map->width + 1) * sizeof(t_map));
        i++;
    }
    return (map_array);
}

void    fill_map_array(char *file_name, t_map *map, t_map **map_array)
{
    int     fd;
    char    *line;
    char    **splitted_line;
    int     x;
    int     y;

    fd = open(file_name, O_RDONLY, 0);
    y = 0;
    line = NULL;
    while (y < map->length )
    {
       line = get_next_line(fd);
       splitted_line = ft_split(line, ' ');
    //    splitted_line = ft_split(get_next_line(fd), ' ');
        x = 0;
        while (x < map->width)
        {
            map_array[x][y].x = x;
            map_array[x][y].y = y;
            map_array[x][y].z = ft_atoi(splitted_line[x]);
            x++;
        }
        y++;
    }
    close(fd);
}
/*
void    fill_map_array(char *file_name, t_map *map, char **map_array)
{
    int     fd;
    char    *line;
    char    **splitted_line;
    int     i;
    int     j;

    fd = open(file_name, O_RDONLY, 0);
    i = 0;
    line = NULL;
    while (i < map->length )
    {
       line = get_next_line(fd);
       splitted_line = ft_split(line, ' ');
    //    splitted_line = ft_split(get_next_line(fd), ' ');
        j = 0;
        while (j < map->width)
        {
            map_array[i][j] = ft_atoi(splitted_line[j]);
            j++;
        }
        i++;
    }
    close(fd);
}
*/
/*
void    fill_map_array(char *file_name, t_map *map)
{
    int     fd;
    char    *line;
    char    **splitted_line;
    int     i;
    int     j;

    fd = open(file_name, O_RDONLY, 0);
    i = 0;
    line = NULL;
    while (i < map->length )
    {
       line = get_next_line(fd);
       splitted_line = ft_split(line, ' ');
       free(line);
    //    splitted_line = ft_split(get_next_line(fd), ' ');
        j = 0;
        while (j < map->width)
        {
            map->height[i][j] = ft_atoi(splitted_line[j]);
            j++;
            free(splitted_line[j]);
        }
        free(splitted_line);
        i++;
    }
    close(fd);
}
*/
static void print_map(t_map *map, t_map **map_array)
{
    int     i;
    int     j;

    i = 0;

    while (i < map->length)
    {
        j = 0;
        while (j < map->width)
        {
            printf("(%d, %d) = %2d\n", (int)map_array[i][j].x, (int)map_array[i][j].y, (int)map_array[i][j].z);
            j++;
        }
        printf("\n");
        i++;
    }
}

void    read_file(char *file_name, t_map *map)
{
    t_map   **map_array;
    // map->length = get_map_length(file_name);
    // map->width = get_map_width(file_name);
    get_map_dimensions(file_name, map);
    map_array = map_memory_allocate(map);
    fill_map_array(file_name, map, map_array);
    print_map(map, map_array);
}

/*
int main(int argc, char **argv)
{
    t_map   *map;
    int     i;
    int     j;

    (void)argc;
    map = (t_map *)malloc(sizeof(t_map));
    if (map == NULL)
        return (1);
    read_file(argv[1], &(*map));
    i = 0;

    while (i < map->length)
    {
        j = 0;
        while (j < map->width)
        {
            printf("%2d ", map->height[i][j]);
            j++;
        }
        printf("\n");
        i++;
    }
    free(map);
}
*/
/*
int main(int argc, char **argv)
{    
    struct t_map   map;

//    map.width = 0;
//    map.length = -1;
    if (argc == 1)
        write (1, "No file specified!\n", 19);
    else if (argc > 2)
        write (1, "Too may arguments!\n", 20);
    else
        get_map_dimensions(argv[1], &map);
        printf("Width of map is %d\n", map.width);
        printf("Length of map is %d\n", map.length);
    return (0);
}
*/