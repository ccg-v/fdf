/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 19:17:17 by ccarrace          #+#    #+#             */
/*   Updated: 2023/07/27 00:12:29 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void    translate(t_map *map, int x_displacement, int y_displacement)
{
    int x;
    int y;
    int translated_x;
    int translated_y;

	printf("\n----------------- DISPLACEMENT ------------------\n");
    y = 0;
    while (y < map->length)
    {
        x = 0;
        while (x < map->width)
        {
            translated_x = map->mesh[y][x].x + x_displacement;
            translated_y = map->mesh[y][x].y + y_displacement;
            map->mesh[y][x].x = translated_x;
            map->mesh[y][x].y = translated_y;
            x++;
        }
        y++;
    }
    print_coordenates(map);
}