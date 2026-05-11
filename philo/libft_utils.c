/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssousmat <ssousmat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:45:02 by ssousmat          #+#    #+#             */
/*   Updated: 2025/05/31 17:47:26 by ssousmat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_calloc(size_t size, size_t nitems)
{
	void	*str;
	size_t	i;
	size_t	n;

	if (size && SIZE_MAX / size <= nitems)
		return (NULL);
	str = malloc(size * nitems);
	if (!str)
		return (NULL);
	i = 0;
	n = nitems * size;
	while (i < n)
		((unsigned char *)str)[i++] = 0;
	return (str);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(long long n, int fd)
{
	if (n < 10)
		ft_putchar_fd(n + 48, fd);
	else
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
}

bool	ft_istherenum(const char *str)
{
	size_t	i;
	bool	digit;

	i = 0;
	digit = false;
	if (!str)
		return (false);
	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == 43 || str[i] == 45)
		i++;
	while (48 <= str[i] && str[i] <= 57)
	{
		digit = true;
		i++;
	}
	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
		i++;
	if (digit && (str[i] == '\0'))
		return (true);
	return (false);
}

int	ft_atoi(const char *str)
{
	size_t	i;
	int		s;
	int		n;

	i = 0;
	n = 0;
	if (!str)
		return (0);
	while ((9 <= str[i] && str[i] <= 13) || str[i] == 32)
		i++;
	s = 1;
	if (str[i] == 43 || str[i] == 45)
	{
		if (str[i] == 45)
			s *= -1;
		i++;
	}
	while (48 <= str[i] && str[i] <= 57)
	{
		n = (str[i] - '0') + n * 10;
		i++;
	}
	return (n * s);
}
