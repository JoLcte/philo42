/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 15:08:05 by jlecomte          #+#    #+#             */
/*   Updated: 2022/03/08 15:23:25 by jlecomte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "philo.h"

void	print_setup(int	*setup, int size)
{
	int	i;

	i = 0;
	printf("-----	PARSING SETUP	-------\n");
	while (i < size)
	{
		printf("setup[%d] = %d\n", i , setup[i]);
		++i;
	}
	printf("-----	PARSING SUCCESS	-------\n\n");
}

void	print_philos(t_frame *frame, t_philo *philo, int nb_philo)
{
	int i;
	
	i = 0;
	printf("-----   PHILOS CHECK   ------\n\n");
	while (i < nb_philo - 1)
	{
		printf("--- Philo %d ---\n", philo[i].id);
		printf("-> left_fork OK ? %d\n", (philo[i].l_fork == &frame->forks[i]));
		printf("-> right_fork OK ? %d\n", (philo[i].r_fork == &frame->forks[i + 1]));
		printf("->nb_meals = %d\n", philo[i].nb_meals);
		printf("->nb_meals = %d\n", philo[i].nb_meals);
		printf("	- - -		\n");
		++i;
	}
	printf("--- Philo %d ---\n", philo[i].id);
	printf("-> left_fork OK ? %d\n", (philo[i].l_fork == &frame->forks[0]));
	printf("-> right_fork OK ? %d\n", (philo[i].r_fork == &frame->forks[i]));
	printf("->nb_meals = %d\n", philo[i].nb_meals);
	printf("->nb_meals = %d\n", philo[i].nb_meals);
	
	printf("-----   PHILOS COMPLETED   ------\n\n");
}

void	print_frame(t_frame *frame)
{
	printf("-----   FRAME CHECK   ------\n\n");
	/*int i = 0;
	t_philo *philo = frame->philo;
	pthread_mutex_t *forks = frame->forks;
	while (philo[i])
		i++;
	printf("->Frame->Philo last : philo[%d]\n", i);
	i = 0;
	while (forks[i])
		i++;
	printf("->Frame->forks last : forks[%d]\n", i);*/
	printf("->start time = %ld\n", frame->start);
	printf("-----   FRAME COMPLETED   ------\n\n");
}

void	print_colors(t_frame *frame)
{
	int i;

	i = 0;
	printf("----   PRINT PALETTE   ----\n");
	printf("Colors = [%d]", frame->palette[i]);
	while (++i < 35)
		printf("[%d]", frame->palette[i]);
	printf("[%d]\n", frame->palette[i]);
	printf("----   COLORS PALETTE OK   ----\n\n");
}
