/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssousmat <ssousmat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:38:06 by ssousmat          #+#    #+#             */
/*   Updated: 2025/05/31 17:39:30 by ssousmat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_end(void *arg)
{
	t_main	*main;

	main = (t_main *)arg;
	while (main->s_t > get_time_ms())
		usleep(1);
	if (main->mx_m_f)
	{
		while (1)
			if (death(main) || mx_m_reached(main))
				break ;
	}
	else
		while (1)
			if (death(main))
				break ;
	return (NULL);
}

void	print_death(t_main *main, int i)
{
	pthread_mutex_lock(&main->end_l);
	pthread_mutex_lock(&main->print_l);
	ft_putnbr_fd(get_time_ms() - main->s_t, 1);
	write(1, " ", 1);
	ft_putnbr_fd((long long)main->ph[i].id, 1);
	write(1, " died\n", 6);
	main->end = true;
	pthread_mutex_unlock(&main->print_l);
	pthread_mutex_unlock(&main->end_l);
}

bool	death(t_main *main)
{
	int		i;
	int		t_s_p_m;

	i = 0;
	while (i < main->n_ph)
	{
		pthread_mutex_lock(&main->end_l);
		if (main->end)
		{
			pthread_mutex_unlock(&main->end_l);
			return (true);
		}
		pthread_mutex_unlock(&main->end_l);
		pthread_mutex_lock(&main->ph[i].p_m_l);
		t_s_p_m = (int)(get_time_ms() - main->ph[i].p_m);
		pthread_mutex_unlock(&main->ph[i].p_m_l);
		if (t_s_p_m > (main->t2d))
		{
			print_death(main, i);
			return (true);
		}
		i++;
	}
	return (false);
}

bool	mx_m_reached(t_main	*main)
{
	int	i;
	int	reached;

	i = 0;
	reached = 0;
	while (i < main->n_ph)
	{
		pthread_mutex_lock(&main->ph[i].m_e_l);
		if (main->ph[i].m_e >= main->mx_m)
			reached++;
		pthread_mutex_unlock(&main->ph[i].m_e_l);
		i++;
	}
	if (reached == main->n_ph)
	{
		pthread_mutex_lock(&main->end_l);
		main->end = true;
		pthread_mutex_unlock(&main->end_l);
		return (true);
	}
	return (false);
}
