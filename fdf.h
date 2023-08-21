/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 19:15:57 by ccarrace          #+#    #+#             */
/*   Updated: 2023/08/22 00:22:53 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <limits.h>
# include <stdio.h>
# include "libft.h"

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
# define KEYNUM_PLUS    69   
# define KEY_MINUS      27
# define KEYNUM_MINUS   78
# define KEY_X          7
# define KEY_Z          8

# define ERR_USER_END       "Program closed by user!\n"
# define ERR_NO_ARGS        "Not enough arguments!\n"
# define ERR_NUM_ARGS       "Wrong number of arguments!\n"
# define ERR_FILE_NAME      "File does not exist or is not a map!\n"
# define ERR_FILE_ACCESS    "Can't access file or file does not exist!\n"
# define ERR_FILE_EMPTY     "File is empty!\n"

typedef struct s_vertex
{
	float		x;
	float		y;
	float		z;
}	t_vertex;

typedef struct s_map
{
	char		*map_file;
	t_vertex	**mesh;
	t_vertex	**mesh_copy;
	int			width;
	int			length;
	int			scale_factor;
	float		z_scale_factor;
	int			min_z;
	int			max_z;
	int			uppermost_point;
	int			lowest_point;
	int			projection;
}	t_map;

typedef struct s_img
{
	void		*image;
	char		*buffer;
	int			bits_per_pixel;
	int			line_bytes;
	int			endian;
	int			image_bytes;
}	t_img;

typedef struct s_fdf
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			win_x;
	int			win_y;
	t_img		*image;
	t_map		*map;
	int			exit_code;
}	t_fdf;

enum e_projection
{
	TOP,
	ISOMETRIC
};

void		check_input(int argc, char *file_name);
t_vertex	**mesh_memory_allocate(t_vertex **mesh, t_fdf *fdf);
void		read_file(char *file_name, t_fdf *fdf);
void		clear_image(t_img *image, int image_bytes);
void		put_pixel_to_image(t_img *image, int x, int y, int color);
void		draw_mesh(t_fdf *fdf);
void		draw_line(t_fdf *fdf, t_vertex start, t_vertex end);
void		display_menu(t_fdf *fdf);
void		render(t_fdf *fdf);
void		scale_to_fit(t_map *map);
void		transform_to_isometric(t_map *map);
void		center_in_screen(t_map *map);
void		center_to_origin(t_map *map);
void		return_to_origin(t_map *map);
void		do_mesh_copy(t_vertex **src_mesh, t_vertex ***dst_mesh, t_fdf *fdf);
void		z_scale(t_map *map);
void		on_error_exit(char *exit_code);
int			key_handle(int keycode, t_fdf *fdf);
int			close_all(t_fdf *fdf);
void		translate(t_map *map, int x_displacement, int y_displacement);
void		scale(t_map *map, int scale_factor);
float		ft_abs(float num);
float		deg_to_rad(float deg_angle);
int			ft_find_min_value(float x, float y);
int			ft_count_columns(const char *str, char c);
void		ft_free_array_of_strings(char **argv);
void    	print_coordenates(t_map *map);
void		print_altitudes(t_map *map);

#endif
