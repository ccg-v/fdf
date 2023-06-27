/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 19:32:01 by ccarrace          #+#    #+#             */
/*   Updated: 2023/06/27 21:55:44 by ccarrace         ###   ########.fr       */
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

void    read_file(char *file_name, t_map *map)
{
    int     fd;
    char    *line;
    char    **splitted_line;
    int     i;
    int     j;

    // map->length = get_map_length(file_name);
    // map->width = get_map_width(file_name);
    get_map_dimensions(file_name, &(*map));
    map->height = malloc((map->length + 1) * sizeof(int *));
    i = 0;
    while (i < map->length)
    {
        map->height[i] = malloc((map->width + 1) * sizeof(int));
        i++;
    }
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