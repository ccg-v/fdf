/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 19:32:01 by ccarrace          #+#    #+#             */
/*   Updated: 2023/07/27 14:16:48 by ccarrace         ###   ########.fr       */
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

static int	count_columns(const char *str, char c)
{
	int	i;
	int	num_columns;

	i = 0;
	num_columns = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i] != c && str[i] != '\n')
			num_columns++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (num_columns);
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
            map->width = count_columns(line, ' ');
            flag = 1;
        }
        map->length++;
    }
    close(fd);
    fd = open(file_name, O_RDONLY, 0);
    lseek(fd, 0, SEEK_SET);
    close(fd);
}

t_vertex   **mesh_memory_allocate(t_map *map)
{
    // t_map   **map_array;
    int     i;
    
    map->mesh = (t_vertex **)malloc((map->length + 1) * sizeof(t_vertex *));
    if (!map->mesh)
        return (NULL);
    i = 0;
    while (i < map->length)
    {
        map->mesh[i] = (t_vertex *)malloc((map->width + 1) * sizeof(t_vertex));
        
        i++;
    }
    return (map->mesh);
}

/*  Remember: y is the line, x is the column    */
/*  Fill the mesh with each point's coordinates */
/*  and save the maximum and minimun z values   */
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
    while (y < map->length)
    {
       line = get_next_line(fd);
       splitted_line = ft_split(line, ' ');
    //    splitted_line = ft_split(get_next_line(fd), ' ');
        x = 0;
        while (x < map->width)
        {
            map->mesh[y][x].x = x; //- (map->width / 2);
            map->mesh[y][x].y = y; //- (map->length / 2);
            map->mesh[y][x].z = ft_atoi(splitted_line[x]);
            if (map->mesh[y][x].z < map->min_z)
                map->min_z = map->mesh[y][x].z;
            if (map->mesh[y][x].z > map->max_z)
                map->max_z = map->mesh[y][x].z;               
            x++;
        }
        y++;
    }
    close(fd);
    return (map->mesh);
}

t_vertex   **read_file(char *file_name, t_map *map)
{
    t_vertex   **mesh;
    // map->length = get_map_length(file_name);
    // map->width = get_map_width(file_name);
    get_map_dimensions(file_name, map);
    mesh = mesh_memory_allocate(map);
    mesh = fill_mesh(file_name, map);
	// center_to_origin(map);
    print_altitudes(map);
    printf("\n------- array of coordenates -------\n"); 
    print_coordenates(map);
    return (mesh);
}
