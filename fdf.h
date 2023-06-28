/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 19:15:57 by ccarrace          #+#    #+#             */
/*   Updated: 2023/06/28 23:50:46 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>    // free, size_t
# include <fcntl.h>     // open
# include <stdio.h>     // printf!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
# include <unistd.h>    // write

typedef struct s_map
{
    int     width;
    int     length;
    int     **height;
    int     zoom_factor;
    int     color;
    void    *mlx_ptr;
    void    *win_ptr;
}           t_map;

char        **ft_split(char const *s, char c);
int	        ft_atoi(const char *str);
//int         check_input (int argc, char *file_name);
void        read_file(char *file_name, t_map *map);
void	    draw_map(t_map *map);

void	    draw_line(float x0, float y0, float x1, float y1, t_map *map);

#endif