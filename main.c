/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 21:38:42 by ccarrace          #+#    #+#             */
/*   Updated: 2023/07/25 00:35:31 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "minilibx_macos/mlx.h"
//#include <stdlib.h>
//#include <math.h>

void	initialize_fdf(t_fdf *fdf, t_img *image)
{
	fdf->win_x = WINDOW_WIDTH;
	fdf->win_y = WINDOW_HEIGHT;
	fdf->mlx_ptr = mlx_init();
	fdf->win_ptr = mlx_new_window(fdf->mlx_ptr, fdf->win_x, fdf->win_y, "FdF");
	image->image = mlx_new_image(fdf->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	image->buffer = mlx_get_data_addr(image->image, &image->bits_per_pixel, \
			&image->line_bytes, &image->endian);
	image->image_bytes = WINDOW_WIDTH * WINDOW_HEIGHT * 4;
	fdf->image = image;
}

/*
void	initialize_image(t_img *img, void *mlx_ptr)
{
	img->image = mlx_new_image(mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	img->buffer = mlx_get_data_addr(img->image, &img->bits_per_pixel, \
			&img->line_bytes, &img->endian);
	img->image_bytes = WINDOW_WIDTH * WINDOW_HEIGHT * 4;
	// img->line = NULL;
}
*/

void	initialize_map(t_map *map)
{
	// map = malloc(sizeof(t_map));
	// if (!map)
	// 	return (NULL);
	map->mesh = NULL;
	map->width = 0;
	map->length = 0;
	map->scale_factor = 25;
	map->min_z = 0;
	map->max_z = 0;
	map->uppermost_point = 0;
	map->lowest_point = 0;
	// return (map);
}

int	main(int argc, char **argv)
{
	t_fdf		fdf;
	t_map		map;
	t_vertex	**mesh;
	t_img		image;

	(void)argv;
	if (argc != 2)
		return (-1);
	else
	{
		initialize_fdf(&fdf, &image);
		initialize_map(&map);
		mesh = read_file(argv[1], &map);
		center_to_origin(&map);
	// printf("--------------- CENTER TO ORIGIN ----------------\n");
	// print_coordenates(&map);
		// clear_image(&(*fdf.image));
		// clear_image(fdf.image);
		// center_to_origin(&map);
		scale_to_fit(&map);
		transform_to_isometric(&map);
		center_in_screen(&map);
		draw_mesh(&fdf, &map);
	// printf("--------------- CENTER ISOMETRIC ----------------\n");
	// print_coordenates(&map);
		// mlx_loop(&(*fdf.mlx_ptr));
		mlx_loop(fdf.mlx_ptr);
		return (0);
	}
}