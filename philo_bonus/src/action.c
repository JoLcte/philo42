/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 17:05:07 by jlecomte          #+#    #+#             */
/*   Updated: 2022/05/04 15:26:36 by jlecomte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eat_with_forks(t_frame *frame, t_philo *philo)
{
	sem_wait(frame->forks);
	print_info(frame, philo->id, FORK);
	sem_wait(frame->forks);
	print_info(frame, philo->id, FORK);
	print_info(frame, philo->id, EATS);
	sem_wait(frame->check);
	philo->last_ate = _get_time();
	sem_post(frame->check);
	ft_sleep(frame->setup[EAT]);
	sem_post(frame->forks);
	sem_post(frame->forks);
}

void	sleep_and_think(t_frame *frame, t_philo *philo)
{
	print_info(frame, philo->id, SLEEPS);
	ft_sleep(frame->setup[SLEEP]);
	print_info(frame, philo->id, THINKS);
}
