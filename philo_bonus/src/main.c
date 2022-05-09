/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 17:23:12 by jlecomte          #+#    #+#             */
/*   Updated: 2022/05/05 14:19:13 by jlecomte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	stop_process(t_frame *frame)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	if (frame->wait_meals)
	{
		while (++i < frame->setup[NB_PHILO])
			waitpid(-1, &j, WUNTRACED);
		printf(END_MEALS, frame->setup[MEALS]);
	}
	else
	{
		if (frame->setup[MEALS] > 0)
		{
			while (j < frame->setup[NB_PHILO])
				sem_post(frame->philo[j++].meals_eaten);
		}
		while (++i < frame->setup[NB_PHILO])
			kill(frame->philo[i].pid, SIGKILL);
	}	
}

static void	clean_stop(t_frame *frame)
{
	int	i;

	sem_wait(frame->check);
	frame->dead = 1;
	sem_post(frame->check);
	usleep(1000);
	stop_process(frame);
	usleep(10000);
	i = 0;
	while (i < frame->setup[NB_PHILO])
	{
		sem_close(frame->philo[i].meals_eaten);
		++i;
	}
	free(frame->philo);
	sem_close(frame->forks);
	sem_close(frame->stop);
	sem_close(frame->print);
	sem_close(frame->philo_full);
	sem_close(frame->check);
}

static void	launch_meals_routine(t_frame *frame)
{
	int	i;	

	i = -1;
	frame->start = _get_time();
	pthread_create(&frame->check_meals, NULL, check_meals, (void *)frame);
	pthread_detach(frame->check_meals);
	while (++i < frame->setup[NB_PHILO])
	{
		frame->i = i;
		frame->philo[i].pid = fork();
		if (fork_err(frame, i))
			return ;
		if (frame->philo[i].pid == 0)
		{
			frame->philo[i].last_ate = _get_time();
			if (frame->philo[i].id % 2 == 0)
				ft_sleep(frame->setup[EAT] / 2);
			pthread_create(&frame->check_death, NULL, \
					check_death, (void *)&frame->philo[i]);
			pthread_detach(frame->check_death);
			meals_routine(frame, &frame->philo[i]);
		}
	}
	sem_wait(frame->stop);
}

static void	launch_routine(t_frame *frame)
{
	const int	nb_philo = frame->setup[NB_PHILO];
	int			i;

	i = 0;
	frame->start = _get_time();
	while (i < nb_philo)
	{
		frame->i = i;
		frame->philo[i].pid = fork();
		if (fork_err(frame, i))
			return ;
		if (frame->philo[i].pid == 0)
		{
			frame->philo[i].last_ate = _get_time();
			if (frame->philo[i].id % 2 == 0)
				ft_sleep(frame->setup[EAT] / 2);
			pthread_create(&frame->check_death, NULL, \
					check_death, (void *)&frame->philo[i]);
			pthread_detach(frame->check_death);
			routine(frame, &frame->philo[i]);
		}
		++i;
	}
	sem_wait(frame->stop);
}

int	main(int ac, char **av)
{
	t_frame	frame;
	char	buff[64];

	if (parse(ac - 1, av + 1, frame.setup))
		return (1);
	if (init_data(&frame))
		return (1);
	memset(buff, 0, 64);
	frame.buff = buff;
	if (frame.setup[MEALS] > 0)
		launch_meals_routine(&frame);
	else
		launch_routine(&frame);
	clean_stop(&frame);
	return (0);
}
