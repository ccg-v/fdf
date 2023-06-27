/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 21:38:42 by ccarrace          #+#    #+#             */
/*   Updated: 2023/06/27 21:05:31 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "minilibx_macos/mlx.h"
#include <math.h>

/* gcc -Wall -Wextra -Werror -I minilibx_macos draw_line.c minilibx_macos/libmlx.a -framework OpenGL -framework AppKit */

float	ft_abs(float num)
{
	if (num < 0)
		return (num * -1);
	return (num);
}

void	draw_line(float x0, float x1, float y0, float y1, t_map map)
{
	float	delta_x;
	float	delta_y;
	int	biggest_delta;

	delta_x = x1 - x0;
	delta_y = y1 - y0;
	if (ft_abs(delta_x) >= ft_abs(delta_y))
		biggest_delta = ft_abs(delta_x);
	else
		biggest_delta = ft_abs(delta_y);
	delta_x /= biggest_delta;
	delta_y /= biggest_delta;

	while ((int)(x0 - x1) || (int)(y0 - y1))
	{
		mlx_pixel_put(map.mlx_ptr, map.win_ptr, x0, y0, 0xffffff);
		x0 += delta_x;
		y0 += delta_y;
	}
}

void	draw_map(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->length)
	{
		x = 0;
		while (x < map->width)
		{
			draw_line(x, y, x + 1, y, *map);
			draw_line(x, y, x, y + 1, *map);
			x++;
		}
		y++;
	}
}

int	main(int argc, char **argv)
{
	t_map	*map;
	
	if (argc != 2)
		return (-1);
	else
	{
		map = (t_map *)malloc(sizeof(t_map));
		if (map == NULL)
			return (-1);
		read_file(argv[1], map);
		map->mlx_ptr = mlx_init();
		map->win_ptr = mlx_new_window(map->mlx_ptr, 1000, 1000, "FdF by ccarrace");
	//	mlx_pixel_put(map->mlx_ptr, map->win_ptr, 1000/2, 1000/2, 0x00FF00);	//	Displays a pixel centered in the window
	//	draw_line(0, 1000, 0, 1000, *map);	//	Displays a line from side to side of the window
		draw_map(map);
		mlx_loop(map->mlx_ptr);
		return (0);
	}
}

/*
void	draw_line(void *mlx_ptr, void *win_ptr, int beginX, int beginY, int endX, int endY, int color)
{
	double	deltaX = endX - beginX;
	double	deltaY = endY - beginY;
	double	pixelX;
	double	pixelY;

	int	pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));

	deltaX /= pixels;
	deltaY /= pixels;
	pixelX = beginX;
	pixelY = beginY;
	while (pixels)
	{
		mlx_pixel_put(mlx_ptr, win_ptr, pixelX, pixelY, color);
		pixelX += deltaX;
		pixelY += deltaY;
		--pixels;
	}
}

int	main(void)
{
	void	*mlx_ptr;
	void	*win_ptr;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 1000, 1000, "FdF by ccarrace");
	mlx_pixel_put(mlx_ptr, win_ptr, 1000/2, 1000/2, 0x00FF00);	//	Displays a pixel centered in the window
	draw_line(mlx_ptr, win_ptr, 0, 0, 1000, 1000, 0xFFFFFF);	//	Displays a line from side to side of the window
	mlx_loop(mlx_ptr);
	return (0);
}
*/
