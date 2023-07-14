/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 21:38:42 by ccarrace          #+#    #+#             */
/*   Updated: 2023/07/15 01:03:52 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "minilibx_macos/mlx.h"
//#include <stdlib.h>
//#include <math.h>

t_fdf	*initialize_fdf(void)
{
	t_fdf	*fdf;

	fdf = malloc(sizeof(t_fdf));
	if (!fdf)
		on_error_exit(0);
	fdf->mlx_ptr = mlx_init();
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, fdf->win_x, fdf->win_y, "FdF");
	fdf->win_x = WINDOW_WIDTH;
	fdf->win_y = WINDOW_HEIGHT;
	// fdf->image = initialize_image(fdf->mlx_ptr);
	// if (!fdf->image)
	// 	return (NULL);
	fdf->image = NULL;
	return (fdf);
}

t_img	*initialize_image(void *mlx_ptr)
{
	t_img	*img;

	img = malloc(sizeof(t_img));
	if (!img)
		return (NULL);
	img->image = mlx_new_image(mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	img->buffer = mlx_get_data_addr(img->image, &img->bits_per_pixel, \
			&img->size_line, &img->endian);
	// img->line = NULL;
	return(img);
}

t_map	*initialize_map(void)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->mesh = NULL;
	map->width = 0;
	map->length = 0;
	map->zoom_factor = 0;
	return (map);
}

/*
t_fdf	*set_default_values(t_fdf *fdf)
{ 
	// fdf = malloc(sizeof(t_fdf));
	// if (!fdf)
	// 	on_error_exit(0);
	// fdf->win_x = WINDOW_WIDTH;
	// fdf->win_y	= WINDOW_HEIGHT;
	// fdf->mlx_ptr = mlx_init();
	// fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, fdf->win_x, fdf->win_y, "FdF");
	initialize_fdf()
	initialize_image(fdf->mlx_ptr);
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
*/

int	main(int argc, char **argv)
{
	t_fdf		*fdf;
	t_map		*map;
	t_vertex	**mesh;
	t_img		*image;
	// t_line		*line;

	if (argc != 2)
		return (-1);
	else
	{
		fdf = initialize_fdf();
		map = initialize_map();
		image = initialize_image(fdf->mlx_ptr);
		// fdf = NULL;
		// map = malloc(sizeof(t_map));
		// if (!map)
		// 	on_error_exit(3);
		// fdf = set_default_values(fdf);
		mesh = read_file(argv[1], map);
		fdf->image = initialize_image(fdf->mlx_ptr);
		map->zoom_factor = 25;
		// line = malloc(sizeof(t_line));
		// if (!line)
		// 	on_error_exit(4);
		build_image(image, map, 0xffffff);
		draw_map(fdf, map);
		mlx_loop(fdf->mlx_ptr);
		return (0);
	}
}