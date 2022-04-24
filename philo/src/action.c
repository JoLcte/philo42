/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 17:05:07 by jlecomte          #+#    #+#             */
/*   Updated: 2022/04/24 18:54:41 by jlecomte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat_with_forks(t_frame *frame, t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	philo->locks = 1;
	pthread_mutex_lock(frame->lock);
	if (print_info(frame, philo->id, PHILO_TAKES_FORK, 0))
		return ;
	pthread_mutex_lock(philo->r_fork);
	philo->locks = 2;
	pthread_mutex_lock(frame->lock);
	if (print_info(frame, philo->id, PHILO_TAKES_FORK, 0))
		return ;
	pthread_mutex_lock(frame->lock);
	if (print_info(frame, philo->id, PHILO_EATS, 0))
		return ;
	pthread_mutex_lock(frame->lock);
	philo->last_ate = _get_time();
	pthread_mutex_unlock(frame->lock);
	ft_sleep(frame->setup[EAT]);
	pthread_mutex_unlock(philo->l_fork);
	philo->locks = 1;
	pthread_mutex_unlock(philo->r_fork);
	philo->locks = 0;
}

void	sleep_and_think(t_frame *frame, t_philo *philo)
{
	pthread_mutex_lock(frame->lock);
	if (print_info(frame, philo->id, PHILO_SLEEPS, 0))
		return ;
	ft_sleep(frame->setup[SLEEP]);
	pthread_mutex_lock(frame->lock);
	if (print_info(frame, philo->id, PHILO_THINKS, 0))
		return ;
}

void	*meals_routine(void *data)
{
	t_philo	*philo;
	t_frame	*frame;

	philo = (t_philo *)data;
	frame = philo->frame;
	if (philo->id % 2 == 0)
		ft_sleep(frame->setup[EAT] / 2);
	while (1)
	{
		eat_with_forks(frame, philo);
		if (stop_all(frame, philo, 1))
			break ;
		++philo->nb_meals;
		if (check_meals(frame, philo))
			break ;
		if (stop_all(frame, philo, 1))
			break ;
		sleep_and_think(frame, philo);
		if (stop_all(frame, philo, 1))
			break ;
	}
	return (NULL);
}

void	*routine(void *data)
{
	t_philo	*philo;
	t_frame	*frame;

	philo = (t_philo *)data;
	frame = philo->frame;
	pthread_mutex_lock(frame->lock);
	philo->last_ate = _get_time();
	pthread_mutex_unlock(frame->lock);
	if (philo->id % 2 == 0)
		ft_sleep(frame->setup[EAT] / 2);
	while (1)
	{
		eat_with_forks(frame, philo);
		if (stop_all(frame, philo, 1))
			break ;
		sleep_and_think(frame, philo);
		if (stop_all(frame, philo, 1))
			break ;
	}
	return (NULL);
}
