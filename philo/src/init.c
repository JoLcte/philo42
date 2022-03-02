/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 17:34:34 by jlecomte          #+#    #+#             */
/*   Updated: 2022/03/02 19:30:32 by jlecomte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_first_philo(t_frame *frame, t_philo *philos, int nb_philo)
{
	philo[0].id = 1;
	philo[0].nb_meals = 0;
	philo[0].is_dead = 0;
	philo[0].last_ate = 0;
	philo[0].l_fork = &frame->forks[i];
	if (nb_philo == 1)
	{
		philo[0].r_fork = NULL;
		return (1);
	}
	philo[0].r_fork = &frame->forks[1];
	return (0);
}

static void	init_philos(t_frame *frame, t_philo *philos, int nb_philo)
{
	int	i;
	
	i = 0;
	if (init_first_philo(frame, philos, nb_philo))
		return ;
	while (++i < nb_philo - 1)
	{
		philo[i].id = i + 1;
		philo[i].nb_meals = 0;
		philo[i].is_dead = 0;
		philo[i].last_ate = 0;
		philo[i].l_fork = &frame->forks[i];
		philo[i].r_fork = &frame->forks[i + 1];
	}
	philo[i].id = i + 1;
	philo[i].nb_meals = 0;
	philo[i].is_dead = 0;
	philo[i].last_ate = 0;
	philo[i].l_fork = &frame->forks[i];
	philo[i].r_fork = &frame->forks[0];
}

int	init_data(t_frame *frame)
{
	int			i;
	const int		nb_philo = frame->setup[NB_PHILO];
	const pthread_mutex_t	*forks = frame->forks;
	
	i = 0;
	frame->philo_thread = malloc(sizeof(pthread_t) * nb_philo);
	if (!frame->philo_thread)
		return (error_exit(frame, MALLOC_ERR));
	frame->forks = malloc(sizeof(pthread_mutex_t) * nb_philo);
	if (!frame->forks)
		return (error_exit(frame, MALLOC_ERR));
	frame->philo = malloc(sizeof(t_philo) * nb_philo);
	if (!frame->philo_thread)
		return (error_exit(frame, MALLOC_ERR));
	if (!pthread_mutex_init(frame->print, NULL))
		return (error_exit(frame, MUTEX_ERR));
	while (i < nb_philo)
	{
		if (!pthread_mutex_init(forks[i], NULL))
			return (error_exit(frame, MUTEX_ERR));
		++i;
	}
	frame->i = 0;
	init_philos(frame, &frame->philo, nb_philo);
	return (0);
}
