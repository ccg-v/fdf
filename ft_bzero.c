/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 20:50:19 by ccarrace          #+#    #+#             */
/*   Updated: 2023/07/14 22:32:51 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* LIBRARY <strings.h>
 *
 * DESCRIPTION
 * Writes 'n' zeroed bytes to the string 's'. If 'n' is zero, bzero does nothing
 * 
 * COMMENTS
 * Same as memset, but memset's 'int c' parameter is always zero in bzero. Thus, 
 * a shorter way to write the function in just a line is calling ft_memset:
 * 						ft_memset(s, 0, n);
 */

#include "fdf.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = 0;
		i++;
	}
}
