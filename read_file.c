/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 19:32:01 by ccarrace          #+#    #+#             */
/*   Updated: 2023/07/10 21:22:33 by ccarrace         ###   ########.fr       */
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

t_vertex   **mesh_memory_allocate(t_map *map)
{
    // t_map   **map_array;
    int     i;
    
    map->mesh = (t_vertex **)malloc((map->length + 1) * sizeof(t_vertex *));
    i = 0;
    while (i < map->length)
    {
        map->mesh[i] = (t_vertex *)malloc((map->width + 1) * sizeof(t_vertex));
        i++;
    }
    return (map->mesh);
}

t_vertex   **fill_mesh(char *file_name, t_map *map)
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
            map->mesh[x][y].x = x;
            map->mesh[x][y].y = y;
            map->mesh[x][y].z = ft_atoi(splitted_line[x]);
            x++;
        }
        y++;
    }
    close(fd);
    return (map->mesh);
}

static void print_map(t_map *map)
{
    int     i;
    int     j;

    i = 0;
    while (i < map->length)
    {
        j = 0;
        while (j < map->width)
        {
            printf("(%d, %d) = %2d\n", (int)map->mesh[i][j].x, (int)map->mesh[i][j].y, (int)map->mesh[i][j].z);
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
            printf("%3d", (int)map->mesh[i][j].z);
            j++;
        }
        printf("\n");
        i++;
    }
}
/*
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
            printf("(%d, %d) = %2d\n", (int)map_array[i][j].vertex.x, (int)map_array[i][j].vertex.y, (int)map_array[i][j].vertex.z);
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
            printf("%3d", (int)map_array[i][j].vertex.z);
            j++;
        }
        printf("\n");
        i++;
    }
}
*/
t_vertex   **read_file(char *file_name, t_map *map)
{
    t_vertex   **mesh;
    // map->length = get_map_length(file_name);
    // map->width = get_map_width(file_name);
    get_map_dimensions(file_name, map);
    mesh = mesh_memory_allocate(map);
    mesh = fill_mesh(file_name, map);
    print_map(map);
    return (mesh);
}
