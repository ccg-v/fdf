/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 19:15:57 by ccarrace          #+#    #+#             */
/*   Updated: 2023/07/11 11:59:16 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>    // free, size_t
# include <fcntl.h>     // open
# include <stdio.h>     // printf!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
# include <unistd.h>    // write

typedef struct s_vertex
{
    float       x;
    float       y;
    float       z;
}               t_vertex;

typedef struct s_map
{
    t_vertex    **mesh;
    int         width;
    int         length;
    int         zoom_factor;
    int         color;
}               t_map;
/*
typedef struct s_line
{
    t_vertex    start;
    t_vertex    end;
}               t_line;
*/
typedef struct s_image
{
    void	    *image;
    char        *address;
	int		    bits_per_pixel;
	int		    line_length;
	int		    endian;
}               t_image;

typedef struct s_fdf
{
    void        *mlx_ptr;
    void        *win_ptr;
    int         win_x;
    int         win_y;
    t_image     *image;
}               t_fdf;


char        **ft_split(char const *s, char c);
int	        ft_atoi(const char *str);
//int         check_input (int argc, char *file_name);
t_vertex       **read_file(char *file_name, t_map *map);
void	    draw_map(t_fdf *fdf, t_map *map);
void	    draw_line(t_fdf *fdf, t_map *map, t_vertex start, t_vertex end);
void        on_error_exit(int exit_code);

#endif