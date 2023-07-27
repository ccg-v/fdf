/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 21:08:38 by ccarrace          #+#    #+#             */
/*   Updated: 2023/07/27 14:29:19 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int key_handle(int keycode, t_fdf *fdf)
{
    if (keycode == KEY_ESC)
        close_all(fdf);
    else if (keycode == KEY_LEFT)
        translate(fdf->map, -10, 0);
    else if (keycode == KEY_RIGHT)
        translate(fdf->map, 10, 0);
    else if (keycode == KEY_DOWN)
        translate(fdf->map, 0 , 10);
    else if (keycode == KEY_UP)
        translate(fdf->map, 0 , -10);

    else if (keycode == KEY_T)
    {        
        printf("changed to Top view\n");
        fdf->map->projection = TOP;
        printf("fdf->map->projection = %d\n", fdf->map->projection);
    }
    else if (keycode == KEY_I)
    {
        printf("changed to Isometric projection\n");
        fdf->map->projection = ISOMETRIC;
        printf("fdf->map->projection = %d\n", fdf->map->projection);
    }
        
    draw_mesh(fdf);
    return (0);
}