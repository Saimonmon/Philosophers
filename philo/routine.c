/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssousmat <ssousmat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:48:09 by ssousmat          #+#    #+#             */
/*   Updated: 2025/05/31 17:49:41 by ssousmat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *ph)
{
	if (ph->id & 1)
	{
		pthread_mutex_lock(ph->r_f);
		ft_print(ph, " has taken a fork\n", 18);
		pthread_mutex_lock(ph->l_f);
		ft_print(ph, " has taken a fork\n", 18);
	}
	else
	{
		pthread_mutex_lock(ph->l_f);
		ft_print(ph, " has taken a fork\n", 18);
		pthread_mutex_lock(ph->r_f);
		ft_print(ph, " has taken a fork\n", 18);
	}
}

void	drop_forks(t_philo *ph)
{
	if (ph->id & 1)
	{
		pthread_mutex_unlock(ph->l_f);
		pthread_mutex_unlock(ph->r_f);
	}
	else
	{
		pthread_mutex_unlock(ph->l_f);
		pthread_mutex_unlock(ph->r_f);
	}
}

void	eat(t_philo *ph)
{
	take_forks(ph);
	pthread_mutex_lock(&ph->p_m_l);
	ph->p_m = get_time_ms();
	pthread_mutex_unlock(&ph->p_m_l);
	ft_print(ph, " is eating\n", 11);
	ft_usleep(ph->main->t2e, ph->main);
	pthread_mutex_lock(&ph->m_e_l);
	ph->m_e++;
	pthread_mutex_unlock(&ph->m_e_l);
	drop_forks(ph);
}

bool	ft_sleep(t_philo *ph)
{
	ft_print(ph, " is sleeping\n", 13);
	return (ft_usleep(ph->main->t2s, ph->main));
}

void	*philo_routine(void *arg)
{
	t_philo		*ph;

	ph = (t_philo *)arg;
	while (ph->main->s_t > get_time_ms())
		usleep(1);
	while (1)
	{
		ft_print(ph, " is thinking\n", 13);
		if (ph->id & 1 && ph->main->n_ph > 1 && \
			(get_time_ms() - ph->main->s_t < 20))
			ft_usleep(ph->main->t2e * 0.5, ph->main);
		eat(ph);
		if (ft_sleep(ph))
			break ;
	}
	return (NULL);
}
