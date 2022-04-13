/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 17:05:07 by jlecomte          #+#    #+#             */
/*   Updated: 2022/04/05 14:44:11 by jlecomte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	dead_sleeping(t_frame *frame, t_philo *philo)
{
	long int	alive;

	pthread_mutex_lock(frame->dead);
	if (frame->stop == 1)
	{
		pthread_mutex_unlock(frame->dead);
		return (1);
	}
	alive = _get_time() - philo->last_ate;
	if (alive + frame->setup[SLEEP] >= frame->setup[DIE])
	{
		pthread_mutex_unlock(frame->dead);
		ft_sleep(frame->setup[DIE] - alive);
		pthread_mutex_lock(frame->dead);
		print_info(frame, philo->id, PHILO_DIED);
		frame->stop = 1;
		pthread_mutex_unlock(frame->dead);
		return (1);
	}
	pthread_mutex_unlock(frame->dead);
	return (0);
}

static int	dead_eating(t_frame *frame, t_philo *philo)
{
	pthread_mutex_lock(frame->dead);
	if (frame->stop == 1)
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(frame->dead);
		return (1);
	}
	if (_get_time() - philo->last_ate + frame->setup[EAT] >= frame->setup[DIE])
	{	
		pthread_mutex_unlock(frame->dead);
		ft_sleep(frame->setup[DIE]);
		pthread_mutex_lock(frame->dead);
		print_info(frame, philo->id, PHILO_DIED);
		frame->stop = 1;
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(frame->dead);
		return (1);
	}
	pthread_mutex_unlock(frame->dead);
	return (0);
}

static int	is_dead(t_frame *frame, t_philo *philo, int lock)
{	
	pthread_mutex_lock(frame->dead);
	if (frame->stop == 1)
	{
		if (lock >= 1)
			pthread_mutex_unlock(philo->l_fork);
		if (lock == 2)
			pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(frame->dead);
		return (1);
	}
	if (_get_time() - philo->last_ate >= frame->setup[DIE])
	{	
		print_info(frame, philo->id, PHILO_DIED);
		frame->stop = 1;
		if (lock >= 1)
			pthread_mutex_unlock(philo->l_fork);
		if (lock == 2)
			pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(frame->dead);
		return (1);
	}
	pthread_mutex_unlock(frame->dead);
	return (0);
}

void	eat_with_forks(t_frame *frame, t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	if (is_dead(frame, philo, 1))
		return ;
	print_info(frame, philo->id, PHILO_TAKES_FORK);
	pthread_mutex_lock(philo->r_fork);
	if (is_dead(frame, philo, 2))
		return ;
	print_info(frame, philo->id, PHILO_TAKES_FORK);
	if (is_dead(frame, philo, 2))
		return ;
	print_info(frame, philo->id, PHILO_EATS);
	philo->last_ate = _get_time();
	if (dead_eating(frame, philo))
		return ;
	ft_sleep(frame->setup[EAT]);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	sleep_and_think(t_frame *frame, t_philo *philo)
{
	print_info(frame, philo->id, PHILO_SLEEPS);
	if (dead_sleeping(frame, philo))
		return ;
	ft_sleep(frame->setup[SLEEP]);
	print_info(frame, philo->id, PHILO_THINKS);
	if (is_dead(frame, philo, 0))
		return ;
}
