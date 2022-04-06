/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 17:23:12 by jlecomte          #+#    #+#             */
/*   Updated: 2022/03/17 10:13:14 by jlecomte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "philo.h"

static void	clean_all(t_frame *frame)
{
	int	i;

	i = 0;
	while (i < frame->setup[NB_PHILO])
	{
		pthread_join(frame->philo[i].thd, NULL);
		++i;
	}
	if (frame->philos_full == frame->setup[NB_PHILO])
		printf(END_MEALS, frame->setup[MEALS]);
	i = 0;
	while (i < frame->setup[NB_PHILO])
	{
		if (pthread_mutex_destroy(&frame->forks[i]))
			printf("couldn't destroy forks[%d]\n", i);
		++i;
	}
	pthread_mutex_destroy(frame->print);
	pthread_mutex_destroy(frame->dead);
	free(frame->print);
	free(frame->dead);
	free(frame->philo);
	free(frame->forks);
}

int	main(int ac, char **av)
{
	t_frame	frame;

	if (parse(ac - 1, av + 1, frame.setup))
		return (1);
	if (init_data(&frame))
		return (1);
	thread_actions(&frame);
	clean_all(&frame);
	return (0);
}
