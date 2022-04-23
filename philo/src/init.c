/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 17:34:34 by jlecomte          #+#    #+#             */
/*   Updated: 2022/04/23 12:48:07 by jlecomte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_first_philo(t_frame *frame, t_philo *philo, int nb_philo)
{
	philo[0].id = 1;
	philo[0].nb_meals = 0;
	philo[0].last_ate = _get_time();
	philo[0].l_fork = &frame->forks[0];
	philo[0].frame = frame;
	if (nb_philo == 1)
	{
		philo[0].r_fork = NULL;
		return (1);
	}
	philo[0].r_fork = &frame->forks[1];
	return (0);
}

static int	init_philos(t_frame *frame, t_philo *philo, int nb_philo)
{
	int	i;

	i = 0;
	if (init_first_philo(frame, philo, nb_philo))
		return (1);
	while (++i < nb_philo - 1)
	{
		philo[i].id = i + 1;
		philo[i].nb_meals = 0;
		philo[i].last_ate = _get_time();
		philo[i].l_fork = &frame->forks[i];
		philo[i].r_fork = &frame->forks[i + 1];
		philo[i].frame = frame;
	}
	philo[i].id = i + 1;
	philo[i].nb_meals = 0;
	philo[i].last_ate = _get_time();
	philo[i].l_fork = &frame->forks[i];
	philo[i].r_fork = &frame->forks[0];
	philo[i].frame = frame;
	return (0);
}

static int	init_mutex(t_frame *frame)
{
	const int	nb_philo = frame->setup[NB_PHILO];
	int			i;

	frame->lock = malloc(sizeof(pthread_mutex_t));
	frame->forks = malloc(sizeof(pthread_mutex_t) * nb_philo);
	if (!frame->forks || !frame->lock)
		return (error_exit(frame, MALLOC_ERR));
	if (pthread_mutex_init(frame->lock, NULL))
		return (error_exit(frame, MUTEX_ERR));
	i = 0;
	while (i < nb_philo)
	{
		if (pthread_mutex_init(&frame->forks[i], NULL))
			return (error_exit(frame, MUTEX_ERR));
		++i;
	}
	return (0);
}

static int	one_philo(t_frame *frame)
{
	printf(PHILO_TAKES_FORK, frame->palette[0], (long int)0, 1);
	usleep(frame->setup[DIE] * 1000);
	printf(PHILO_DIED, frame->palette[0], (long int)frame->setup[DIE], 1);
	pthread_mutex_destroy(&frame->forks[0]);
	pthread_mutex_destroy(frame->lock);
	free(frame->lock);
	free(frame->forks);
	free(frame->philo);
	return (1);
}

int	init_data(t_frame *frame)
{
	const int		nb_philo = frame->setup[NB_PHILO];

	frame->philo = malloc(sizeof(t_philo) * nb_philo);
	if (!frame->philo)
		return (error_exit(frame, MALLOC_ERR));
	if (init_mutex(frame))
		return (1);
	frame->start = 0;
	frame->stop = 0;
	frame->philos_full = 0;
	fill_colors(frame->palette, 36);
	if (init_philos(frame, frame->philo, nb_philo))
		return (one_philo(frame));
	return (0);
}
