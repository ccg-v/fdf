/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 21:38:42 by ccarrace          #+#    #+#             */
/*   Updated: 2023/07/02 22:05:14 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "minilibx_macos/mlx.h"
#include <math.h>

float	ft_abs(float num)
{
	if (num < 0)
		return (num * -1);
	return (num);
}

void	isometric(t_map *map)
{
	map->x = (map->x - map->y) * cos(0.8);
	map->y = (map->x + map->y) * sin(0.8) - map->z;
}

void	draw_line(t_map start, t_map end, t_map *map)
{
	float	delta_x;
	float	delta_y;
	int	biggest_delta;

	start.x *= map->zoom_factor;
	start.y *= map->zoom_factor;
	end.x *= map->zoom_factor;
	end.y *= map->zoom_factor;

	delta_x = end.x - start.x;
	delta_y = end.y - start.y;
	if (ft_abs(delta_x) >= ft_abs(delta_y))
		biggest_delta = ft_abs(delta_x);
	else
		biggest_delta = ft_abs(delta_y);
	delta_x /= biggest_delta;
	delta_y /= biggest_delta;

	while ((int)(start.x - end.x) || (int)(start.y - end.y))
	{
		mlx_pixel_put(map->mlx_ptr, map->win_ptr, start.x, start.y, 0xffffff);
		start.x += delta_x;
		start.y += delta_y;
	}
}

void	draw_map(t_map **map_array, t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y <= map->length)
	{
		x = 0;
		while (x <= map->width)
		{
			if (x < (map->width))
				draw_line(map_array[x][y], map_array[x + 1][y], map);
			if (y < (map->length))
				draw_line(map_array[x][y], map_array[x][y + 1], map);
			x++;
		}
		y++;
	}
}
