/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 13:52:06 by jlecomte          #+#    #+#             */
/*   Updated: 2022/05/05 13:55:55 by jlecomte         ###   ########.fr       */
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
		sem_wait(frame->check);
		if (frame->dead)
			return (NULL);
		sem_post(frame->check);
		usleep(100);
		sem_wait(frame->check);
		now = _get_time();
		if (now - philo->last_ate >= frame->setup[DIE])
		{
			sem_post(frame->check);
			print_info(frame, philo->id, DIED);
			sem_post(frame->stop);
			return (NULL);
		}
		sem_post(frame->check);
	}
	return (NULL);
}

static	int	check_meals_loop(t_frame *frame)
{
	int	i;
	int	count;

	count = 0;
	while (count < frame->setup[MEALS])
	{
		i = 0;
		while (i < frame->setup[NB_PHILO])
		{
			sem_wait(frame->check);
			if (frame->dead)
			{
				sem_post(frame->check);
				return (1);
			}
			sem_post(frame->check);
			sem_wait(frame->philo[i].meals_eaten);
			++i;
		}
		++count;
	}
	return (0);
}

void	*check_meals(void *data)
{
	t_frame	*frame;

	frame = (t_frame *)data;
	if (frame->setup[NB_PHILO] == 1)
		return (NULL);
	usleep(10000);
	if (check_meals_loop(frame))
		return (NULL);
	frame->wait_meals = 1;
	sem_post(frame->stop);
	return (NULL);
}
