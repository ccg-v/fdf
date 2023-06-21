/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 21:38:42 by ccarrace          #+#    #+#             */
/*   Updated: 2023/06/22 00:00:22 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx_macos/mlx.h"
#include <stdlib.h>
#include <math.h>

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
}	t_data;

void	draw_line(void *mlx_ptr, void *win_ptr, double beginX, double beginY, double endX, double endY, int color)
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
/*
int	mouse_event(void *param)
{
	t_data	data;

	data = *(t_data *)param; 	//	(t_data *) typecast informs the compiler that
								//	param must be treated as a pointer to a t_data
								//	structure, but does not assign the value of the 
								//	pointer to 'data'. To access the value pointed 
								//	to by 'param' we must dereference the pointer 
								//	using the '*' operator
	mlx_pixel_put(data->mlx_ptr, data->win_ptr, 1000/2, 1000/4, 0x00FF00);
	return (1);
}
*/

void draw_pixel(void *mlx_ptr, void *win_ptr, int x, int y)
{
    mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0x00FF00);
}

int mouse_event(int x, int y, void *param)
{
    t_data *data = (t_data *)param;
    draw_pixel(data->mlx_ptr, data->win_ptr, x, y);
    return (0);
}

#include <stdio.h>
int	main(void)
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_data	*data;
printf("Hola\n");
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 1000, 1000, "FdF by ccarrace");
	data = (t_data *)malloc(sizeof(t_data));
	if (data == NULL)
		return (1);
	data->mlx_ptr = mlx_ptr;
	data->win_ptr = win_ptr;
//	mlx_pixel_put(mlx_ptr, win_ptr, 1000/2, 1000/2, 0x00FF00);	//	Displays a pixel centered in the window
//	draw_line(mlx_ptr, win_ptr, 0, 333, 999, 666, 0xFFFFFF);	//	Displays a line from side to side of the window
	mlx_mouse_hook(win_ptr, &mouse_event, &data);
	mlx_loop(mlx_ptr);
	return (0);
}
