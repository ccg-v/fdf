/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 21:08:38 by ccarrace          #+#    #+#             */
/*   Updated: 2023/07/31 20:24:20 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	key_projection(t_fdf *fdf, int keycode)
{
	static int	flag = 0;

	if (keycode == KEY_T && flag == 1)
	{
		fdf->map->projection = TOP;
		do_mesh_copy(fdf->map->mesh_copy, &fdf->map->mesh, fdf);
		center_in_screen(fdf->map);
		draw_mesh(fdf);
		flag = 0;
	}
	else if (keycode == KEY_I && flag == 0)
	{
		fdf->map->projection = ISOMETRIC;
		return_to_origin(fdf->map);
		transform_to_isometric(fdf->map);
		center_in_screen(fdf->map);
		draw_mesh(fdf);
		flag = 1;
	}
}

static void	key_scale_z(t_fdf *fdf, int keycode)
{
	if ((keycode == KEY_MINUS || keycode == KEYNUM_MINUS) \
			&& fdf->map->projection == 1)
	{
		if (fdf->map->z_scale_factor > 0.025)
			fdf->map->z_scale_factor -= 0.025;
	}
	else if ((keycode == KEY_PLUS || keycode == KEYNUM_PLUS) \
			&& fdf->map->projection == 1)
	{
		if (fdf->map->z_scale_factor < 0.975)
			fdf->map->z_scale_factor += 0.025;
	}
	do_mesh_copy(fdf->map->mesh_copy, &fdf->map->mesh, fdf);
	z_scale(fdf->map);
	return_to_origin(fdf->map);
	center_in_screen(fdf->map);
	transform_to_isometric(fdf->map);
	center_in_screen(fdf->map);
	draw_mesh(fdf);
}

static void	key_translate(t_fdf *fdf, int keycode)
{
	if (keycode == KEY_LEFT)
	{
		translate(fdf->map, -10, 0);
		draw_mesh(fdf);
	}
	else if (keycode == KEY_RIGHT)
	{
		translate(fdf->map, 10, 0);
		draw_mesh(fdf);
	}
	else if (keycode == KEY_DOWN)
	{
		translate(fdf->map, 0, 10);
		draw_mesh(fdf);
	}
	else if (keycode == KEY_UP)
	{
		translate(fdf->map, 0, -10);
		draw_mesh(fdf);
	}
}

int	key_handle(int keycode, t_fdf *fdf)
{
	if (keycode == KEY_ESC)
		close_all(fdf);
	else if (keycode == KEY_T || keycode == KEY_I)
		key_projection(fdf, keycode);
	else if (keycode == KEY_MINUS || keycode == KEYNUM_MINUS \
		|| keycode == KEY_PLUS || keycode == KEYNUM_PLUS)
		key_scale_z(fdf, keycode);
	else if (keycode == KEY_LEFT || keycode == KEY_RIGHT || keycode == KEY_DOWN \
		|| keycode == KEY_UP)
		key_translate(fdf, keycode);
	return (0);
}

void	do_mesh_copy(t_vertex **src_mesh, t_vertex ***dst_mesh, t_fdf *fdf)
{
	int	x;
	int	y;

	if (*dst_mesh == NULL)
		*dst_mesh = mesh_memory_allocate(src_mesh, fdf);
	y = 0;
	while (y < fdf->map->length)
	{
		x = 0;
		while (x < fdf->map->width)
		{
			(*dst_mesh)[y][x].x = src_mesh[y][x].x;
			(*dst_mesh)[y][x].y = src_mesh[y][x].y;
			(*dst_mesh)[y][x].z = src_mesh[y][x].z;
			x++;
		}
		y++;
	}
}
