/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 17:08:15 by jlecomte          #+#    #+#             */
/*   Updated: 2022/05/03 21:07:26 by jlecomte         ###   ########.fr       */
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

/*static	int	ft_itoa(long int n, char *s)
{
	long int	n_save;
	int		ret;
	int		i;

	if (!n)
	{
		s[0] = '0';
		s[1] = '\0';
		return (1);
	}
	i = 0;
	n_save = n;
	while (n)
	{
		n /= 10;
		++i;
	}
	ret = i;
	s[i] = '\0';
	while (--i >= 0)
	{
		s[i] = n_save % 10 + '0';
		n_save /= 10;
	}
	return (ret);
}*/

/*void	add_buff(char *s, int size, int print)
{
	char buff[64];
	static int	idx_save;
	int		i;
	
	i = 0;
	while (i < size)
	{
		buff[idx_save + i] = s[i];
		++i;
	}
	idx_save += size;
	if (print)
	{
		buff[idx_save] = '\0';
		write(1, buff, idx_save);
		idx_save = 0;
	}
}*/

void	print_info(t_frame *frame, int id, char *msg, int dead)
{
	const unsigned int	color = frame->palette[id % 36];
	//char			s[11];
	long int			now;
	//int			ret;

	sem_wait(frame->print);
	now = _get_time();
	/*add_buff("\e[38;5;45m", 10, 0);
	ret = ft_itoa(now - frame->start, s);
	add_buff(s, ret, 0);
	add_buff("\t", 1, 0);
	add_buff("Philo ", 6, 0);
	ret = ft_itoa(id, s);
	add_buff(s, ret, 0);
	if (msg == EATS)
		add_buff(" is eating\e[m\n", 14, 1);
	else if (msg == FORK)
		add_buff(" has taken a fork\e[m\n", 21, 1);
	else if (msg == SLEEPS)
		add_buff(" is sleeping\e[m\n", 16, 1);
	else if (msg == THINKS)
		add_buff(" is thinking\e[m\n", 16, 1);
	else if (msg == DIED)
		add_buff(" died\e[m\n", 9, 1);*/
	printf(msg, color, now - frame->start, id); 
	if (dead)
		return ;
	else
		sem_post(frame->print);
}

void	ft_sleep(long int ms)
{
	long int	now;

	now = _get_time();
	while (_get_time() < now + ms)
		usleep(ms);
}
