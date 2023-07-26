/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 21:08:38 by ccarrace          #+#    #+#             */
/*   Updated: 2023/07/27 00:58:45 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// int key_handle(t_fdf *fdf, t_map *map, int keycode)
int key_handle(int keycode, t_container *container)
{
    if (keycode == KEY_ESC)
        close_all(&container->fdf);
    else if (keycode == KEY_LEFT)
        translate(&container->map, -10, 0);
    else if (keycode == KEY_RIGHT)
        translate(&container->map, 10, 0);
    else if (keycode == KEY_DOWN)
        translate(&container->map, 0 , 10);
    else if (keycode == KEY_UP)
        translate(&container->map, 0 , -10);
    // else if (keycode == KEY_DEL)
    //     clear_image(fdf->image);
    draw_mesh(&container->fdf, &container->map);
    return (0);
}