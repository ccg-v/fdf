/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 19:15:57 by ccarrace          #+#    #+#             */
/*   Updated: 2023/07/02 20:58:59 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>    // free, size_t
# include <fcntl.h>     // open
# include <stdio.h>     // printf!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
# include <unistd.h>    // write
/*
typedef struct s_vertex
{
    float       x;
    float       y;
    float       z;
}               t_vertex;
*/
typedef struct s_map
{
    int         width;
    int         length;
    // int         **height;
    // t_vertex    vertex;
    float       x;
    float       y;
    float       z;
    int         zoom_factor;
    int         color;
    void        *mlx_ptr;
    void        *win_ptr;
}               t_map;

char        **ft_split(char const *s, char c);
int	        ft_atoi(const char *str);
//int         check_input (int argc, char *file_name);
t_map       **read_file(char *file_name, t_map *map);
void	    draw_map(t_map **map_array, t_map *map);

void	    draw_line(t_map start, t_map end, t_map *map);

#endif