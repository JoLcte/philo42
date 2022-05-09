/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:56:34 by jlecomte          #+#    #+#             */
/*   Updated: 2022/05/05 13:55:01 by jlecomte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	clean_exit(t_frame *frame)
{
	int	i;

	i = 0;
	sem_close(frame->forks);
	sem_close(frame->print);
	sem_close(frame->philo_full);
	sem_close(frame->check);
	sem_close(frame->stop);
	while (i < frame->setup[NB_PHILO])
	{
		sem_close(frame->philo[i].meals_eaten);
		++i;
	}
	free(frame->philo);
	exit(0);
}

void	meals_routine(t_frame *frame, t_philo *philo)
{
	sem_wait(frame->check);
	philo->last_ate = _get_time();
	sem_post(frame->check);
	while (1)
	{
		eat_with_forks(frame, philo);
		++philo->nb_meals;
		sem_post(philo->meals_eaten);
		if (philo->nb_meals == frame->setup[MEALS])
			clean_exit(frame);
		sleep_and_think(frame, philo);
	}
}

void	routine(t_frame *frame, t_philo *philo)
{
	sem_wait(frame->check);
	philo->last_ate = _get_time();
	sem_post(frame->check);
	while (1)
	{
		eat_with_forks(frame, philo);
		sleep_and_think(frame, philo);
	}
}
