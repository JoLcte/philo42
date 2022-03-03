/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 17:23:12 by jlecomte          #+#    #+#             */
/*   Updated: 2022/03/03 18:30:23 by jlecomte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parsing.h"
#include "philo.h"


int	main(int ac, char **av)
{
	t_frame	frame;

	if (parse(ac - 1, av + 1, frame.setup))
		return (1);
	print_setup(frame.setup, 5);
	if (init_data(&frame))
		return (1);
	//thread_actions(&frame);
//	send threads in functions
//	check somewhere when to stop
//	destroy everything
	return (0);
}
