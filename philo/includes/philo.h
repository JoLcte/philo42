/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 14:04:21 by jlecomte          #+#    #+#             */
/*   Updated: 2022/03/02 19:19:49 by jlecomte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>

/*
**	--- DEFINES FOR READABILITY ---
*/

# define NB_PHILO	0
# define DIE		1
# define EAT		2
# define SLEEP		3
# define MEALS		4
# define MUTEX_ERR	"Error: mutex could not be initilized\n"
# define MALLOC_ERR	"Error: memory could not be allocated\n"

/*
**	--- DATA STRUCTURES ---
*/

typedef struct	s_philo
{
	pthread_mutex_t *l_fork;
	pthread_mutex_t	*r_fork;
	time_t		last_ate;
	unsigned int	id;
	unsigned int	nb_meals;
	char		is_dead;
}		t_philo;

typedef struct	s_frame
{
	pthread_mutex_t	*print;
	pthread_t	*philo_thread;
	pthread_mutex_t	*forks;
	t_philo		*philo;
	time_t		start;
	int		setup[5];
	int		i;
}		t_frame;

/*
**	--- INIT FUNCTIONS ---
*/

int	init_data(t_frame *frame);

/*
**	--- DEBUG ---
*/

void	print_setup(int *setup, int size);


#endif
