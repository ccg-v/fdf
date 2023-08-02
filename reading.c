/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 19:32:01 by ccarrace          #+#    #+#             */
/*   Updated: 2023/07/31 20:13:19 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	get_map_dimensions(char *file_name, t_map *map)
{
	int		fd;
	char	*line;
	int		flag;

	fd = open(file_name, O_RDONLY, 0);
	map->length = -1;
	map->width = 0;
	line = "";
	flag = 0;
	while (line != NULL)
	{
		line = get_next_line(fd);
		if (flag == 0 && line)
		{
			map->width = ft_count_columns(line, ' ');
			flag = 1;
		}
		map->length++;
		free(line);
	}
	free(line);
	close(fd);
}

t_vertex	**mesh_memory_allocate(t_vertex **mesh, t_fdf *fdf)
{
	int	i;

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

static void	fill_mesh_row(t_fdf *fdf, int x, int y, char **splitted_line)
{
	while (x < fdf->map->width)
	{
		fdf->map->mesh[y][x].x = x;
		fdf->map->mesh[y][x].y = y;
		fdf->map->mesh[y][x].z = ft_atoi(splitted_line[x]);
		x++;
	}
}

t_vertex	**fill_mesh(char *file_name, t_fdf *fdf)
{
	int		fd;
	char	*line;
	char	**splitted_line;
	int		x;
	int		y;

	fd = open(file_name, O_RDONLY, 0);
	y = 0;
	line = NULL;
	while (y < fdf->map->length)
	{
		line = get_next_line(fd);
		splitted_line = ft_split(line, ' ');
		x = 0;
		fill_mesh_row(fdf, x, y, splitted_line);
		ft_free_array_of_strings(splitted_line);
		free(line);
		y++;
	}
	close(fd);
	return (fdf->map->mesh);
}

void	read_file(char *file_name, t_fdf *fdf)
{
	get_map_dimensions(file_name, fdf->map);
	fdf->map->mesh = mesh_memory_allocate(fdf->map->mesh, fdf);
	fill_mesh(file_name, fdf);
}
