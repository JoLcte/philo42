/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 17:08:15 by jlecomte          #+#    #+#             */
/*   Updated: 2022/04/05 15:12:08 by jlecomte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	error_exit(t_frame *frame, const char *s)
{
	printf("%s", s);
	if (frame->philo)
		free(frame->philo);
	if (frame->philo_full)
		sem_close(frame->philo_full);
	if (frame->stop)
		sem_close(frame->philo_full);
	if (frame->forks)
		sem_close(frame->forks);
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

void	print_info(t_frame *frame, int id, char *msg, int dead)
{
	const unsigned int	color = frame->palette[id % 36];
	long int			now;

	sem_wait(frame->print);
	now = _get_time();
	printf(msg, color, now - frame->start, id);
	if (!dead)
		sem_post(frame->print);
}

void    ft_sleep(t_frame *frame, long int ms)
{
	long int	now;
	long int	time_wtf;

	time_wtf = (long int)(1000 * frame->setup[NB_PHILO] * 0.005);
	if ( time_wtf > 5000)
		time_wtf = 5000;

	now = _get_time();
	while (_get_time() < now + ms)
		usleep(time_wtf);
}
