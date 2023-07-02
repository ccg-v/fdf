/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 19:32:01 by ccarrace          #+#    #+#             */
/*   Updated: 2023/07/02 21:15:13 by ccarrace         ###   ########.fr       */
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

t_map   **fill_map_array(char *file_name, t_map *map, t_map **map_array)
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
    return (map_array);
}

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
    i = 0;
    while (i < map->length)
    {
        j = 0;
        while (j < map->width)
        {
            printf("%3d", (int)map_array[i][j].z);
            j++;
        }
        printf("\n");
        i++;
    }
}

t_map   **read_file(char *file_name, t_map *map)
{
    t_map   **map_array;
    // map->length = get_map_length(file_name);
    // map->width = get_map_width(file_name);
    get_map_dimensions(file_name, map);
    map_array = map_memory_allocate(map);
    map_array = fill_map_array(file_name, map, map_array);
    print_map(map, map_array);
    return (map_array);
}