/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_load.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemzouri <kemzouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:30:51 by kemzouri          #+#    #+#             */
/*   Updated: 2025/04/01 13:48:26 by kemzouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	game_load(t_map *game)
{
	game->win_height = game->height * TILE_SIZE;
	game->win_width = game->width * TILE_SIZE;
	game->mlx = mlx_init();
	if (game->mlx == NULL)
	{
		ft_putstr_fd("Error\nFailed to initialize mlx.\n", 2);
		ft_free(game);
		exit(1);
	}
	game->mlx_window = mlx_new_window(game->mlx, game->win_width,
			game->win_height, "so_long");
	if (game->mlx_window == NULL)
	{
		ft_putstr_fd("Error\nFailed to create window.\n", 2);
		ft_free(game);
		exit(1);
	}
	init_images(game);
	display_images(game);
	mlx_key_hook(game->mlx_window, key_hook, game);
	mlx_hook(game->mlx_window, 17, 0, close_game, game);
	mlx_loop(game->mlx);
}
