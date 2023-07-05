/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 21:38:42 by ccarrace          #+#    #+#             */
/*   Updated: 2023/07/05 18:37:36 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "minilibx_macos/mlx.h"
//#include <stdlib.h>
//#include <math.h>

int	set_default_values(t_map *map)
{
	map->win_x = 600;
	map->win_y	= 600;
	if (!(map->mlx_ptr = mlx_init()))
	{
		printf("Error: no mlx_ptr!\n");
		return (-1);
	}
	else
		printf("mlx->ptr = %p\n", map->mlx_ptr);
	// map->mlx_ptr = mlx_init();
	if (!(map->win_ptr = mlx_new_window(map->mlx_ptr, map->win_x, \
		map->win_y, "FDF by ccarrace")))
	{
		printf("Error: no win->ptr!\n");
		return (-1);
	}
	else
		printf("map->win_ptr = %p\n", map->win_ptr);
	map->zoom_factor = 20;
	return (0);
}

int	main(int argc, char **argv)
{
	t_map	*map;
	t_map	**map_array;

	if (argc != 2)
		return (-1);
	else
	{
		map = (t_map *)malloc(sizeof(t_map));
		if (map == NULL)
			return (-1);
		map_array = read_file(argv[1], map);
		map->mlx_ptr = mlx_init();
		map->win_ptr = mlx_new_window(map->mlx_ptr, 2000, 1000, "FdF by ccarrace");
	//	mlx_pixel_put(map->mlx_ptr, map->win_ptr, 1000/2, 1000/2, 0x00FF00);	//	Displays a pixel centered in the window
	//	draw_line(0, 0, 1000, 1000, map);	//	Displays a line from corner to corner of the window
		map->zoom_factor = 25;
		draw_map(map_array, map);
		mlx_loop(map->mlx_ptr);
		return (0);
	}
}