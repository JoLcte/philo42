/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:56:34 by jlecomte          #+#    #+#             */
/*   Updated: 2022/04/25 16:14:21 by jlecomte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	exit_clean(t_frame *frame)
{
	printf("coucou\n");
	usleep(1000000);
	free(frame->philo);
	sem_close(frame->forks);
	sem_close(frame->print);
	sem_close(frame->philo_full);
	sem_close(frame->check);
	sem_close(frame->stop);
	exit(0);
}

void	*check_death(void *data)
{
	t_frame		*frame;
	t_philo		*philo;
	long int	now;

	philo = (t_philo *)data;
	frame = philo->frame;
	while (1)
	{
		sem_wait(frame->check);
		if (frame->dead)
			return (NULL);
		sem_post(frame->check);
		usleep(1000);
		now = _get_time();
		sem_wait(frame->check);
		if (now - philo->last_ate >= frame->setup[DIE])
		{
			sem_post(frame->check);
			print_info(frame, philo->id, PHILO_DIED, 1);
			sem_post(frame->stop);
			return (NULL);
		}
		sem_post(frame->check);
	}
	return (NULL);
}

void	*check_meals(void *data)
{
	t_frame	*frame;
	int		n;

	frame = (t_frame *)data;
	n = frame->setup[NB_PHILO];
	if (n == 1)
		return (NULL);
	while (n)
	{
		sem_wait(frame->philo_full);
		usleep(10000);
		if (frame->dead){
			printf("coucou\n");
			return (NULL);}
		n--;
	}
	frame->wait_meals = 1;
	sem_post(frame->stop);
	return (NULL);
}

void	meals_routine(t_frame *frame, t_philo *philo)
{
	sem_wait(frame->check);
	philo->last_ate = _get_time();
	sem_post(frame->check);
	while (1)
	{
		eat_with_forks(frame, philo);
		++philo->nb_meals;
		if (philo->nb_meals == frame->setup[MEALS])
		{	
			sem_post(frame->philo_full);
			exit_clean(frame);
		}
		sleep_and_think(frame, philo);
	}
}

void	routine(t_frame *frame, t_philo *philo)
{
	sem_wait(frame->check);
	philo->last_ate = _get_time();
	sem_post(frame->check);
	while (1)
	{
		eat_with_forks(frame, philo);
		sleep_and_think(frame, philo);
	}
}
