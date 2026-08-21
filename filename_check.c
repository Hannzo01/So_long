/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filename_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemzouri <kemzouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 20:26:18 by kemzouri          #+#    #+#             */
/*   Updated: 2025/04/03 19:04:03 by kemzouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	is_valid_filename(char *str)
{
	int	len;

	len = ft_strln(str);
	if (len < 5)
	{
		ft_putstr_fd("Error\nInvalid extension\n", 2);
		return (0);
	}
	if (ft_strncmp(str + len - 4, ".ber", 4) != 0 || str[len - 5] == '/')
	{
		ft_putstr_fd("Error\nInvalid extension || name\n", 2);
		return (0);
	}
	return (1);
}
