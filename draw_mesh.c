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
/*
void	put_pixel_to_image(t_img *image, int x, int y, int color)
{
    char    *pixel;

    pixel = image->buffer + (y * image->line_bytes + x * (image->bits_per_pixel / 8));
    *(int *)pixel = color;
}
*/

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

// void	draw_line(t_fdf *fdf, t_map *map, t_vertex start, t_vertex end)
void	draw_line(t_fdf *fdf, t_vertex start, t_vertex end)
{
	float	delta_x;
	float	delta_y;
	int		biggest_delta;

	// start.x *= map->scale_factor;
	// start.y *= map->scale_factor;
	// start.z *= map->scale_factor;
	// end.x *= map->scale_factor;
	// end.y *= map->scale_factor;
	// end.z *= map->scale_factor;

	to_isometric(&start, &end);
	center_isometric(&start, &end);

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
		// if (start.x > 0 && start.y > 0 && start.x < WINDOW_WIDTH && start.y < WINDOW_HEIGHT)
		{
			put_pixel_to_image(fdf->image, start.x, start.y, 0xffffff);
			start.x += delta_x;
			start.y += delta_y;
			biggest_delta--;
		}
	}
}

void draw_mesh(t_fdf *fdf, t_map *map)
{
    int row;
    int column;

    row = 0;
    while (row < map->length)
    {
        column = 0;
        while (column < map->width)
        {
            if (column < (map->width - 1))
                // draw_line(fdf, map, map->mesh[row][column], map->mesh[row][column + 1]);
				draw_line(fdf, map->mesh[row][column], map->mesh[row][column + 1]);
            if (row < (map->length - 1))
                // draw_line(fdf, map, map->mesh[row][column], map->mesh[row + 1][column]);
				draw_line(fdf, map->mesh[row][column], map->mesh[row + 1][column]);
            column++;
        }
        row++;
    }
    mlx_put_image_to_window(fdf->mlx_ptr, fdf->win_ptr, fdf->image->image, 0, 0);
}

void	scale_to_fit(t_map	*map)
{
	float	scale_x;
	float	scale_y;
	float	scale_z;

	scale_x = (WINDOW_WIDTH / 2) / map->width;
	scale_y = (WINDOW_HEIGHT / 2) / map->length;
	scale_z = (WINDOW_HEIGHT / 2) / (map->max_z + ft_abs(map->min_z)); //Que pasa si min_z es mayor que 0, hay que restar?
printf("max_z = %d\n", map->max_z);
printf("min_z = %d\n", map->min_z);
printf("scale_x = %f\n", scale_x);
printf("scale_y = %f\n", scale_y);
printf("scale_z = %f\n", scale_z);
	map->scale_factor = ft_find_min_value(scale_x, ft_find_min_value(scale_y, scale_z));
printf("scale factor (%d)\n", map->scale_factor);

	int	x;
	int	y;
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

	// float	adjusted_height = (map->max_z + ft_abs(map->min_z)) * map->scale_factor;
	// float	total_height = adjusted_height * map->length;
	// float	vertical_offset = ((WINDOW_HEIGHT / 2) - total_height) / 2;
	// y = 0;
	// while (y < map->length)
	// {
	// 	x = 0;
	// 	while (x < map->width)
	// 	{
	// 		map->mesh[y][x].x *= (WINDOW_HEIGHT / 2) / 2;
	// 		map->mesh[y][x].y *= vertical_offset;
	// 		x++;
	// 	}
	// 	y++;
	// }
}

void	center_isometric(t_vertex *start, t_vertex *end)
{
	t_vertex	new_start;
	t_vertex	new_end;

	new_start.x = start->x + (WINDOW_WIDTH / 2);
	new_start.y = start->y + (WINDOW_HEIGHT / 2);
	new_end.x = end->x + (WINDOW_WIDTH / 2);
	new_end.y = end->y + (WINDOW_HEIGHT / 2);
printf("CENTER IN SCREEN  : (%d, %d)-->(%d, %d) becomes /%d, %d)-->(%d, %d)\n", (int)start->x, (int)start->y, (int)end->x, (int)end->y, (int)new_start.x, (int)new_start.y, (int)new_end.x, (int)new_end.y);
	start->x = new_start.x;
	start->y = new_start.y;
	end->x = new_end.x;
	end->y = new_end.y;
}

void	to_isometric(t_vertex *start, t_vertex *end)
{
	t_vertex	new_start;
	t_vertex	new_end;
float	start_x;
float	start_y;
float	end_x;
float	end_y;
float	new_start_x;
float	new_start_y;
float	new_end_x;
float	new_end_y;

start_x = start->x;
start_y = start->y;

	new_start.x = (start->x - start->y) * cos(deg_to_rad(30));
	new_start.y = (start->x + start->y) * sin(deg_to_rad(30)) - start->z;
	printf("------------------- ISOMETRIC -------------------\n");
	printf("start:(%f, %f) becomes new_start:(%f, %f)\n", start->x, start->y, new_start.x, new_start.y);
	// printf("start:(%f, %f) becomes new_start:(%f, %f)\n", start->x / map->scale_factor, start->y / map->scale_factor, new_start.x / map->scale_factor, new_start.y / map->scale_factor);
	start->x = new_start.x;
	start->y = new_start.y;

new_start_x = start->x;
new_start_y = start->y;
end_x = end->x;
end_y = end->y;

	new_end.x = (end->x - end->y) * cos(deg_to_rad(30));
	new_end.y = (end->x + end->y) * sin(deg_to_rad(30)) - end->z;
	printf("  end:(%f, %f) becomes   new_end:(%f, %f)\n", end->x, end->y, new_end.x, new_end.y);
	// printf("  end:(%f, %f) becomes   new_end:(%f, %f\n", end->x / map->scale_factor, end->y / map->scale_factor, new_end.x / map->scale_factor, new_end.y / map->scale_factor);
	end->x = new_end.x;
	end->y = new_end.y;

new_end_x = end->x;
new_end_y = end->y;
	// printf("ISOMETRIC         : (%d, %d)-->(%d, %d) becomes (%d, %d)-->(%d, %d)\n", (int)start->x, (int)start->y, (int)end->x, (int)end->y, (int)new_start.x, (int)new_start.y, (int)new_end.x, (int)new_end.y);
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
}
