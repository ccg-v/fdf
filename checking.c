/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccarrace <ccarrace@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 18:08:10 by ccarrace          #+#    #+#             */
/*   Updated: 2023/07/31 20:23:28 by ccarrace         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	filename_is_right(char *filename)
{
	size_t	len;
	char	*extension;

	len = ft_strlen(filename);
	extension = ft_substr(filename, len - 4, 4);
	if (ft_strncmp(extension, ".fdf", 4) != 0)
	{
		free(extension);
		return (0);
	}
	free(extension);
	return (1);
}

static void	file_not_allowed(int fd)
{
	if (fd == -1)
	{
		close (fd);
		on_error_exit(ERR_FILE_ACCESS);
	}
}

static void	file_is_empty(char *file_name)
{
	char	*line;
	int		fd;

	fd = open(file_name, O_RDONLY, 0);
	file_not_allowed(fd);
	line = get_next_line(fd);
	if (line == NULL)
	{
		free(line);
		close(fd);
		on_error_exit(ERR_FILE_EMPTY);
	}
	else
	{
		while (line != NULL)
		{
			free(line);
			line = get_next_line(fd);
		}
		free(line);
	}
	close(fd);
}

void	check_input(int argc, char *file_name)
{
	if (argc != 2)
		on_error_exit(ERR_NUM_ARGS);
	else
	{
		if (filename_is_right(file_name) == 0)
			on_error_exit(ERR_FILE_NAME);
		file_is_empty(file_name);
	}
}

// int	check_input(int argc, char *file_name)
// {
// 	int		fd;
// 	char	*line;
// 	if (argc == 2)
// 	{
// 		if (filename_is_right(file_name) == 0)
// 			on_error_exit(ERR_FILE_NAME);
// 		fd = open(file_name, O_RDONLY, 0);
// 		if (fd == -1)
// 		{
// 			close (fd);
// 			on_error_exit(ERR_FILE_ACCESS);
// 		}
// 		line = get_next_line(fd);
// 		if (line == NULL)
// 		{
// 			free(line);
// 			close(fd);
// 			on_error_exit(ERR_FILE_EMPTY);
// 		}
// 		else
// 		{
// 			while (line != NULL)
// 			{
// 				free(line);
// 				line = get_next_line(fd);
// 			}
// 			free(line);
// 		}
// 		close(fd);
// 		return (0);
// 	}
// 	on_error_exit(ERR_NUM_ARGS);
// 	return (1);
// }
