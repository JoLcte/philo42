/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 17:05:07 by jlecomte          #+#    #+#             */
/*   Updated: 2022/03/03 17:27:25 by jlecomte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    eat_with_forks(t_frame * frame, t_philo *philo)
{
	(void)frame;
	(void)philo;
	return ;
}

void    sleep_and_think(t_frame *frame, t_philo *philo)
{
        const unsigned int      color = frame->palette[philo->id % 36];
        long int        now;

        now = _get_time();
        if (frame->stop || (philo->nb_meals == frame->setup[MEALS]))
                return ;
        pthread_mutex_lock(frame->print);
        printf(PHILO_SLEEPS, color, now - frame->start, philo->id);
        pthread_mutex_unlock(frame->print);
        sleep(frame->setup[SLEEP]);
        now = _get_time();
        if (now - philo->last_ate >= frame->setup[DIE])
        {
                pthread_mutex_lock(frame->print);
                printf(PHILO_DIED, color, now - frame->start, philo->id);
                frame->stop = 1;
                pthread_mutex_unlock(frame->print);
                return ;
        }
	now = _get_time();
        pthread_mutex_lock(frame->print);
        printf(PHILO_THINKS, color, now - frame->start, philo->id);
        pthread_mutex_unlock(frame->print);
}
