/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemzouri <kemzouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 23:33:53 by kemzouri          #+#    #+#             */
/*   Updated: 2025/04/03 09:42:56 by kemzouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	clone_map(t_map *game)
{
	int	i;

	i = 0;
	game->clone_map = malloc(sizeof(char *) * (game->height + 1));
	if (!game->clone_map)
		return ;
	while (i < game->height)
	{
		game->clone_map[i] = ft_strdup(game->map[i]);
		if (!game->clone_map[i])
		{
			while (i-- > 0)
				free(game->clone_map[i]);
			free(game->clone_map);
			game->clone_map = NULL;
			return ;
		}
		i++;
	}
	game->clone_map[i] = NULL;
}

void	flood_fill(t_map *game, int x, int y)
{
	if (game->clone_map[y][x] == 'X' || game->clone_map[y][x] == '1')
		return ;
	if (game->clone_map[y][x] == 'C')
		game->ff_c++;
	if (game->clone_map[y][x] == 'E')
		game->ff_e++;
	game->clone_map[y][x] = 'X';
	flood_fill(game, x - 1, y);
	flood_fill(game, x + 1, y);
	flood_fill(game, x, y - 1);
	flood_fill(game, x, y + 1);
}

int	ff_validity(t_map *game)
{
	clone_map(game);
	if (!game->clone_map)
		return (ft_putstr_fd("Error\nMap cloning failed!\n", 2), 0);
	flood_fill(game, game->x_pos, game->y_pos);
	if (game->collectibles != game->ff_c)
		return (ft_putstr_fd("Error\nSome 'C' are not reached!\n", 2), 0);
	if (game->ff_e == 0)
		return (ft_putstr_fd("Error\nExit cannot be reached!\n", 2), 0);
	return (1);
}
