/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 18:08:10 by ccarrace          #+#    #+#             */
/*   Updated: 2023/06/28 21:15:40 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "get_next_line/get_next_line.h"

int check_input (int argc, char *file_name)
{
    int fd;
    
    if (argc == 2)
    {
        fd = open(file_name, O_RDONLY, 0);
        if (!get_next_line(fd))
        {
            write(1, "File is empty\n", 14);
            close(fd);
            return (1);
        }
        else
        {
            write(1, "Map is correct\n", 15);
        }
        return (0);
    }
    write(1, "Wrong number of arguments\n", 26);
    return (1);
}