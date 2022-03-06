/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 17:05:07 by jlecomte          #+#    #+#             */
/*   Updated: 2022/03/04 19:05:13 by jlecomte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_dead(t_frame *frame, t_philo *philo, long int now, int lock)
{	
        const unsigned int      color = frame->palette[philo->id % 36];

	if (now - philo->last_ate >= frame->setup[DIE])
	{	
                pthread_mutex_lock(frame->print);
                printf(PHILO_DIED, color, now - frame->start, philo->id);
                frame->stop = 1;
                pthread_mutex_unlock(frame->print);
		if (lock >= 1)
			pthread_mutex_unlock(philo->l_fork);
		if (lock == 2)
			pthread_mutex_unlock(philo->r_fork);
		return (1);
	}
	return (0);
}

void    eat_with_forks(t_frame * frame, t_philo *philo)
{
        const unsigned int      color = frame->palette[philo->id % 36];
	long int		now;

	now = _get_time();
	if (is_dead(frame, philo, now, 0))
		return ;
	pthread_mutex_lock(philo->l_fork);
	pthread_mutex_lock(frame->print);
	printf(PHILO_TAKES_FORK, color, now - frame->start, philo->id);
	pthread_mutex_unlock(frame->print);
	now = _get_time();
	if (is_dead(frame, philo, now, 1))
		return ;
	pthread_mutex_lock(philo->r_fork);
	pthread_mutex_lock(frame->print);
	printf(PHILO_TAKES_FORK, color, now - frame->start, philo->id);
	pthread_mutex_unlock(frame->print);
	now = _get_time();
	if (is_dead(frame, philo, now, 2))
		return ;
	pthread_mutex_lock(frame->print);
	printf(PHILO_EATS, color, now - frame->start, philo->id);
	pthread_mutex_unlock(frame->print);
	usleep(frame->setup[EAT] * 1000);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void    sleep_and_think(t_frame *frame, t_philo *philo)
{
        const unsigned int      color = frame->palette[philo->id % 36];
        long int        now;

        if (frame->stop || (philo->nb_meals == frame->setup[MEALS]))
                return ;
        now = _get_time();
        pthread_mutex_lock(frame->print);
        printf(PHILO_SLEEPS, color, now - frame->start, philo->id);
        pthread_mutex_unlock(frame->print);
        usleep(frame->setup[SLEEP] * 1000);
        now = _get_time();
        if (is_dead(frame, philo, now, 0))
                return ;
	now = _get_time();
        pthread_mutex_lock(frame->print);
        printf(PHILO_THINKS, color, now - frame->start, philo->id);
        pthread_mutex_unlock(frame->print);
}
