/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 21:38:42 by ccarrace          #+#    #+#             */
/*   Updated: 2023/08/22 00:54:06 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"

void	initialize_map(t_map *map, char *map_file)
{
	map->map_file = map_file;
	map->mesh = NULL;
	map->mesh_copy = NULL;
	map->width = 0;
	map->length = -1;
	map->scale_factor = 1;
	map->z_scale_factor = 1;
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
	on_error_exit(ERR_USER_END);
	return (0);
}

void	on_error_exit(char *error_code)
{
	ft_putstr_fd(error_code, 2);
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	t_fdf		fdf;
	t_map		map;
	t_img		image;

	if (argc != 2)
		on_error_exit(ERR_NUM_ARGS);
	else
	{
		check_input(argc, argv[1]);
		initialize_map(&map, argv[1]);
		initialize_fdf(&fdf, &map, &image);
		read_file(argv[1], &fdf);
		print_altitudes(&map);
		ft_putstr_fd("\nmap of coordenates:\n", 1);
		print_coordenates(&map);
		center_to_origin(fdf.map);
		scale_to_fit(fdf.map);
		do_mesh_copy(fdf.map->mesh, &fdf.map->mesh_copy, &fdf);
		center_in_screen(fdf.map);
		draw_mesh(&fdf);
		mlx_hook(fdf.win_ptr, 17, 0, close_all, &fdf);
		mlx_key_hook(fdf.win_ptr, &key_handle, &fdf);
		mlx_loop(fdf.mlx_ptr);
		return (0);
	}
}
