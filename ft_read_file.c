/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 19:32:01 by ccarrace          #+#    #+#             */
/*   Updated: 2023/06/23 01:05:47 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int ft_get_map_length(char *file_name)
{
    char    *line;
    int     fd;
    int     map_length;

    fd = open(file_name, O_RDONLY, 0);
    map_length = 0;
    while(get_next_line(fd))
        map_length++;
    close(fd);
    return (map_length);
}

int get_width(char *file_name)
{
    char    *line;
    int     fd;
    int     map_width;
    
    fd = open(file_name, O_RDONLY, 0);
    
}

void    ft_read_file(char *file_name)
{
    
}