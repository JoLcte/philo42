/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 17:05:07 by jlecomte          #+#    #+#             */
/*   Updated: 2022/04/05 15:16:19 by jlecomte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eat_with_forks(t_frame *frame, t_philo *philo)
{
	sem_wait(frame->forks);
	print_info(frame, philo->id, PHILO_TAKES_FORK, 0);
	ft_sleep(frame, 0.01);
	sem_wait(frame->forks);
	print_info(frame, philo->id, PHILO_TAKES_FORK, 0);
	print_info(frame, philo->id, PHILO_EATS, 0);
	philo->last_ate = _get_time();
	ft_sleep(frame, frame->setup[EAT]);
	sem_post(frame->forks);
	sem_post(frame->forks);
}

void	sleep_and_think(t_frame *frame, t_philo *philo)
{
	print_info(frame, philo->id, PHILO_SLEEPS, 0);
	ft_sleep(frame, frame->setup[SLEEP]);
	print_info(frame, philo->id, PHILO_THINKS, 0);
}
