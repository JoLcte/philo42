/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:56:34 by jlecomte          #+#    #+#             */
/*   Updated: 2022/04/24 17:03:38 by jlecomte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_meals(t_frame *frame, t_philo *philo)
{
	if (philo->nb_meals == frame->setup[MEALS])
	{
		pthread_mutex_lock(frame->lock);
		++frame->philos_full;
		if (frame->philos_full == frame->setup[NB_PHILO])
		{
			frame->stop = 1;
			pthread_mutex_unlock(frame->lock);
			return (1);
		}
		pthread_mutex_unlock(frame->lock);
		return (0);
	}
	return (0);
}

int	stop_all(t_frame *frame, t_philo *philo)
{
	pthread_mutex_lock(frame->lock);
	if (frame->stop)
	{
		pthread_mutex_unlock(frame->lock);
		if (philo->locks == 2)
		{
			pthread_mutex_unlock(philo->l_fork);
			pthread_mutex_unlock(philo->r_fork);
		}
		else if (philo->locks == 1)
		{
			if (philo->id % 2 == 0)
				pthread_mutex_unlock(philo->r_fork);
			else
				pthread_mutex_unlock(philo->l_fork);

		}
		return (1);
	}
	pthread_mutex_unlock(frame->lock);
	return (0);
}

static void	is_dead(t_frame *frame)
{
	int	i;

	while (1)
	{
		i = 0;
		pthread_mutex_lock(frame->lock);
		if (frame->stop)
		{
			pthread_mutex_unlock(frame->lock);
			return ;
		}
		pthread_mutex_unlock(frame->lock);
		while (i < frame->setup[NB_PHILO])
		{
			pthread_mutex_lock(frame->lock);
			if (frame->stop)
			{
				pthread_mutex_unlock(frame->lock);
				return ;
			}
			if (_get_time() - frame->philo[i].last_ate >= frame->setup[DIE])
			{
				print_info(frame, frame->philo[i].id, PHILO_DIED, 1);
				frame->stop = 1;
				pthread_mutex_unlock(frame->lock);
				return ;
			}
			pthread_mutex_unlock(frame->lock);
			++i;
		}
		usleep(1000);
	}
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
	usleep(2000);
	is_dead(frame);
}
