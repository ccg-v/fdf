/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_menu.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 22:42:13 by ccarrace          #+#    #+#             */
/*   Updated: 2023/07/30 00:02:31 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"

void    display_menu(t_fdf *fdf)
{
    int x;
    int y;
    char *projection;

    x = 10;
    y = 10;
    projection = "";
    if (fdf->map->projection == 0)
        projection = "TOP VIEW";
    else if (fdf->map->projection == 1)
        projection = "ISOMETRIC VIEW";

    mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, x, y, 0xfbfe88, projection);
    if (fdf->map->projection == 0)
        mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, x, y += 50, 0xffffff, "I     : isometric view");
    else if (fdf->map->projection == 1)
        mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, x, y += 50, 0xffffff, "T     : top view");
    mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, x, y += 20, 0xffffff, "arrows: shift map");
    mlx_string_put(fdf->mlx_ptr, fdf->win_ptr, x, y += 20, 0xffffff, "+/-   : zoom in/out");
}