/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 17:34:34 by jlecomte          #+#    #+#             */
/*   Updated: 2022/05/05 13:18:22 by jlecomte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static	void	mini_ft_itoa(int id, char *s)
{
	int	i;

	i = 3;
	s[i] = '\0';
	while (--i >= 0)
	{
		s[i] = id % 10 + '0';
		id /= 10;
	}
}

static int	init_philos(t_frame *frame, t_philo *philo, int nb_philo)
{
	int		i;
	char	sem_name[4];

	i = 0;
	while (i < nb_philo)
	{
		mini_ft_itoa(i + 1, sem_name);
		sem_unlink(sem_name);
		philo[i].meals_eaten = sem_open(sem_name, O_CREAT | O_EXCL, \
				0644, 0);
		if (philo[i].meals_eaten == SEM_FAILED)
			return (1);
		philo[i].frame = frame;
		philo[i].id = i + 1;
		philo[i].nb_meals = 0;
		philo[i].last_ate = _get_time();
		philo[i].pid = -1;
		++i;
	}
	return (0);
}

static int	init_sem(t_frame *frame)
{
	sem_unlink("philo_full");
	sem_unlink("forks");
	sem_unlink("stop");
	sem_unlink("print");
	sem_unlink("check");
	frame->philo_full = sem_open("philo_full", O_CREAT | O_EXCL, 0644, 1);
	frame->forks = sem_open("forks", O_CREAT | O_EXCL, 0644, \
			frame->setup[NB_PHILO]);
	frame->stop = sem_open("stop", O_CREAT | O_EXCL, 0644, 0);
	frame->print = sem_open("print", O_CREAT | O_EXCL, 0644, 1);
	frame->check = sem_open("check", O_CREAT | O_EXCL, 0644, 1);
	if (frame->philo_full == SEM_FAILED || frame->forks == SEM_FAILED
		|| frame->stop == SEM_FAILED || frame->print == SEM_FAILED
		|| frame->check == SEM_FAILED)
		return (1);
	return (0);
}

int	init_data(t_frame *frame)
{
	const int		nb_philo = frame->setup[NB_PHILO];

	frame->philo = malloc(sizeof(t_philo) * nb_philo);
	if (!frame->philo)
		return (error_exit(frame, MALLOC_ERR));
	frame->check_death = 0;
	frame->check_meals = 0;
	if (init_sem(frame) || init_philos(frame, frame->philo, nb_philo))
		return (error_exit(frame, SEM_ERR));
	fill_colors(frame->palette, 36);
	frame->start = 0;
	frame->dead = 0;
	frame->wait_meals = 0;
	return (0);
}
