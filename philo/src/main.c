/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 17:23:12 by jlecomte          #+#    #+#             */
/*   Updated: 2022/03/08 15:27:53 by jlecomte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parsing.h"
#include "philo.h"


int	main(int ac, char **av)
{
	t_frame	frame;

	if (parse(ac - 1, av + 1, frame.setup))
		return (1);
//	print_setup(frame.setup, 5);
	if (init_data(&frame))
		return (1);
//	print_philos(&frame, frame.philo, frame.setup[NB_PHILO]);
//	print_frame(&frame);
//	print_colors(&frame);
	thread_actions(&frame);
	int i = 0;
	while (i < frame.setup[NB_PHILO])
	{
		pthread_join(frame.philo_thread[i], NULL);
		++i;
	}
//	send threads in functions
//	check somewhere when to stop
//	destroy everything
	return (0);
}
