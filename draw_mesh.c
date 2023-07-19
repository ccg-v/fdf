/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mesh.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 21:38:42 by ccarrace          #+#    #+#             */
/*   Updated: 2023/07/16 19:51:44 by ccarrace         ###   ########.fr       */
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

float	deg_to_rad(float deg_angle)
{
	float	rad_angle;

	rad_angle = (deg_angle * M_PI) / 180;
	return (rad_angle);
}

void	clear_image(t_img *image)
{
	int	x;
	int	y;

	ft_bzero(image->buffer, image->image_bytes);
	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			put_pixel_to_image(image, x, y, 0x008000);
			x++;
		}
	}
	y++;
}

void	put_pixel_to_image(t_img *image, int x, int y, int color)
{
    char    *pixel;

    pixel = image->buffer + (y * image->line_bytes + x * (image->bits_per_pixel / 8));
    *(int *)pixel = color;
}

/*
void	put_pixel_to_image(t_img *image, float x, float y, int color)
{
	int		pixel;

	pixel = ((int)y * image->line_bytes) + ((int)x * 4);
	if (image->endian == 1)
	{
		image->buffer[pixel + 0] = (color >> 24);
		image->buffer[pixel + 1] = (color >> 16) & 0xff;
		image->buffer[pixel + 2] = (color >> 8) & 0xff;
		image->buffer[pixel + 3] = (color) & 0xff;
	}
	else if (image->endian == 0)
	{
		image->buffer[pixel + 0] = (color) & 0xff;
		image->buffer[pixel + 1] = (color >> 8) & 0xff;
		image->buffer[pixel + 2] = (color >> 16) & 0xff;
		image->buffer[pixel + 3] = (color >> 24);
	}
}
*/

void	draw_line(t_fdf *fdf, t_map *map, t_vertex start, t_vertex end)
{
	float	delta_x;
	float	delta_y;
	int		biggest_delta;

	start.x *= map->scale_factor;
	start.y *= map->scale_factor;
	start.z *= map->scale_factor;
	end.x *= map->scale_factor;
	end.y *= map->scale_factor;
	end.z *= map->scale_factor;

	to_isometric(&start, &end);
	// center_in_image(map, &start, &end);
	center_isometric(&start, &end);
	// center_to_origin(map);

	delta_x = end.x - start.x;
	delta_y = end.y - start.y;
	if (ft_abs(delta_x) >= ft_abs(delta_y))
		biggest_delta = ft_abs(delta_x);
	else
		biggest_delta = ft_abs(delta_y);
	delta_x /= biggest_delta;
	delta_y /= biggest_delta;

	// while ((int)(start.x - end.x) || (int)(start.y - end.y))
	while (biggest_delta > 0)
	{
		put_pixel_to_image(fdf->image, start.x, start.y, 0xffffff);
		start.x += delta_x;
		start.y += delta_y;
		biggest_delta--;
	}
}

void	draw_mesh(t_fdf *fdf, t_map *map)
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
	mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr , fdf->image->image, 0, 0);
}

void	center_isometric(t_vertex *start, t_vertex *end)
{
	t_vertex	new_start;
	t_vertex	new_end;


	new_start.x = start->x + (WINDOW_WIDTH / 2);
	new_start.y = start->y + (WINDOW_HEIGHT / 2);
	start->x = new_start.x;
	start->y = new_start.y;
	new_end.x = end->x + (WINDOW_WIDTH / 2);
	new_end.y = end->y + (WINDOW_HEIGHT / 2);
	printf("CENTER IN SCREEN  : (%d, %d)-->(%d, %d) becomes (%d, %d)-->(%d, %d)\n", (int)start->x, (int)start->y, (int)end->x, (int)end->y, (int)new_start.x, (int)new_start.y, (int)new_end.x, (int)new_end.y);
	end->x = new_end.x;
	end->y = new_end.y;
}

void	center_to_origin(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->length)
	{
		x = 0;
		while (x < map->width)
		{
			if ((map->width % 2) > 0)
			{
				map->mesh[y][x].x -= (map->width / 2);
				map->mesh[y][x].y -= (map->length / 2);
			}
			else
			{
				map->mesh[y][x].x -= (map->width / 2) - 0.5;
				map->mesh[y][x].y -= (map->length / 2) - 0.5;				
			}
			x++;
		}
		y++;
	}
}

void	to_isometric(t_vertex *start, t_vertex *end)
{
	t_vertex	new_start;
	t_vertex	new_end;

	// map->scale_factor /= 2;

	// printf("map->scale_factor = %d\n", map->scale_factor);
	new_start.x = (start->x - start->y) * cos(deg_to_rad(30));
	new_start.y = (start->x + start->y) * sin(deg_to_rad(30)) - start->z;
	// printf("------------------- ISOMETRIC -------------------\n");
	// printf("start:(%d, %d, %d) becomes new_start:(%d, %d, %d)\n", (int)start->x, (int)start->y, (int)start->z, (int)new_start.x, (int)new_start.y, (int)start->z);
	start->x = new_start.x;
	start->y = new_start.y;
	new_end.x = (end->x - end->y) * cos(deg_to_rad(30));
	new_end.y = (end->x + end->y) * sin(deg_to_rad(30)) - end->z;
	// printf("  end:(%d, %d, %d) becomes   new_end:(%d, %d, %d)\n", (int)end->x, (int)end->y, (int)end->z, (int)new_end.x, (int)new_end.y, (int)end->z);
	end->x = new_end.x;
	end->y = new_end.y;
	// printf("ISOMETRIC         : (%d, %d)-->(%d, %d) becomes (%d, %d)-->(%d, %d)\n", (int)start->x, (int)start->y, (int)end->x, (int)end->y, (int)new_start.x, (int)new_start.y, (int)new_end.x, (int)new_end.y);
}

void	scale_to_fit(t_map	*map)
{
	float	scale_x;
	float	scale_y;

	scale_x = (WINDOW_WIDTH / 2) / map->width;
	scale_y = (WINDOW_HEIGHT / 2) / map->length;
	// if (map->max_z >= ft_abs(map->min_z))
	// 	scale_y = (WINDOW_HEIGHT / 2) / (map->length - map->max_z);
	// else
	// 	scale_y = (WINDOW_HEIGHT / 2) / (map->length - map->min_z);

	printf("scale_x = %f\n", scale_x);
	printf("scale_y = %f\n", scale_y);
	// if ((map->width * map->scale_factor) >= WINDOW_WIDTH)
	// {
	// 	map->scale_factor = scale_x;
	// 	printf("scale_x = %f\n", scale_x);
	// }
	// if ((map->length * map->scale_factor) >= WINDOW_HEIGHT)
	// {

	// 	printf("scale_y = %f\n", scale_y);
	// }		
	if (scale_x >= scale_y)
		map->scale_factor = (int)scale_x;
	else if (scale_y > scale_x)
		map->scale_factor = (int)scale_y;
	printf("scale factor (%d)\n", map->scale_factor);
}



/*
void	draw_mesh(t_vertex **map_array, t_map *map)
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