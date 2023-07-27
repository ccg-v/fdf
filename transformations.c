/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 19:17:17 by ccarrace          #+#    #+#             */
/*   Updated: 2023/07/27 12:34:21 by ccarrace         ###   ########.fr       */
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

void    scale(t_map *map, int scale_factor)
{
    int x;
    int y;
    int scaled_x;
    int scaled_y;

	printf("\n--------------------- SCALE ---------------------\n");
    y = 0;
    while (y < map->length)
    {
        x = 0;
        while (x < map->width)
        {
            scaled_x = map->mesh[y][x].x * scale_factor;
            scaled_y = map->mesh[y][x].y * scale_factor;
            x++;
        }
        y++;
    }  
}