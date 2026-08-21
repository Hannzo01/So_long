/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _map_content.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemzouri <kemzouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 23:18:08 by kemzouri          #+#    #+#             */
/*   Updated: 2025/03/25 23:52:06 by kemzouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_valid(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] != 'P' && map[i][j] != 'E' && map[i][j] != 'C'
				&& map[i][j] != '1' && map[i][j] != '0')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void	count_element(t_map *game)
{
	int	y;
	int	x;

	y = 0;
	while (game->map[y] != NULL)
	{
		x = 0;
		while (game->map[y][x] != '\0')
		{
			if (game->map[y][x] == 'C')
				game->collectibles++;
			else if (game->map[y][x] == 'P')
			{
				game->y_pos = y;
				game->x_pos = x;
				game->p++;
			}
			else if (game->map[y][x] == 'E')
				game->e++;
			x++;
		}
		y++;
	}
}

int	valid_characters(t_map *game)
{
	if (is_valid(game->map) == 1)
		return ((ft_putstr_fd("Error\nInvalid char\n", 2), 0));
	count_element(game);
	if (game->collectibles < 1)
		return (ft_putstr_fd("Error\nAt least one collectible is required.\n",
				2), 0);
	if (game->e != 1)
		return (ft_putstr_fd("Error\nThe map must contain exactly one exit.\n",
				2), 0);
	if (game->p != 1)
		return (ft_putstr_fd("Error\nThe map must contain one player.\n", 2),
			0);
	return (1);
}
