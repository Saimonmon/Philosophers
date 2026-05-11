/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssousmat <ssousmat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:16:33 by ssousmat          #+#    #+#             */
/*   Updated: 2025/05/31 18:36:58 by ssousmat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	init_ph(t_main *main)
{
	int	i;

	main->ph = ft_calloc(sizeof(t_philo), main->n_ph);
	if (!main->ph)
		return (false);
	main->s_t = get_time_ms() + main->n_ph + 200;
	i = 0;
	while (i < main->n_ph)
	{
		main->ph[i].id = i + 1;
		main->ph[i].p_m = main->s_t;
		main->ph[i].r_f = &main->f[i];
		main->ph[i].l_f = &main->f[(i + 1) % main->n_ph];
		main->ph[i].main = main;
		i++;
	}
	return (true);
}

bool	init_mutex_ph_clean(t_main *main, int i, size_t flag)
{
	pthread_mutex_destroy(&main->print_l);
	pthread_mutex_destroy(&main->end_l);
	if (flag >= 1)
		pthread_mutex_destroy(&main->f[i]);
	if (flag == 2)
		pthread_mutex_destroy(&main->ph[i].p_m_l);
	while (0 <= --i)
	{
		pthread_mutex_destroy(&main->f[i]);
		pthread_mutex_destroy(&main->ph[i].p_m_l);
		pthread_mutex_destroy(&main->ph[i].m_e_l);
	}
	return (false);
}

bool	init_mutex(t_main *main)
{
	int	i;

	if (pthread_mutex_init(&main->print_l, NULL))
		return (false);
	if (pthread_mutex_init(&main->end_l, NULL))
	{
		pthread_mutex_destroy(&main->print_l);
		return (false);
	}
	i = 0;
	while (i < main->n_ph)
	{
		if (pthread_mutex_init(&main->f[i], NULL))
			return (init_mutex_ph_clean(main, i, 0));
		if (pthread_mutex_init(&main->ph[i].p_m_l, NULL))
			return (init_mutex_ph_clean(main, i, 1));
		if (pthread_mutex_init(&main->ph[i].m_e_l, NULL))
			return (init_mutex_ph_clean(main, i, 2));
		i++;
	}
	main->mutex_init = true;
	return (true);
}

bool	init_main(t_main *main, int argc, char **argv)
{
	main->n_ph = ft_atoi(argv[1]);
	main->t2d = ft_atoi(argv[2]);
	main->t2e = ft_atoi(argv[3]);
	main->t2s = ft_atoi(argv[4]);
	if (main->n_ph <= 0 \
		|| main->t2d <= 0 || main->t2e <= 0 || main->t2s <= 0)
		return (false);
	if (argc == 6)
	{
		main->mx_m_f = true;
		main->mx_m = ft_atoi(argv[5]);
		if (main->mx_m <= 0)
			return (false);
	}
	main->f = ft_calloc(sizeof(pthread_mutex_t), main->n_ph);
	if (!main->f)
		return (false);
	return (true);
}

t_main	*parsing(int argc, char **argv)
{
	t_main	*main;
	int		i;

	if (argc != 5 && argc != 6)
		return (printf("Wrong argument number\n"), NULL);
	i = 0;
	while (++i < argc)
		if (!ft_istherenum(argv[i]))
			return (printf("Wrong argument format\n"), NULL);
	main = ft_calloc(sizeof(t_main), 1);
	if (!main)
		return (NULL);
	if (!init_main(main, argc, argv))
		return (printf("Wrong argument value\n"), ft_clean(main), NULL);
	if (!init_ph(main))
		return (printf("Error while creating philos\n"), ft_clean(main), NULL);
	if (!init_mutex(main))
		return (printf("Error while creating mutexes\n"), ft_clean(main), NULL);
	return (main);
}
