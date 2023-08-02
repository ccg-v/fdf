/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   centering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 17:17:53 by ccarrace          #+#    #+#             */
/*   Updated: 2023/08/02 12:21:21 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	center_to_origin(t_map *map)
{
	int	x;
	int	y;

	ft_putstr_fd("center to origin:\n", 1);
	y = 0;
	while (y < map->length)
	{
		x = 0;
		while (x < map->width)
		{
			if ((map->width % 2) > 0)
				map->mesh[y][x].x -= (map->width / 2); 
			else
				map->mesh[y][x].x -= (map->width / 2) - 0.5;
			if ((map->length % 2) > 0)
				map->mesh[y][x].y -= (map->length / 2);
			else
				map->mesh[y][x].y -= (map->length / 2) - 0.5;
			x++;
		}
		y++;
	}
	print_coordenates(map);
}

void	return_to_origin(t_map *map)
{
	int	x;
	int	y;

	ft_putstr_fd("return to origin:\n", 1);
	y = 0;
	while (y < map->length)
	{
		x = 0;
		while (x < map->width)
		{
			map->mesh[y][x].x -= (WINDOW_WIDTH / 2);
			map->mesh[y][x].y -= (WINDOW_HEIGHT / 2);
			x++;
		}
		y++;
	}
	print_coordenates(map);
}

void	center_in_screen(t_map *map)
{
	int		x;
	int		y;
	float	centered_x;
	float	centered_y;

	ft_putstr_fd("center in screen:\n", 1);
	y = 0;
	while (y < map->length)
	{
		x = 0;
		while (x < map->width)
		{
			centered_x = map->mesh[y][x].x + (WINDOW_WIDTH / 2);
			centered_y = map->mesh[y][x].y + (WINDOW_HEIGHT / 2);
			map->mesh[y][x].x = centered_x;
			map->mesh[y][x].y = centered_y;
			x++;
		}
		y++;
	}
	print_coordenates(map);
}
