/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 21:08:38 by ccarrace          #+#    #+#             */
/*   Updated: 2023/07/31 00:24:07 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int key_handle(int keycode, t_fdf *fdf)
{
    int scale_factor;
    scale_factor = ft_find_min_value(fdf->map->width, fdf->map->length);
    printf("\nKEY_HANDLE(): ZOOM_FACTOR = %d\n", scale_factor);
    // move
    if (keycode == KEY_ESC)
        close_all(fdf);
    else if (keycode == KEY_LEFT)
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
        translate(fdf->map, 0 , 10);
        draw_mesh(fdf);
    }
    else if (keycode == KEY_UP)
    {
        translate(fdf->map, 0 , -10);
        draw_mesh(fdf);
    }

    // scale
    else if (keycode == KEY_PLUS)
    {
        scale(fdf->map, scale_factor);
        // scale(fdf->map, fdf->map->scale_factor++);
        draw_mesh(fdf);
    }
    else if (keycode == KEY_MINUS)
    {
        scale(fdf->map, -(scale_factor));
        // scale(fdf->map, fdf->map->scale_factor--);
        draw_mesh(fdf);       
    }

    // change projection
    else if (keycode == KEY_T)
    {
        printf("changing to TOP view\n");
        fdf->map->projection = TOP;
        printf("fdf->map->projection = %d\n", fdf->map->projection);
        render(fdf);
    }
    else if (keycode == KEY_I)
    {
        printf("changing to ISOMETRIC view\n");
        fdf->map->projection = ISOMETRIC;
        printf("fdf->map->projection = %d\n", fdf->map->projection);
        render(fdf);
    }
    return (0);
}