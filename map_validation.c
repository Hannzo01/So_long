/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemzouri <kemzouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 21:26:28 by kemzouri          #+#    #+#             */
/*   Updated: 2025/03/28 17:35:00 by kemzouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_map_validity(t_map *game)
{
	if ((check_map_shape(game) == 0))
		return (0);
	if (is_map_surrounded(game) == 0)
		return (0);
	if (valid_characters(game) == 0)
		return (0);
	if (ff_validity(game) == 0)
	{
		free_2d_array(game->clone_map);
		return (0);
	}
	return (1);
}

int	check_map_shape(t_map *game)
{
	int	i;
	int	j;

	i = 0;
	game->width = ft_strln(game->map[i]);
	while (game->map[i] != NULL)
	{
		j = 0;
		while (game->map[i][j] != '\0')
			j++;
		if (j != game->width)
		{
			ft_putstr_fd("Error\nMap is not rectangular || empty lines!\n", 2);
			return (0);
		}
		i++;
	}
	i--;
	if (i == 1)
		return (ft_putstr_fd("Error\nMap is too small to be valid!\n", 2), 0);
	return (1);
}

int	is_map_surrounded(t_map *game)
{
	int	i;
	int	j;

	if (check_char(game->map[0], '1') == 0)
		return (ft_putstr_fd("Error\nMap with walls error!\n", 2), 0);
	else if (check_char(game->map[game->height - 1], '1') == 0)
		return (ft_putstr_fd("Error\nMap with walls error!\n", 2), 0);
	i = 0;
	while (game->map[i] != NULL)
	{
		j = 0;
		while (game->map[i][j] != '\0')
		{
			if (j == 0 || j == game->width - 1)
			{
				if (game->map[i][j] != '1')
					return (ft_putstr_fd("Error\nMap with walls error!\n", 2),
						0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	check_char(char *str, char c)
{
	int	i;
	int	len;

	len = ft_strln(str);
	i = 0;
	while (i < len)
	{
		if (str[i] != c)
			return (0);
		i++;
	}
	return (1);
}
