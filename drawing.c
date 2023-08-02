/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 21:38:42 by ccarrace          #+#    #+#             */
/*   Updated: 2023/07/31 17:46:56 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include "math.h"

void	clear_image(t_img *image, int image_bytes)
{
	int	x;
	int	y;

	ft_bzero(image->buffer, image_bytes);
	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			put_pixel_to_image(image, x, y, 0x000000);
			x++;
		}
		y++;
	}
}

void	put_pixel_to_image(t_img *image, int x, int y, int color)
{
	char	*pixel;

	if (x > 0 && y > 0 && x < WINDOW_WIDTH && y < WINDOW_HEIGHT)
	{
		pixel = image->buffer + (y * image->line_bytes + x * \
			(image->bits_per_pixel / 8));
		*(int *)pixel = color;
	}
}

void	draw_line(t_fdf *fdf, t_vertex start, t_vertex end)
{
	float	delta_x;
	float	delta_y;
	int		biggest_delta;

	delta_x = end.x - start.x;
	delta_y = end.y - start.y;
	if (ft_abs(delta_x) >= ft_abs(delta_y))
		biggest_delta = ft_abs(delta_x);
	else
		biggest_delta = ft_abs(delta_y);
	delta_x /= biggest_delta;
	delta_y /= biggest_delta;
	while (biggest_delta > 0)
	{
		put_pixel_to_image(fdf->image, start.x, start.y, 0xffffff);
		start.x += delta_x;
		start.y += delta_y;
		biggest_delta--;
	}
}

void	draw_mesh(t_fdf *fdf)
{
	int	y;
	int	x;
	int	image_bytes;

	image_bytes = WINDOW_WIDTH * WINDOW_HEIGHT * 4;
	clear_image(fdf->image, image_bytes);
	y = 0;
	while (y < fdf->map->length)
	{
		x = 0;
		while (x < fdf->map->width)
		{
			if (x < (fdf->map->width - 1))
				draw_line(fdf, fdf->map->mesh[y][x], fdf->map->mesh[y][x + 1]);
			if (y < (fdf->map->length - 1))
				draw_line(fdf, fdf->map->mesh[y][x], fdf->map->mesh[y + 1][x]);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, \
		fdf->image->image, 0, 0);
	display_menu(fdf);
}
