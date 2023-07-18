/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 19:15:57 by ccarrace          #+#    #+#             */
/*   Updated: 2023/07/18 23:14:17 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>    // free, size_t
# include <fcntl.h>     // open
# include <stdio.h>     // printf!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
# include <unistd.h>    // write
# include <limits.h>    // INT_MIN, INT_MAX

# define WINDOW_WIDTH   1280
# define WINDOW_HEIGHT  720

typedef struct s_img
{
    void	    *image;
    char        *buffer;
	int		    bits_per_pixel;
	int		    line_bytes;
	int		    endian;
    int         image_bytes;
    // t_line      *line;
}               t_img;

typedef struct s_fdf
{
    void        *mlx_ptr;
    void        *win_ptr;
    int         win_x;
    int         win_y;
    t_img       *image;
}               t_fdf;

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
    int         scale_factor;
    float       min_x;
    float       max_x;
    float       min_y;
    float       max_y;
    // int         color;
}               t_map;

/*
typedef struct s_line
{
    t_vertex    start;
    t_vertex    end;
}               t_line;
*/

char        **ft_split(char const *s, char c);
int	        ft_atoi(const char *str);
void	    ft_bzero(void *s, size_t n);
//int         check_input (int argc, char *file_name);
t_vertex    **read_file(char *file_name, t_map *map);
void	    clear_image(t_img *image);
void	    put_pixel_to_image(t_img *image, int x, int y, int color);
void	    draw_mesh(t_fdf *fdf, t_map *map);
void	    draw_line(t_fdf *fdf, t_map *map, t_vertex start, t_vertex end);
void	    to_isometric(t_vertex *start, t_vertex *end);
void	    scale_to_fit(t_map	*map);
void	    center_in_image(t_map *map, t_vertex *start, t_vertex *end);
void	    center_isometric(t_map *map, t_vertex *start, t_vertex *end);
void        on_error_exit(int exit_code);

#endif