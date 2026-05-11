/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssousmat <ssousmat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:49:47 by ssousmat          #+#    #+#             */
/*   Updated: 2025/05/31 17:52:14 by ssousmat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	get_end(t_main *main)
{
	bool	end;

	pthread_mutex_lock(&main->end_l);
	end = main->end;
	pthread_mutex_unlock(&main->end_l);
	return (end);
}

long long	get_time_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec * 0.001));
}

bool	ft_usleep(long long duration_ms, t_main *main)
{
	long long	start;

	start = get_time_ms();
	while ((get_time_ms() - start) < duration_ms)
	{
		pthread_mutex_lock(&main->end_l);
		if (main->end)
		{
			pthread_mutex_unlock(&main->end_l);
			return (true);
		}
		pthread_mutex_unlock(&main->end_l);
		usleep(100);
	}
	return (false);
}

void	ft_print(t_philo *ph, const char *msg, size_t len)
{
	long long	time;

	pthread_mutex_lock(&ph->main->end_l);
	pthread_mutex_lock(&ph->main->print_l);
	if (ph->main->end)
	{
		pthread_mutex_unlock(&ph->main->print_l);
		pthread_mutex_unlock(&ph->main->end_l);
		return ;
	}
	time = get_time_ms() - ph->main->s_t;
	ft_putnbr_fd(time, 1);
	write(1, " ", 1);
	ft_putnbr_fd((long long)ph->id, 1);
	write(1, msg, len);
	pthread_mutex_unlock(&ph->main->print_l);
	pthread_mutex_unlock(&ph->main->end_l);
}
