/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 21:38:42 by ccarrace          #+#    #+#             */
/*   Updated: 2023/07/28 13:20:44 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "minilibx_macos/mlx.h"

void	initialize_map(t_map *map, char *map_file)
{
	map->map_file = map_file;
	map->mesh = NULL;
	map->width = 0;
	map->length = 0;
	map->scale_factor = 1;
	map->min_z = 0;
	map->max_z = 0;
	map->uppermost_point = 0;
	map->lowest_point = 0;
	map->projection = TOP;
}

void	initialize_fdf(t_fdf *fdf, t_map *map, t_img *image)
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
	fdf->map = map;
}

int	close_all(t_fdf *fdf)
{
	mlx_destroy_image(fdf->mlx_ptr, fdf->image->image);
	mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
	on_error_exit(fdf->exit_code);
	return (0);
}

void	render(t_fdf *fdf)
{
	// t_vertex	**mesh;

	// mesh = read_file(fdf->map->map_file, fdf->map);
	// center_to_origin(fdf->map);
	// scale_to_fit(fdf->map);
	if (fdf->map->projection == ISOMETRIC)
	{
		return_to_origin(fdf->map);
		transform_to_isometric(fdf->map);
	}
	else if (fdf->map->projection == TOP)
		return_to_origin(fdf->map);
	// scale_to_fit(fdf->map);
	center_in_screen(fdf->map);
	draw_mesh(fdf);
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
		initialize_map(&map, argv[1]);
		initialize_fdf(&fdf, &map, &image);
		mesh = read_file(argv[1], fdf.map);
		center_to_origin(fdf.map);
		scale_to_fit(fdf.map);
		// if (fdf.map->projection == ISOMETRIC)
		// 	transform_to_isometric(fdf.map);
		center_in_screen(fdf.map);
		draw_mesh(&fdf);
		// render(&fdf);
	// printf("--------------- CENTER ISOMETRIC ----------------\n");
	// print_coordenates(&map);
		// fdf.exit_code = 0;
		mlx_hook(fdf.win_ptr, 17, 0, close_all, &fdf);
		// mlx_hook(fdf.win_ptr, 2, 0, key_handle, &container);
		mlx_key_hook(fdf.win_ptr, &key_handle, &fdf);
		mlx_loop(fdf.mlx_ptr);
		return (0);
	}
}