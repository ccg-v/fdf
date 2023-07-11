/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 21:38:42 by ccarrace          #+#    #+#             */
/*   Updated: 2023/07/11 21:00:15 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "minilibx_macos/mlx.h"
//#include <stdlib.h>
//#include <math.h>

t_fdf	*set_default_values(t_fdf *fdf)
{ 
	fdf = malloc(sizeof(t_fdf));
	if (!fdf)
		on_error_exit(0);
	fdf->win_x = 2560;
	fdf->win_y	= 1440;
	fdf->mlx_ptr = mlx_init();
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, fdf->win_x, fdf->win_y, "FdF");
	// if (!(fdf->mlx_ptr = mlx_init()))
	// 	on_error_exit(1);
	// else
	// 	printf("mlx->ptr = %p\n", fdf->mlx_ptr);
	// if (!(fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, fdf->win_x, \
	// 	fdf->win_y, "FDF by ccarrace")))
	// 	on_error_exit(2);
	// else
	// 	printf("map->win_ptr = %p\n", fdf->win_ptr);
	return (fdf);
}

int	main(int argc, char **argv)
{
	t_fdf		*fdf;
	t_map		*map;
	t_vertex	**mesh;
	// t_line		*line;

	if (argc != 2)
		return (-1);
	else
	{
		fdf = NULL;
		map = malloc(sizeof(t_map));
		if (!map)
			on_error_exit(3);
		fdf = set_default_values(fdf);
		mesh = read_file(argv[1], map);
		map->zoom_factor = 25;
		// line = malloc(sizeof(t_line));
		// if (!line)
		// 	on_error_exit(4);
		draw_map(fdf, map);
		mlx_loop(fdf->mlx_ptr);
		return (0);
	}
}