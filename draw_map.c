/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 21:38:42 by ccarrace          #+#    #+#             */
/*   Updated: 2023/07/11 20:58:53 by ccarrace         ###   ########.fr       */
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

/*
void	isometric(t_map *map)
{
	map->mesh.x = (map->mesh.x - map->mesh.y) * cos(0.8);
	map->mesh.y = (map->mesh.x + map->mesh.y) * sin(0.8) - map->mesh.z;
}
*/

void	draw_line(t_fdf *fdf, t_map *map, t_vertex start, t_vertex end)
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
	// while (biggest_delta > 0)
	{
		mlx_pixel_put(fdf->mlx_ptr, fdf->win_ptr, start.x, start.y, 0xffffff);
		start.x += delta_x;
		start.y += delta_y;
		biggest_delta--;
	}
}

void	draw_map(t_fdf *fdf, t_map *map)
{
	int	x;
	int	y;
	y = 0;
	while (y < map->length)
	{
		x = 0;
		while (x < map->width)
		{
			if (x < (map->width - 1))
				draw_line(fdf, map, map->mesh[x][y], map->mesh[x + 1][y]);
			if (y < (map->length - 1))
				draw_line(fdf, map, map->mesh[x][y], map->mesh[x][y + 1]);
			x++;
		}
		y++;
	}
}

/*
void	draw_map(t_vertex **map_array, t_map *map)
{
	int	x;
	int	y;
	y = 0;
	while (y < map->length)
	{
		x = 0;
		while (x < map->width)
		{
			if (x < (map->width - 1))
				draw_line(map_array[x][y].vertex.z, map_array[x + 1][y].vertex.z, map);
			if (y < (map->length - 1))
				draw_line(map_array[x][y].vertex.z, map_array[x][y + 1].vertex.z, map);
			x++;
		}
		y++;
	}
}
*/