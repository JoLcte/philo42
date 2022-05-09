/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 13:14:46 by jlecomte          #+#    #+#             */
/*   Updated: 2022/05/05 13:21:55 by jlecomte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static	int	ft_itoa(long int n, char *s)
{
	long int	n_save;
	int			ret;
	int			i;

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
}

static void	add_buff(char *s, int size, int print, char *buff)
{
	static int	idx_save;
	int			i;

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
}

static void	fill_buff(t_frame *frame, int id)
{
	const int	color = frame->palette[id % 36];
	long int	now;
	char		nb[11];
	int			ret;

	sem_wait(frame->print);
	now = _get_time();
	add_buff("\e[38;5;45m", 10, 0, frame->buff);
	ret = ft_itoa(now - frame->start, nb);
	add_buff(nb, ret, 0, frame->buff);
	add_buff("\t\e[38;5;", 8, 0, frame->buff);
	ret = ft_itoa(color, nb);
	add_buff(nb, ret, 0, frame->buff);
	add_buff("mPhilo ", 7, 0, frame->buff);
	ret = ft_itoa(id, nb);
	add_buff(nb, ret, 0, frame->buff);
}

void	print_info(t_frame *frame, int id, int msg)
{
	fill_buff(frame, id);
	if (msg == EATS)
		add_buff(" is eating\e[m\n", 14, 1, frame->buff);
	else if (msg == FORK)
		add_buff(" has taken a fork\e[m\n", 21, 1, frame->buff);
	else if (msg == SLEEPS)
		add_buff(" is sleeping\e[m\n", 16, 1, frame->buff);
	else if (msg == THINKS)
		add_buff(" is thinking\e[m\n", 16, 1, frame->buff);
	else if (msg == DIED)
	{
		add_buff(" died\e[m\n", 9, 1, frame->buff);
		return ;
	}
	sem_post(frame->print);
}
