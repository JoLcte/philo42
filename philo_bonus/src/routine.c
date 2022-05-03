/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:56:34 by jlecomte          #+#    #+#             */
/*   Updated: 2022/05/03 21:09:40 by jlecomte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	clean_exit(t_frame *frame)
{
	free(frame->philo);
	sem_close(frame->forks);
	sem_close(frame->print);
	sem_close(frame->philo_full);
	sem_close(frame->check);
	sem_close(frame->stop);
	exit(0);
}

void	*check_death(void *data)
{
	t_frame		*frame;
	t_philo		*philo;
	long int	now;

	philo = (t_philo *)data;
	frame = philo->frame;
	while (1)
	{
		sem_wait(frame->check);
		if (frame->dead)
			return (NULL);
		sem_post(frame->check);
		usleep(1000);
		now = _get_time();
		sem_wait(frame->check);
		if (now - philo->last_ate >= frame->setup[DIE])
		{
			if (frame->setup[MEALS] > 0)
				sem_post(frame->philo_full);
			sem_post(frame->check);
			print_info(frame, philo->id, PHILO_DIED, 1);
			sem_post(frame->stop);
			return (NULL);
		}
		sem_post(frame->check);
	}
	return (NULL);
}

void	*check_meals(void *data)
{
	t_frame	*frame;
	int		n;
	int		i;
	int		count;

	frame = (t_frame *)data;
	n = frame->setup[NB_PHILO];
	if (n == 1)
		return (NULL);
	count = 0;
	while (count < frame->setup[MEALS])
	{
		i = 0;
		while (i < frame->setup[NB_PHILO])
		{
			sem_wait(frame->philo[i].meals_eaten);
			++i;
		}
		++count;
	}
	frame->wait_meals = 1;
	usleep(10000);
	sem_post(frame->stop);
	return (NULL);
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
