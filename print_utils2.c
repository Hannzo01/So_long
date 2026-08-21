/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kemzouri <kemzouri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 01:52:28 by kemzouri          #+#    #+#             */
/*   Updated: 2025/03/31 15:31:27 by kemzouri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int n)
{
	if (n == -2147483648)
		write(1, "-2147483648", 11);
	if (n < 0)
	{
		ft_putchar('-');
		n = -n;
	}
	if (n >= 10)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	else
		ft_putchar(n + 48);
}

int	ft_strln(char *str)
{
	int	i;

	if (!str)
		return (-1);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	free_2d(char **map, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		free(map[j]);
		j++;
	}
	free(map);
}

void	*ft_memset(void *s, int c, int n)
{
	int				i;
	unsigned char	*p;

	p = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		p[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
