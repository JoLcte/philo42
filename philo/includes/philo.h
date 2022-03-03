/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 14:04:21 by jlecomte          #+#    #+#             */
/*   Updated: 2022/03/03 18:28:51 by jlecomte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

/*
**	--- DEFINES FOR READABILITY ---
*/

# define NB_PHILO		0
# define DIE			1
# define EAT			2
# define SLEEP			3
# define MEALS			4
# define MUTEX_ERR		"\e[48;5;160m\
Error: mutex could not be initilized\e[m\n"
# define MALLOC_ERR		"\e[48;5;160m\
Error: memory could not be allocated\n"
# define PHILO_EATS		"\e[38;5;%dm%ld	Philo %d is eating\e[m\n"
# define PHILO_TAKES_FORK	"\e[38;5;%dm%ld	Philo %d has taken a fork\e[m\n"
# define PHILO_SLEEPS		"\e[38;5;%dm%ld	Philo %d is sleeping\e[m\n"
# define PHILO_THINKS		"\e[38;5;%dm%ld	Philo %d is thinking\e[m\n"
# define PHILO_DIED		"\e[38;5;%dm%ld	Philo %d died\e[m\n"

/*
**	--- DATA STRUCTURES ---
*/

typedef struct	s_philo
{
	pthread_mutex_t *l_fork;
	pthread_mutex_t	*r_fork;
	time_t		last_ate;
	unsigned int	id;
	int	nb_meals;
}		t_philo;

typedef struct	s_frame
{
	pthread_mutex_t	*print;
	pthread_t	*philo_thread;
	pthread_mutex_t	*forks;
	t_philo		*philo;
	time_t		start;
	int		setup[5];
	int		palette[36];
	int		i;
	char		stop;
}		t_frame;

/*
**	--- MAIN FUNCTIONS ---
*/

int	init_data(t_frame *frame);
void	thread_actions(t_frame *frame);
void	eat_with_forks(t_frame *frame, t_philo *philo);
void	sleep_and_think(t_frame *frame, t_philo *philo);
long int	_get_time();

/*
**	--- CLEANUP ---
*/

int	error_exit(t_frame *frame, const char *s);

/*
**	--- DEBUG ---
*/

void	print_setup(int *setup, int size);


#endif
