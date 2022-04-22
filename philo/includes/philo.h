/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 14:04:21 by jlecomte          #+#    #+#             */
/*   Updated: 2022/04/22 16:04:15 by jlecomte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
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
# define MUTEX_ERR		"\e[48;5;160m\
Error: mutex could not be initilized\e[m\n"
# define MALLOC_ERR		"\e[48;5;160m\
Error: memory could not be allocated\n"
# define PHILO_EATS		"\e[38;5;%dm%ld	Philo %d is eating\e[m\n"
# define PHILO_DIED		"\e[38;5;%dm%ld	Philo %d died\e[m\n"
# define PHILO_SLEEPS		"\e[38;5;%dm%ld	Philo %d is sleeping\e[m\n"
# define PHILO_TAKES_FORK	"\e[38;5;%dm%ld	Philo %d has taken a fork\e[m\n"
# define PHILO_THINKS		"\e[38;5;%dm%ld	Philo %d is thinking\e[m\n"
# define END_MEALS		"\e[38;5;193mAll philosophers have eaten \
at least %d meal(s).\e[m\n"

/*
**	--- DATA STRUCTURES ---
*/

typedef struct s_frame	t_frame;

typedef struct s_philo
{
	pthread_t		thd;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	t_frame			*frame;
	long int		last_ate;
	unsigned int	id;
	int				nb_meals;
}		t_philo;

typedef struct s_frame
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	*lock;
	t_philo			*philo;
	long int		start;
	int				setup[5];
	int				palette[36];
	int				philos_full;
	int				stop;
}		t_frame;

/*
**	--- MAIN FUNCTIONS ---
*/

int			error_exit(t_frame *frame, const char *s);
int			init_data(t_frame *frame);
int			parse(int nb_args, char **args, int *setup);
void		eat_with_forks(t_frame *frame, t_philo *philo);
void		fill_colors(int *arr, int size);
void		ft_sleep(long int ms);
int			print_info(t_frame *frame, int id, char *msg, int dead);
void		sleep_and_think(t_frame *frame, t_philo *philo);
void		thread_actions(t_frame *frame);
long int	_get_time(void);

/*
**	--- DEBUG ---
*/

void		print_forks(t_frame *frame, const char *s, int n, \
			pthread_mutex_t *fork);
void		print_frame(t_frame *frame);
void		print_philos(t_frame *frame, t_philo *philo, int nb_philo);
void		print_setup(int *setup, int size);

#endif
