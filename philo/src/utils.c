/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 17:08:15 by jlecomte          #+#    #+#             */
/*   Updated: 2022/04/22 16:04:47 by jlecomte         ###   ########.fr       */
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
	if (frame->philo)
		free(frame->philo);
	return (1);
}

long int	_get_time(void)
{
	long int		now;
	struct timeval	time;

	gettimeofday(&time, NULL);
	now = time.tv_sec * 1000 + time.tv_usec * 0.001;
	return (now);
}

void	fill_colors(int *arr, int size)
{
	int	i;
	int	start;
	int	j;

	if (size != 36)
	{
		printf("Colors array could not be filled\n");
		return ;
	}
	i = -1;
	j = 0;
	start = 34;
	while (j < 6)
	{
		i = -1;
		while (++i < 6)
			arr[i] = start + i;
		++j;
		start += 36;
		arr += i;
	}
}

int	print_info(t_frame *frame, int id, char *msg, int dead)
{
	const unsigned int	color = frame->palette[id % 36];
	long int			now;

	if (frame->stop)
	{
		pthread_mutex_unlock(frame->lock);
		return (1);
	}
	now = _get_time();
	printf(msg, color, now - frame->start, id);
	if (!dead)
		pthread_mutex_unlock(frame->lock);
	return (0);
}

void	ft_sleep(long int ms)
{
	long int	now;

	now = _get_time();
	while (_get_time() < now + ms)
		usleep(ms);
}
