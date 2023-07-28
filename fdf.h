/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 19:15:57 by ccarrace          #+#    #+#             */
/*   Updated: 2023/07/29 01:42:48 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>    // free, size_t
# include <fcntl.h>     // open
# include <unistd.h>    // write
# include <limits.h>    // INT_MIN, INT_MAX

# include <stdio.h>     //  printf!!!!!!!!!!!!!!!!!!!!!!!! DELETE !!!

# define WINDOW_WIDTH   1280
# define WINDOW_HEIGHT  720

# define KEY_ESC        53
# define KEY_LEFT       123
# define KEY_RIGHT      124
# define KEY_DOWN       125
# define KEY_UP         126
# define KEY_T          17
# define KEY_I          34
# define KEY_PLUS       24
# define KEY_MINUS      27

typedef struct s_vertex
{
    float       x;
    float       y;
    float       z;
}   t_vertex;

typedef struct s_map
{
    char        *map_file;
    t_vertex    **mesh;
    int         width;
    int         length;
    int         scale_factor;
    int         min_z;
    int         max_z;
    int         uppermost_point;
    int         lowest_point;
    int         projection;
}   t_map;

typedef struct s_img
{
    void	    *image;
    char        *buffer;
	int		    bits_per_pixel;
	int		    line_bytes;
	int		    endian;
    int         image_bytes;
}   t_img;

typedef struct s_fdf
{
    void        *mlx_ptr;
    void        *win_ptr;
    int         win_x;
    int         win_y;
    t_img       *image;
    t_map       *map;
    int         exit_code;
}   t_fdf;

// typedef struct s_container
// {
//     t_fdf       *fdf;
//     t_map       *map;
// }   t_container;       

enum e_projection
{
    TOP,
    ISOMETRIC
};

char        **ft_split(char const *s, char c);
int	        ft_atoi(const char *str);
void	    ft_bzero(void *s, size_t n);
float       ft_find_min_value(float x, float y);
size_t      ft_strlen(const char *str);
char	    *ft_substr(char const *s, unsigned int start, size_t len);
char	    *ft_strdup(const char *s1);
char	    *ft_strjoin(char const *s1, char const *s2);
char	    *ft_strchr(const char *s, int c);
char        *get_next_line(int fd);

int         check_input (int argc, char *file_name);
t_vertex    **read_file(char *file_name, t_map *map);
void	    clear_image(t_img *image, int image_bytes);
// void	    put_pixel_to_image(t_img *image, int x, int y, int color);
void	    put_pixel_to_image(t_img *image, int x, int y, int color);
void	    draw_mesh(t_fdf *fdf);
// void	    draw_line(t_fdf *fdf, t_map *map, t_vertex start, t_vertex end);
void	    draw_line(t_fdf *fdf, t_vertex start, t_vertex end);
void	render(t_fdf *fdf);

void	    scale_to_fit(t_map *map);
void        transform_to_isometric(t_map *map);
// void	    center_in_image(t_map *map, t_vertex *start, t_vertex *end);
void	    center_in_screen(t_map *map);
void        center_to_origin(t_map *map);
void	    return_to_origin(t_map *map);

void        on_error_exit(int exit_code);
// int      key_handle(t_fdf *fdf, t_map *map, int keycode);
int         key_handle(int keycode, t_fdf *fdf);
int	        close_all(t_fdf *fdf);

void        translate(t_map *map, int x_displacement, int y_displacement);
void        scale(t_map *map, int scale_factor);
void        print_altitudes(t_map *map);
void        print_coordenates(t_map *map);
#endif