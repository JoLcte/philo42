/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 17:05:07 by jlecomte          #+#    #+#             */
/*   Updated: 2022/04/22 16:07:04 by jlecomte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	dead_sleeping(t_frame *frame, t_philo *philo)
{
	long int	alive;

	pthread_mutex_lock(frame->lock);
	if (frame->stop == 1)
	{
		pthread_mutex_unlock(frame->lock);
		return (1);
	}
	alive = _get_time() - philo->last_ate;
	if (alive + frame->setup[SLEEP] >= frame->setup[DIE])
	{
		ft_sleep(frame->setup[DIE] - alive);
		print_info(frame, philo->id, PHILO_DIED, 1);
		frame->stop = 1;
		pthread_mutex_unlock(frame->lock);
		return (1);
	}
	pthread_mutex_unlock(frame->lock);
	return (0);
}

static int	dead_eating(t_frame *frame, t_philo *philo)
{
	pthread_mutex_lock(frame->lock);
	if (frame->stop == 1)
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(frame->lock);
		return (1);
	}
	if (_get_time() - philo->last_ate + frame->setup[EAT] >= frame->setup[DIE])
	{	
		ft_sleep(frame->setup[DIE]);
		print_info(frame, philo->id, PHILO_DIED, 1);
		frame->stop = 1;
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(frame->lock);
		return (1);
	}
	pthread_mutex_unlock(frame->lock);
	return (0);
}

static int	is_dead(t_frame *frame, t_philo *philo, int lock)
{	
	pthread_mutex_lock(frame->lock);
	if (frame->stop == 1)
	{
		if (lock >= 1)
			pthread_mutex_unlock(philo->l_fork);
		if (lock == 2)
			pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(frame->lock);
		return (1);
	}
	if (_get_time() - philo->last_ate >= frame->setup[DIE])
	{	
		print_info(frame, philo->id, PHILO_DIED, 1);
		frame->stop = 1;
		if (lock >= 1)
			pthread_mutex_unlock(philo->l_fork);
		if (lock == 2)
			pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(frame->lock);
		return (1);
	}
	pthread_mutex_unlock(frame->lock);
	return (0);
}

void	eat_with_forks(t_frame *frame, t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	if (is_dead(frame, philo, 1))
		return ;
	pthread_mutex_lock(frame->lock);
	print_info(frame, philo->id, PHILO_TAKES_FORK, 0);
	pthread_mutex_lock(philo->r_fork);
	if (is_dead(frame, philo, 2))
		return ;
	pthread_mutex_lock(frame->lock);
	print_info(frame, philo->id, PHILO_TAKES_FORK, 0);
	if (is_dead(frame, philo, 2))
		return ;
	pthread_mutex_lock(frame->lock);
	print_info(frame, philo->id, PHILO_EATS, 0);
	philo->last_ate = _get_time();
	if (dead_eating(frame, philo))
		return ;
	ft_sleep(frame->setup[EAT]);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	sleep_and_think(t_frame *frame, t_philo *philo)
{
	pthread_mutex_lock(frame->lock);
	if (print_info(frame, philo->id, PHILO_SLEEPS, 0))
		return ;
	if (dead_sleeping(frame, philo))
		return ;
	ft_sleep(frame->setup[SLEEP]);
	pthread_mutex_lock(frame->lock);
	if (print_info(frame, philo->id, PHILO_THINKS, 0))
		return ;
	if (is_dead(frame, philo, 0))
		return ;
}
