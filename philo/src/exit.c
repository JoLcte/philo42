/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:43:27 by jlecomte          #+#    #+#             */
/*   Updated: 2022/03/03 18:36:41 by jlecomte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_exit(t_frame *frame, const char *s)
{
	int	i;
	
	i = 0;
	printf("%s", s);
	if (frame->forks)
	{
		while (i < frame->setup[NB_PHILO])
			pthread_mutex_destroy(&frame->forks[i++]);
		free(frame->forks);
	}
	if (frame->philo_thread)
		free(frame->philo_thread);
	if (frame->philo)
		free(frame->philo);
	return (1);
}
