/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemzouri <kemzouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 20:25:50 by kemzouri          #+#    #+#             */
/*   Updated: 2025/04/03 20:19:09 by kemzouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	calculate_map_height(char *filename)
{
	int		fd;
	int		height;
	char	*line;

	height = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (ft_putstr_fd("Error\nInvalid fd\n", 2), 0);
	line = get_next_line(fd);
	if (line == NULL)
		return (close(fd), ft_putstr_fd("Error\nEmpty file\n", 2), 0);
	if (line[0] == '\n' && line[1] == '\0')
	{
		close(fd);
		get_next_line(-1);
		return (free(line),
			ft_putstr_fd("Error\nMap cannot start with a newline\n", 2), 0);
	}
	while (line != NULL)
	{
		height++;
		free(line);
		line = get_next_line(fd);
	}
	return (close(fd), height);
}

int	store_map_in_array(char *filename, t_map *game)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	if (line == NULL)
		return (0);
	game->map = malloc((game->height + 1) * sizeof(char *));
	if (game->map == NULL)
		return (0);
	while (line != NULL)
	{
		if (line[ft_strln(line) - 1] == '\n')
			line[ft_strln(line) - 1] = '\0';
		game->map[i] = ft_strdup(line);
		if (game->map[i] == NULL)
			return (free_2d(game->map, i), close(fd), free(line), 0);
		i++;
		free(line);
		line = get_next_line(fd);
	}
	game->map[i] = NULL;
	return (close(fd), 1);
}
