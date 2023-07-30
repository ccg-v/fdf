/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 19:32:01 by ccarrace          #+#    #+#             */
/*   Updated: 2023/07/31 00:40:37 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
int map_width;
int map_length;

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
map_width = map->width;
        }
map_length = map->length;
        map->length++;
        free(line); 
    }
    close(fd);
}

t_vertex   **mesh_memory_allocate(t_vertex **mesh, t_fdf *fdf)
{
    int     i;
    
    mesh = (t_vertex **)malloc((fdf->map->length + 1) * sizeof(t_vertex *));
    if (!mesh)
        return (NULL);
    i = 0;
    while (i < fdf->map->length)
    {
        mesh[i] = (t_vertex *)malloc((fdf->map->width + 1) * sizeof(t_vertex));
        if (!mesh[i])
            return (NULL);
        i++;
    }
    return (mesh);
}

// t_vertex   **mesh_memory_allocate(t_map *map)
// {
//     // t_map   **map_array;
//     int     i;
    
//     map->mesh = (t_vertex **)malloc((map->length + 1) * sizeof(t_vertex *));
//     if (!map->mesh)
//         return (NULL);
//     i = 0;
//     while (i < map->length)
//     {
//         map->mesh[i] = (t_vertex *)malloc((map->width + 1) * sizeof(t_vertex));
//         if (!map->mesh[i])
//             return (NULL);
//         i++;
//     }
//     return (map->mesh);
// }

void	ft_free_array_of_strings(char **argv)
{
	int	i;

	i = 0;
	if (argv == NULL || *argv == NULL)
		return ;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

/*  Remember: y is the line, x is the column    */
/*  Fill the mesh with each point's coordinates */
/*  and save the maximum and minimun z values   */
t_vertex   **fill_mesh(char *file_name, t_fdf *fdf)
{
    int     fd;
    char    *line;
    char    **splitted_line;
    int     x;
    int     y;

    fd = open(file_name, O_RDONLY, 0);
    y = 0;
    line = NULL;
void *map_address = (void *)fdf->map;
int map_width = fdf->map->width;
int map_length = fdf->map->length;
void *mesh_address = (void *)fdf->map->mesh;
printf ("fdf->map address = %p\n", map_address);
printf ("map->width = %d\n", map_width);
printf ("map->length = %d\n", map_length);
printf ("fdf->map->mesh = %p\n", mesh_address);
    while (y < fdf->map->length)
    {
       line = get_next_line(fd);
       splitted_line = ft_split(line, ' ');
    //    splitted_line = ft_split(get_next_line(fd), ' ');
        x = 0;
        while (x < fdf->map->width)
        {
            fdf->map->mesh[y][x].x = x; //- (map->width / 2);
            fdf->map->mesh[y][x].y = y; //- (map->length / 2);
            fdf->map->mesh[y][x].z = ft_atoi(splitted_line[x]);
            if (fdf->map->mesh[y][x].z < fdf->map->min_z)
                fdf->map->min_z = fdf->map->mesh[y][x].z;
            if (fdf->map->mesh[y][x].z > fdf->map->max_z)
                fdf->map->max_z = fdf->map->mesh[y][x].z;               
            x++;
        }
        y++;
        free(line);
        ft_free_array_of_strings(splitted_line);
    }   
    close(fd);
    return (fdf->map->mesh);
}

void    read_file(char *file_name, t_fdf *fdf)
{
    get_map_dimensions(file_name, fdf->map);
    fdf->map->mesh = mesh_memory_allocate(fdf->map->mesh, fdf);
    fill_mesh(file_name, fdf);
	// center_to_origin(map);
    // print_altitudes(map);
    // printf("\n------- array of coordenates -------\n"); 
    // print_coordenates(map);
}

void    do_mesh_copy(t_vertex **src_mesh, t_vertex ***dst_mesh, t_fdf *fdf)
{
    int x;
    int y;
    if (*dst_mesh == NULL)
        *dst_mesh = mesh_memory_allocate(src_mesh, fdf);
    y = 0;
    while(y < fdf->map->length)
    {
        x = 0;
        while (x < fdf->map->width)
        {
            (*dst_mesh)[y][x].x = src_mesh[y][x].x;
            (*dst_mesh)[y][x].y = src_mesh[y][x].y;
            (*dst_mesh)[y][x].z = src_mesh[y][x].z;
            x++;
        }
        y++; 
    }
	printf("\n----------------- ORIGINAL MESH -----------------\n");
    print_coordenates(fdf->map, src_mesh);
	printf("\n------------------- MESH COPY -------------------\n");
    print_coordenates(fdf->map, *dst_mesh); 
}

// t_vertex   **do_mesh_copy(t_fdf *fdf);
// {
//     t_vertex    **source_mesh;
//     t_vertex    **mesh_copy;
//     int         x;
//     int         y;

//     source_mesh = fdf->map->mesh;
//     mesh_copy = fdf->map->mesh_copy;
//     mesh_copy = mesh_memory_allocate(fdf->map);
//     y = 0;
//     while(y < fdf->map->length)
//     {
//         x = 0;
//         while (x < fdf->map->width)
//         {
//             mesh_copy[y][x].x = original_mesh[y][x].x;
//             mesh_copy[y][x].y = original_mesh[y][x].y;
//             mesh_copy[y][x].z = original_mesh[y][x].z;
//             x++;
//         }
//         y++; 
//     }
// 	printf("\n----------------- ORIGINAL MESH -----------------\n");
//     print_coordenates(fdf->map, original_mesh);
// 	printf("\n------------------- MESH COPY -------------------\n");
//     print_coordenates(fdf->map, mesh_copy);
//     return (mesh_copy);   
// }