/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 21:38:42 by ccarrace          #+#    #+#             */
/*   Updated: 2023/07/06 19:29:32 by ccarrace         ###   ########.fr       */
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
	map->vertex.x = (map->vertex.x - map->vertex.y) * cos(0.8);
	map->vertex.y = (map->vertex.x + map->vertex.y) * sin(0.8) - map->vertex.z;
}

void	draw_line(t_map start, t_map end, t_map *map)
{
	float	delta_x;
	float	delta_y;
	int	biggest_delta;

	start.vertex.x *= map->zoom_factor;
	start.vertex.y *= map->zoom_factor;
	end.vertex.x *= map->zoom_factor;
	end.vertex.y *= map->zoom_factor;

	delta_x = end.vertex.x - start.vertex.x;
	delta_y = end.vertex.y - start.vertex.y;
	if (ft_abs(delta_x) >= ft_abs(delta_y))
		biggest_delta = ft_abs(delta_x);
	else
		biggest_delta = ft_abs(delta_y);
	delta_x /= biggest_delta;
	delta_y /= biggest_delta;

	while ((int)(start.vertex.x - end.vertex.x) || (int)(start.vertex.y - end.vertex.y))
	{
		mlx_pixel_put(map->mlx_ptr, map->win_ptr, start.vertex.x, start.vertex.y, 0xffffff);
		start.vertex.x += delta_x;
		start.vertex.y += delta_y;
	}
}
/*
void	draw_map(t_map **map_array, t_map *map)
{
	int	x;
	int	y;
	y = 0;
	while (y < map->length)
	{
		x = 0;
		while (x < map->width)
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
*/