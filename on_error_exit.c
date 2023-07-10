/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   on_error_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 20:26:05 by ccarrace          #+#    #+#             */
/*   Updated: 2023/07/10 23:12:12 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void on_error_exit(int exit_code)
{
	if (exit_code == 0)
    	write(1, "Error allocating t_fdf\n", 21);
  	if (exit_code == 1)
    	write(1, "Error: no mlx_ptr!\n", 19);
  	if (exit_code == 2)
    	write(1, "Error: no win_ptr!\n", 19);
	if (exit_code == 3)
		write(1, "Error allocating t_map\n", 23);
	if (exit_code == 4)
		write(1, "Error allocating t_line\n", 24);
  	exit(exit_code);
}