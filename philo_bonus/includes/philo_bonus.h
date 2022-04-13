/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 14:04:21 by jlecomte          #+#    #+#             */
/*   Updated: 2022/04/06 17:46:58 by jlecomte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef INT32_MAX
#  define INT32_MAX 2147483647
# endif

/*
**	--- DEFINES FOR READABILITY ---
*/

# define WRONG_VAL "\e[48;5;124m \
Error: wrong value. Arguments must be unsigned integers.\e[m\n"
# define TOO_BIG "\e[48;5;124m \
Error: too big value. Arguments must be smaller than INTMAX.\e[m\n"
# define WRONG_SETUP "\e[48;5;124m \
Error: try [nb_philo][time_to_die][time_to_eat][time_to_sleep][nb_meals]\e[m\n"
# define NO_ZERO "\e[48;5;124m \
Error: null value. Arguments must be greater than 0.\e[m\n"

# define NB_PHILO		0
# define DIE			1
# define EAT			2
# define SLEEP			3
# define MEALS			4
# define FORK_ERR		"\e[48;5;160m\
Error: process could not be forked.\e[m\n"
# define SEM_ERR		"\e[48;5;160m\
Error: semaphore failed to open.\e[m\n"
# define MALLOC_ERR		"\e[48;5;160m\
Error: memory could not be allocated.\e[m\n"
# define PHILO_EATS		"\e[38;5;%dm%ld	Philo %d is eating\e[m\n"
# define PHILO_TAKES_FORK	"\e[38;5;%dm%ld	Philo %d has taken a fork\e[m\n"
# define PHILO_SLEEPS		"\e[38;5;%dm%ld	Philo %d is sleeping\e[m\n"
# define PHILO_THINKS		"\e[38;5;%dm%ld	Philo %d is thinking\e[m\n"
# define PHILO_DIED		"\e[38;5;%dm%ld	Philo %d died\e[m\n"
# define END_MEALS		"\e[38;5;193mAll philosophers have eaten \
%d meal(s).\e[m\n"

/*
**	--- DATA STRUCTURES ---
*/

typedef struct s_frame	t_frame;

typedef struct s_philo
{
	pid_t			pid;
	t_frame			*frame;
	long int		last_ate;
	unsigned int	id;
	int				nb_meals;
}		t_philo;

typedef struct s_frame
{
	pthread_t		check_death;
	pthread_t		check_meals;
	sem_t			*stop;
	sem_t			*forks;
	sem_t			*philo_full;
	sem_t			*print;
	t_philo			*philo;
	long int		start;
	int				setup[5];
	int				palette[36];
	int				dead;
	int				i;
	int				wait_meals;
}		t_frame;

/*
**	--- MAIN FUNCTIONS ---
*/

int			error_exit(t_frame *frame, const char *s);
int			init_data(t_frame *frame);
int			parse(int nb_args, char **args, int *setup);
void		*check_death(void *data);
void		*check_meals(void *data);
void		eat_with_forks(t_frame *frame, t_philo *philo);
void		fill_colors(int *arr, int size);
void		ft_sleep(long int ms);
void		meals_routine(t_frame *frame, t_philo *philo);
void		print_info(t_frame *frame, int id, char *msg, int dead);
void		routine(t_frame *frame, t_philo *philo);
void		sleep_and_think(t_frame *frame, t_philo *philo);
long int	_get_time(void);

/*
**	--- DEBUG ---
*/

//void		print_setup(int *setup, int size);
//void		print_philos(t_frame *frame, t_philo *philo, int nb_philo);
//void		print_frame(t_frame *frame);

#endif
