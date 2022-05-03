/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 17:23:12 by jlecomte          #+#    #+#             */
/*   Updated: 2022/05/03 21:09:19 by jlecomte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	clean_all(t_frame *frame)
{
	int	i;
	int	status;

	status = 0;
	i = -1;
	sem_wait(frame->check);
	frame->dead = 1;
	sem_post(frame->check);
	if (frame->wait_meals)
	{
		while (++i < frame->setup[NB_PHILO])
			waitpid(-1, &status, WUNTRACED);
		printf(END_MEALS, frame->setup[MEALS]);
	}
	else
	{
		while (++i < frame->setup[NB_PHILO])
			kill(frame->philo[i].pid, SIGKILL);
	}	
	usleep(10000);
	free(frame->philo);
	sem_close(frame->forks);
	sem_close(frame->stop);
	sem_close(frame->print);
	sem_close(frame->philo_full);
	sem_close(frame->check);
}

static int	fork_err(t_frame *frame, int i)
{
	if (frame->philo[i].pid == -1)
	{
		printf(FORK_ERR);
		while (i--)
			kill(frame->philo[i].pid, SIGKILL);
		return (1);
	}
	return (0);
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

	if (parse(ac - 1, av + 1, frame.setup))
		return (1);
	if (init_data(&frame))
		return (1);
	if (frame.setup[MEALS] > 0)
		launch_meals_routine(&frame);
	else
		launch_routine(&frame);
	clean_all(&frame);
	sem_unlink("forks");
	sem_unlink("stop");
	sem_unlink("print");
	sem_unlink("check");
	sem_unlink("philo_full");
	return (0);
}
