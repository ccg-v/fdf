/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 19:15:57 by ccarrace          #+#    #+#             */
/*   Updated: 2023/06/25 20:51:43 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>    // free, size_t
# include <stdio.h>     // printf

typedef struct s_map
{
    int     width;
    int     length;
    int     **height;
    void    *mlx_ptr;
    void    *win_ptr;
}           t_map;

char    **ft_split(char const *s, char c);
int	    ft_atoi(const char *str);

#endif