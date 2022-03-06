/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 17:34:34 by jlecomte          #+#    #+#             */
/*   Updated: 2022/03/04 18:42:54 by jlecomte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	fill_colors(int *arr, int size)
{
        int i;
        int start;
        int j;

        if (size < 36)
                printf("Colors array could not be filled\n");
        i = -1;
        j = 0;
        start = 34;
        while (j < 6)
        {
                start += j;
                while (++i < 6)
                        arr[i] = start + i;
                ++j;
        }
}

static int	init_first_philo(t_frame *frame, t_philo *philo, int nb_philo)
{
	philo[0].id = 1;
	philo[0].nb_meals = 0;
	philo[0].last_ate = 0;
	philo[0].l_fork = &frame->forks[0];
	if (nb_philo == 1)
	{
		philo[0].r_fork = NULL;
		return (1);
	}
	philo[0].r_fork = &frame->forks[1];
	return (0);
}

static void	init_philos(t_frame *frame, t_philo *philo, int nb_philo)
{
	int	i;
	
	i = 0;
	if (init_first_philo(frame, philo, nb_philo))
		return ;
	while (++i < nb_philo - 1)
	{
		philo[i].id = i + 1;
		philo[i].nb_meals = 0;
		philo[i].last_ate = 0;
		philo[i].l_fork = &frame->forks[i];
		philo[i].r_fork = &frame->forks[i + 1];
	}
	philo[i].id = i + 1;
	philo[i].nb_meals = 0;
	philo[i].last_ate = 0;
	philo[i].l_fork = &frame->forks[0];
	philo[i].r_fork = &frame->forks[i];
}

static int	init_mutex(t_frame *frame)
{
	const int	nb_philo = frame->setup[NB_PHILO];
	int			i;

	frame->mutex_i = malloc(sizeof(pthread_mutex_t));
	if (!frame->mutex_i)
		return (error_exit(frame, MALLOC_ERR));
	frame->print = malloc(sizeof(pthread_mutex_t));
	if (!frame->print)
		return (error_exit(frame, MALLOC_ERR));
	frame->forks = malloc(sizeof(pthread_mutex_t) * nb_philo);
	if (!frame->forks)
		return (error_exit(frame, MALLOC_ERR));
	if (pthread_mutex_init(frame->print, NULL))
		return (error_exit(frame, MUTEX_ERR));
	i = 0;
	while (i < nb_philo)
	{
		if (pthread_mutex_init(&frame->forks[i], NULL))
			return (error_exit(frame, MUTEX_ERR));
		++i;
	}
	return (0);
}

int	init_data(t_frame *frame)
{
	const int		nb_philo = frame->setup[NB_PHILO];
	
	printf("nb_philo ds init_data = %d\n", nb_philo);
	frame->philo_thread = malloc(sizeof(pthread_t) * nb_philo);
	if (!frame->philo_thread)
		return (error_exit(frame, MALLOC_ERR));
	frame->philo = malloc(sizeof(t_philo) * nb_philo);
	if (!frame->philo)
		return (error_exit(frame, MALLOC_ERR));
	if (init_mutex(frame))
		return (1);
	frame->i = 0;
	frame->start = 0;
	frame->stop = 0;
	fill_colors(frame->palette, 36);
	init_philos(frame, frame->philo, nb_philo);
	return (0);
}
