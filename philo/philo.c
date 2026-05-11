/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssousmat <ssousmat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 17:44:36 by ssousmat          #+#    #+#             */
/*   Updated: 2025/05/31 17:47:56 by ssousmat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	start_threads(t_main *main, pthread_t *monitor_thread)
{
	int	i;

	i = 0;
	if (pthread_create(monitor_thread, NULL, monitor_end, (void *)main))
		return (ft_clean(main), false);
	while (i < main->n_ph)
	{
		if (pthread_create(&main->ph[i].th_id, NULL, philo_routine, \
			&main->ph[i]))
		{
			pthread_mutex_lock(&main->end_l);
			main->end = true;
			pthread_mutex_unlock(&main->end_l);
			break ;
		}
		i++;
	}
	return (true);
}

void	ft_clean(t_main *main)
{
	int	i;

	i = 0;
	while (i < main->n_ph && main->mutex_init)
	{
		pthread_mutex_destroy(&main->f[i]);
		pthread_mutex_destroy(&main->ph[i].p_m_l);
		pthread_mutex_destroy(&main->ph[i].m_e_l);
		i++;
	}
	if (main->f)
		free(main->f);
	if (main->ph)
		free(main->ph);
	if (main->mutex_init)
	{
		pthread_mutex_destroy(&main->print_l);
		pthread_mutex_destroy(&main->end_l);
	}
	if (main)
		free(main);
}

void	one_philo(t_main *main)
{
	while (main->s_t > get_time_ms())
		usleep(1);
	ft_print(&main->ph[0], " is thinking\n", 13);
	ft_print(&main->ph[0], " has taken a fork\n", 18);
	usleep(main->t2d * 1000);
	ft_print(&main->ph[0], " died\n", 6);
}

int	main(int argc, char **argv)
{
	t_main		*main;
	pthread_t	monitor_thread;
	int			i;

	main = parsing(argc, argv);
	if (!main)
		return (1);
	if (main->n_ph == 1)
		one_philo(main);
	else
	{
		if (!start_threads(main, &monitor_thread))
			return (printf("Error while creating threads\n"), 1);
		pthread_join(monitor_thread, NULL);
		i = 0;
		while (i < main->n_ph)
			pthread_join(main->ph[i++].th_id, NULL);
	}
	ft_clean(main);
	return (0);
}
