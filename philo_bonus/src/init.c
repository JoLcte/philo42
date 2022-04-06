/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 17:34:34 by jlecomte          #+#    #+#             */
/*   Updated: 2022/04/06 17:48:04 by jlecomte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	init_philos(t_frame *frame, t_philo *philo, int nb_philo)
{
	int	i;

	i = 0;
	while (i < nb_philo)
	{
		philo[i].frame = frame;
		philo[i].id = i + 1;
		philo[i].nb_meals = 0;
		philo[i].last_ate = _get_time();
		philo[i].pid = -1;
		++i;
	}
}

static int	init_sem(t_frame *frame)
{
	sem_unlink("philo_full");
	sem_unlink("forks");
	sem_unlink("stop");
	sem_unlink("print");
	sem_unlink("died");
	frame->philo_full = NULL;
	frame->forks = NULL;
	frame->stop = NULL;
	frame->print = NULL;
	frame->philo_full = sem_open("philo_full", O_CREAT | O_EXCL, 0644, 1);
	if (frame->philo_full == SEM_FAILED)
		return (1);
	frame->forks = sem_open("forks", O_CREAT | O_EXCL, 0644, \
			frame->setup[NB_PHILO]);
	if (frame->forks == SEM_FAILED)
		return (1);
	frame->stop = sem_open("stop", O_CREAT | O_EXCL, 0644, 0);
	if (frame->stop == SEM_FAILED)
		return (1);
	frame->print = sem_open("print", O_CREAT | O_EXCL, 0644, 1);
	if (frame->print == SEM_FAILED)
		return (1);
	return (0);
}

int	init_data(t_frame *frame)
{
	const int		nb_philo = frame->setup[NB_PHILO];

	frame->philo = malloc(sizeof(t_philo) * nb_philo);
	if (!frame->philo)
		return (error_exit(frame, MALLOC_ERR));
	frame->check_death = 0;
	frame->check_meals = 0;
	if (init_sem(frame))
		return (error_exit(frame, SEM_ERR));
	init_philos(frame, frame->philo, nb_philo);
	fill_colors(frame->palette, 36);
	frame->start = 0;
	frame->dead = 0;
	frame->wait_meals = 0;
	return (0);
}
