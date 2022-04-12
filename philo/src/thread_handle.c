/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:56:34 by jlecomte          #+#    #+#             */
/*   Updated: 2022/04/05 14:46:08 by jlecomte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_meals(t_frame *frame, t_philo *philo)
{
	if (philo->nb_meals == frame->setup[MEALS])
	{
		pthread_mutex_lock(frame->dead);
		++frame->philos_full;
		if (frame->philos_full == frame->setup[NB_PHILO])
		{
			frame->stop = 1;
			pthread_mutex_unlock(frame->dead);
			return (1);
		}
		pthread_mutex_unlock(frame->dead);
		return (0);
	}
	return (0);
}

static int	stop_all(t_frame *frame)
{
	pthread_mutex_lock(frame->dead);
	if (frame->stop)
	{
		pthread_mutex_unlock(frame->dead);
		return (1);
	}
	pthread_mutex_unlock(frame->dead);
	return (0);
}

static void	*meals_routine(void *data)
{
	t_philo	*philo;
	t_frame	*frame;

	philo = (t_philo *)data;
	frame = philo->frame;
	if (philo->id % 2 == 0)
		ft_sleep(frame, frame->setup[EAT] / 2);
	while (1)
	{
		eat_with_forks(frame, philo);
		if (stop_all(frame))
			break ;
		++philo->nb_meals;
		if (check_meals(frame, philo))
			break ;
		if (stop_all(frame))
			break ;
		sleep_and_think(frame, philo);
		if (stop_all(frame))
			break ;
	}
	return (NULL);
}

static void	*routine(void *data)
{
	t_philo	*philo;
	t_frame	*frame;

	philo = (t_philo *)data;
	frame = philo->frame;
	if (philo->id % 2 == 0)
		ft_sleep(frame, frame->setup[EAT] / 2);
	while (1)
	{
		eat_with_forks(frame, philo);
		if (stop_all(frame))
			break ;
		sleep_and_think(frame, philo);
		if (stop_all(frame))
			break ;
	}
	return (NULL);
}

void	thread_actions(t_frame *frame)
{
	const unsigned int	nb_philo = frame->setup[NB_PHILO];
	unsigned int		i;

	i = 0;
	frame->start = _get_time();
	if (frame->setup[MEALS] > 0)
	{
		while (i < nb_philo)
		{
			pthread_create(&frame->philo[i].thd, \
				NULL, meals_routine, (void *)&frame->philo[i]);
			++i;
		}
	}
	else
	{
		while (i < nb_philo)
		{
			pthread_create(&frame->philo[i].thd, \
				NULL, routine, (void *)&frame->philo[i]);
			++i;
		}
	}
}
