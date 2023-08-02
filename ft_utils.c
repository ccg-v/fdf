/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:42:25 by ccarrace          #+#    #+#             */
/*   Updated: 2023/07/31 20:09:47 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stddef.h>
#include <stdlib.h>

float	ft_abs(float num)
{
	if (num < 0)
		return (num * -1);
	return (num);
}

float	deg_to_rad(float deg_angle)
{
	float	rad_angle;

	rad_angle = (deg_angle * M_PI) / 180;
	return (rad_angle);
}

float	ft_find_min_value(float x, float y)
{
	if (x < y)
		return (x);
	else
		return (y);
}

int	ft_count_columns(const char *str, char c)
{
	int	i;
	int	num_columns;

	i = 0;
	num_columns = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i] != c && str[i] != '\n')
			num_columns++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (num_columns);
}

void	ft_free_array_of_strings(char **argv)
{
	int	i;

	i = 0;
	if (argv == NULL || *argv == NULL)
		return ;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}
