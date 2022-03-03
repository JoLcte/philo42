/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:56:34 by jlecomte          #+#    #+#             */
/*   Updated: 2022/03/03 17:44:05 by jlecomte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*count_meals_routine(void *data)
{
	t_frame * const frame = (t_frame *)data;
	t_philo * const philo = &frame->philo[frame->i];

	frame->start = _get_time();
	philo->last_ate = frame->start;
	while (!frame->stop && (philo->nb_meals < frame->setup[MEALS]))
	{
		eat_with_forks(frame, philo);
		++philo->nb_meals;
		sleep_and_think(frame, philo);
	}
	return (NULL);
}

static void	*routine(void *data)
{
	t_frame * const frame = (t_frame *)data;
	t_philo * const philo = &frame->philo[frame->i];
	
	frame->start = _get_time();
	philo->last_ate = frame->start;
	while (!frame->stop)
	{
		eat_with_forks(frame, philo);
		sleep_and_think(frame, philo);
	}
	return (NULL);
}



void	thread_actions(t_frame *frame)
{
	const unsigned int	nb_philo = frame->setup[NB_PHILO];
	unsigned int			i;

	i = 0;
	if (frame->setup[MEALS] > 0)
	{
		while (i < nb_philo)
		{
			frame->i = i;
			pthread_create(&frame->philo_thread[i], \
				 NULL, count_meals_routine, (void *)frame);
			++i;
		}
		if (frame->stop)
			return ;
			// do something to stop everything
	}
	else
	{
		while (i < nb_philo)
		{
			frame->i = i;
			pthread_create(&frame->philo_thread[i], \
				 NULL, routine, (void *)frame);
			++i;
		}
		if (frame->stop)
			return ;
	}
}
