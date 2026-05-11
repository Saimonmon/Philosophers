/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssousmat <ssousmat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 18:41:20 by ssousmat          #+#    #+#             */
/*   Updated: 2025/05/31 18:42:23 by ssousmat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct s_main	t_main;

typedef struct s_philo
{
	pthread_t		th_id;
	size_t			id;
	long long		p_m;
	int				m_e;
	pthread_mutex_t	p_m_l;
	pthread_mutex_t	m_e_l;
	pthread_mutex_t	*l_f;
	pthread_mutex_t	*r_f;
	t_main			*main;
}	t_philo;

typedef struct s_main
{
	int				n_ph;
	int				t2d;
	int				t2e;
	int				t2s;
	int				mx_m;
	bool			mx_m_f;
	long long		s_t;
	bool			end;
	bool			mutex_init;
	pthread_mutex_t	*f;
	pthread_mutex_t	print_l;
	pthread_mutex_t	end_l;
	t_philo			*ph;
}	t_main;

// philo.c
void		ft_clean(t_main *main);

//	init.c
t_main		*parsing(int argc, char **argv);
bool		start_threads(t_main *main, pthread_t *monitor_thread);

//	routine.c
void		*philo_routine(void *arg);

//	death.c
void		*monitor_end(void *arg);
bool		death(t_main *main);
bool		mx_m_reached(t_main	*main);

//	utils.c
bool		get_end(t_main *main);
long long	get_time_ms(void);
bool		ft_usleep(long long duration_ms, t_main *main);
void		ft_print(t_philo *ph, const char *msg, size_t len);

//	libft_utils.c
void		*ft_calloc(size_t size, size_t nitems);
void		ft_putnbr_fd(long long n, int fd);
bool		ft_istherenum(const char *str);
int			ft_atoi(const char *str);