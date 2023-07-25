/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 19:15:57 by ccarrace          #+#    #+#             */
/*   Updated: 2023/07/25 16:57:15 by ccarrace         ###   ########.fr       */
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
    int         min_z;
    int         max_z;
    int         uppermost_point;
    int         lowest_point;
    // int         color;
}               t_map;

char        **ft_split(char const *s, char c);
int	        ft_atoi(const char *str);
void	    ft_bzero(void *s, size_t n);
float       ft_find_min_value(float x, float y);
// int         check_input (int argc, char *file_name);
t_vertex    **read_file(char *file_name, t_map *map);
void	    clear_image(t_img *image);
// void	    put_pixel_to_image(t_img *image, int x, int y, int color);
void	    put_pixel_to_image(t_img *image, int x, int y, int color);
void	    draw_mesh(t_fdf *fdf, t_map *map);
// void	    draw_line(t_fdf *fdf, t_map *map, t_vertex start, t_vertex end);
void	    draw_line(t_fdf *fdf, t_vertex start, t_vertex end);
void	    to_isometric(t_vertex *start, t_vertex *end);
void        transform_to_isometric(t_map *map);
void	    scale_to_fit(t_map *map);
void	    center_in_image(t_map *map, t_vertex *start, t_vertex *end);
void	    center_in_screen(t_map *map);
void        center_to_origin(t_map *map);
void        on_error_exit(int exit_code);

void        print_altitudes(t_map *map);
void        print_coordenates(t_map *map);
#endif