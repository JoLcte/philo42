/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 17:05:07 by jlecomte          #+#    #+#             */
/*   Updated: 2022/04/25 15:41:11 by jlecomte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eat_with_forks(t_frame *frame, t_philo *philo)
{
	sem_wait(frame->forks);
	print_info(frame, philo->id, PHILO_TAKES_FORK, 0);
	sem_wait(frame->forks);
	print_info(frame, philo->id, PHILO_TAKES_FORK, 0);
	print_info(frame, philo->id, PHILO_EATS, 0);
	sem_wait(frame->check);
	philo->last_ate = _get_time();
	sem_post(frame->check);
	ft_sleep(frame->setup[EAT]);
	sem_post(frame->forks);
	sem_post(frame->forks);
}

void	sleep_and_think(t_frame *frame, t_philo *philo)
{
	print_info(frame, philo->id, PHILO_SLEEPS, 0);
	ft_sleep(frame->setup[SLEEP]);
	print_info(frame, philo->id, PHILO_THINKS, 0);
}
