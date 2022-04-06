/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:56:34 by jlecomte          #+#    #+#             */
/*   Updated: 2022/03/17 01:45:49 by jlecomte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*check_death(void *data)
{
	t_frame		*frame;
	t_philo		*philo;
	long int	now;

	frame = (t_frame *)data;
	philo = &frame->philo[frame->i];
	while (1)
	{
		now = _get_time();
		if (now - philo->last_ate >= frame->setup[DIE])
		{
			print_info(frame, philo->id, PHILO_DIED, 1);
			sem_post(frame->stop);
			sem_post(frame->philo_full);
			return (NULL);
		}
	}
	return (NULL);
}

void	*check_meals(void *data)
{
	t_frame	*frame;
	int		n;

	frame = (t_frame *)data;
	n = frame->setup[NB_PHILO];
	if (n == 1)
		return (NULL);
	while (n)
	{
		sem_wait(frame->philo_full);
		if (frame->dead)
			return (NULL);
		n--;
	}
	frame->wait_meals = 1;
	sem_post(frame->stop);
	printf(END_MEALS, frame->setup[MEALS]);
	return (NULL);
}

void	meals_routine(t_frame *frame, t_philo *philo)
{
	philo->last_ate = _get_time();
	while (1)
	{
		eat_with_forks(frame, philo);
		++philo->nb_meals;
		sleep_and_think(frame, philo);
		if (philo->nb_meals == frame->setup[MEALS])
		{
			sem_post(frame->philo_full);
			exit(0);
		}
	}
}

void	routine(t_frame *frame, t_philo *philo)
{
	philo->last_ate = _get_time();
	while (1)
	{
		eat_with_forks(frame, philo);
		sleep_and_think(frame, philo);
	}
}
