/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transforming.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 19:17:17 by ccarrace          #+#    #+#             */
/*   Updated: 2023/08/22 01:48:42 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "math.h"

void	scale_to_fit(t_map	*map)
{
	float	scale_x;
	float	scale_y;
	int		x;
	int		y;

	ft_putstr_fd("\nscale to fit:\n", 1);
	scale_x = WINDOW_WIDTH / map->width;
	scale_y = WINDOW_HEIGHT / map->length;
	map->scale_factor = ft_find_min_value(scale_x, scale_y);
	ft_putnbr_fd(map->scale_factor, 1);
	y = 0;
	while (y < map->length)
	{
		x = 0;
		while (x < map->width)
		{
			map->mesh[y][x].x *= map->scale_factor;
			map->mesh[y][x].y *= map->scale_factor;
			map->mesh[y][x].z *= map->scale_factor;
			x++;
		}
		y++;
	}
	print_coordenates(map);
}

void	transform_to_isometric(t_map *map)
{
	int		x;
	int		y;
	float	iso_x;
	float	iso_y;

	ft_putstr_fd("\ntransform to isometric:\n", 1);
	y = 0;
	while (y < map->length)
	{
		x = 0;
		while (x < map->width)
		{
			iso_x = (map->mesh[y][x].x - map->mesh[y][x].y) \
					* cos(deg_to_rad(30));
			iso_y = (map->mesh[y][x].x + map->mesh[y][x].y) \
					* sin(deg_to_rad(30)) - map->mesh[y][x].z;
			map->mesh[y][x].x = iso_x;
			map->mesh[y][x].y = iso_y;
			x++;
		}
		y++;
	}
	print_coordenates(map);
}

void	translate(t_map *map, int x_displacement, int y_displacement)
{
	int	x;
	int	y;
	int	translated_x;
	int	translated_y;

	ft_putstr_fd("\ntranslate:\n", 1);
	y = 0;
	while (y < map->length)
	{
		x = 0;
		while (x < map->width)
		{
			translated_x = map->mesh[y][x].x + x_displacement;
			translated_y = map->mesh[y][x].y + y_displacement;
			map->mesh[y][x].x = translated_x;
			map->mesh[y][x].y = translated_y;
			x++;
		}
		y++;
	}
	print_coordenates(map);
}

void	z_scale(t_map *map)
{
	int		x;
	int		y;
	float	scaled_z;

	ft_putstr_fd("\nz scale:\n", 1);
	scaled_z = 0.0;
	y = 0;
	while (y < map->length)
	{
		x = 0;
		while (x < map->width)
		{
			scaled_z = map->mesh[y][x].z * map->z_scale_factor;
			map->mesh[y][x].z = scaled_z;
			x++;
		}
		y++;
	}
	print_coordenates(map);
}
