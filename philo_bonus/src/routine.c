/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:56:34 by jlecomte          #+#    #+#             */
/*   Updated: 2022/04/06 18:02:48 by jlecomte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*check_death(void *data)
{
	t_frame		*frame;
	t_philo		*philo;
	long int	now;

	philo = (t_philo *)data;
	frame = philo->frame;
	while (1)
	{
		if (frame->dead)
			return (NULL);
		usleep(1000);
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
	//	printf("on va la\n");
		sem_wait(frame->philo_full);
		usleep(10000);
		if (frame->dead)
			return (NULL);
		n--;
	//	printf("on va bien la et n = %d\n", n);
	}
	frame->wait_meals = 1;
	sem_post(frame->stop);
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
