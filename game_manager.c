/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemzouri <kemzouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 15:57:46 by kemzouri          #+#    #+#             */
/*   Updated: 2025/04/01 13:58:34 by kemzouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_images(t_map *game)
{
	game->p_image = mlx_xpm_file_to_image(game->mlx, "./textures/player.xpm",
			&game->image_width, &game->image_height);
	game->d_image = mlx_xpm_file_to_image(game->mlx, "./textures/door.xpm",
			&game->image_width, &game->image_height);
	game->f_image = mlx_xpm_file_to_image(game->mlx, "./textures/floor.xpm",
			&game->image_width, &game->image_height);
	game->c_image = mlx_xpm_file_to_image(game->mlx,
			"./textures/collectibles.xpm", &game->image_width,
			&game->image_height);
	game->w_image = mlx_xpm_file_to_image(game->mlx, "./textures/wall.xpm",
			&game->image_width, &game->image_height);
	if (game->p_image == NULL || game->d_image == NULL || game->f_image == NULL
		|| game->c_image == NULL || game->w_image == NULL)
	{
		ft_putstr_fd("Error\nFailed to load images.\n", 2);
		ft_free_images(game);
		ft_free(game);
		exit(1);
	}
}

void	ft_free_images(t_map *game)
{
	if (game->d_image != NULL)
		mlx_destroy_image(game->mlx, game->d_image);
	if (game->p_image != NULL)
		mlx_destroy_image(game->mlx, game->p_image);
	if (game->f_image != NULL)
		mlx_destroy_image(game->mlx, game->f_image);
	if (game->c_image != NULL)
		mlx_destroy_image(game->mlx, game->c_image);
	if (game->w_image != NULL)
		mlx_destroy_image(game->mlx, game->w_image);
}

void	display_images(t_map *game)
{
	game->i = 0;
	while (game->map[game->i] != NULL)
	{
		game->j = 0;
		while (game->map[game->i][game->j] != '\0')
		{
			if (game->map[game->i][game->j] == 'C')
				mlx_put_image_to_window(game->mlx, game->mlx_window,
					game->c_image, game->j * 64, game->i * 64);
			else if (game->map[game->i][game->j] == 'E')
				mlx_put_image_to_window(game->mlx, game->mlx_window,
					game->d_image, game->j * 64, game->i * 64);
			else if (game->map[game->i][game->j] == 'P')
				mlx_put_image_to_window(game->mlx, game->mlx_window,
					game->p_image, game->j * 64, game->i * 64);
			else if (game->map[game->i][game->j] == '1')
				mlx_put_image_to_window(game->mlx, game->mlx_window,
					game->w_image, game->j * 64, game->i * 64);
			else if (game->map[game->i][game->j] == '0')
				mlx_put_image_to_window(game->mlx, game->mlx_window,
					game->f_image, game->j * 64, game->i * 64);
			game->j++;
		}
		game->i++;
	}
}

void	handle_door(t_map *game)
{
	if (game->collected == game->collectibles)
	{
		game->move_count++;
		write(1, "Moves:", 6);
		ft_putnbr(game->move_count);
		write(1, "\n", 1);
		write(1, "You Won!\n", 9);
		ft_free_images(game);
		ft_free(game);
		exit(0);
	}
	else
	{
		game->door_flag = 1;
		game->map[game->y_pos][game->x_pos] = '0';
		game->map[game->future_y][game->future_x] = 'P';
		game->x_pos = game->future_x;
		game->y_pos = game->future_y;
		display_images(game);
	}
}

int	move_player(t_map *game)
{
	game->future_x = game->x_pos + game->press_x;
	game->future_y = game->y_pos + game->press_y;
	if (game->map[game->future_y][game->future_x] == '1')
		return (0);
	if (game->map[game->future_y][game->future_x] == 'E')
	{
		handle_door(game);
		return (1);
	}
	if (game->map[game->future_y][game->future_x] == 'C')
		game->collected++;
	if (game->door_flag == 1)
	{
		game->map[game->y_pos][game->x_pos] = 'E';
		game->door_flag = 0;
	}
	else
		game->map[game->y_pos][game->x_pos] = '0';
	game->map[game->future_y][game->future_x] = 'P';
	game->x_pos = game->future_x;
	game->y_pos = game->future_y;
	display_images(game);
	return (1);
}
