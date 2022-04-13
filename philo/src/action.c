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

static int	dead_sleeping(t_frame *frame, t_philo *philo, long int now)
{
	long int	alive;

	pthread_mutex_lock(frame->dead);
	if (frame->stop == 1)
	{
		pthread_mutex_unlock(frame->dead);
		return (1);
	}
	alive = now - philo->last_ate;
	if (alive + frame->setup[SLEEP] >= frame->setup[DIE])
	{
		pthread_mutex_unlock(frame->dead);
		ft_sleep(frame->setup[DIE] - alive);
		pthread_mutex_lock(frame->dead);
		now = _get_time();
		print_info(frame, philo->id, now, PHILO_DIED);
		frame->stop = 1;
		pthread_mutex_unlock(frame->dead);
		return (1);
	}
	pthread_mutex_unlock(frame->dead);
	return (0);
}

static int	dead_eating(t_frame *frame, t_philo *philo, long int now)
{
	pthread_mutex_lock(frame->dead);
	if (frame->stop == 1)
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(frame->dead);
		return (1);
	}
	if (now - philo->last_ate + frame->setup[EAT] >= frame->setup[DIE])
	{	
		pthread_mutex_unlock(frame->dead);
		ft_sleep(frame->setup[DIE]);
		pthread_mutex_lock(frame->dead);
		now = _get_time();
		print_info(frame, philo->id, now, PHILO_DIED);
		frame->stop = 1;
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(frame->dead);
		return (1);
	}
	pthread_mutex_unlock(frame->dead);
	return (0);
}

static int	is_dead(t_frame *frame, t_philo *philo, long int now, int lock)
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
	if (now - philo->last_ate >= frame->setup[DIE])
	{	
		now = _get_time();
		print_info(frame, philo->id, now, PHILO_DIED);
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
	long int		now;

	pthread_mutex_lock(philo->l_fork);
	now = _get_time();
	if (is_dead(frame, philo, now, 1))
		return ;
	now = _get_time();
	print_info(frame, philo->id, now, PHILO_TAKES_FORK);
	pthread_mutex_lock(philo->r_fork);
	now = _get_time();
	if (is_dead(frame, philo, now, 2))
		return ;
	now = _get_time();
	print_info(frame, philo->id, now, PHILO_TAKES_FORK);
	now = _get_time();
	if (is_dead(frame, philo, now, 2))
		return ;
	now = _get_time();
	print_info(frame, philo->id, now, PHILO_EATS);
	philo->last_ate = now;
	if (dead_eating(frame, philo, now))
		return ;
	ft_sleep(frame->setup[EAT]);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	sleep_and_think(t_frame *frame, t_philo *philo)
{
	long int	now;

	now = _get_time();
	print_info(frame, philo->id, now, PHILO_SLEEPS);
	if (dead_sleeping(frame, philo, now))
		return ;
	ft_sleep(frame->setup[SLEEP]);
	now = _get_time();
	print_info(frame, philo->id, now, PHILO_THINKS);
	if (is_dead(frame, philo, now, 0))
		return ;
}
