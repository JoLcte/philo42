/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:56:34 by jlecomte          #+#    #+#             */
/*   Updated: 2022/03/02 19:49:49 by jlecomte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*routine(void	*data)
{
	const t_frame *frame = (t_frame *)data;
	const t_philo *philo = &philo[frame->i];
//	int	stop;
	
//	stop = (philo->is_dead || philo->nb_meals == frame->setup[MEALS]);
	frame->start = _get_time();
	philo->last_ate = frame->start;
	while (1)
	{
		if (eat_with_forks(frame))
			return (philo_thread[frame->i]);
		sleep_and_think(frame);
	}
	return (NULL);
}

/* Is returning the dead thread a good idea ?*/
void	thread_actions(t_frame *frame)
{
	const int	nb_philo = frame->setup[NB_PHILO];
	pthread_t	dead_thread;
	int	i;

	i = 0;
	while (i < nb_philo)
	{
		frame->i = i;
		dead_thread = pthread_create(&frame->philo_thread[i], NULL, \
			 routine, (void *)frame);
		++i;
	}
}
