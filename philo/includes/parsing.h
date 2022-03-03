/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 13:58:30 by jlecomte          #+#    #+#             */
/*   Updated: 2022/03/03 18:27:54 by jlecomte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <unistd.h>
# include <stdio.h>

# ifndef INT32_MAX
#  define INT32_MAX 2147483647
# endif

# define WRONG_VAL "\e[48;5;124m \
Error: wrong value. Arguments must be unsigned integers.\e[m\n"
# define TOO_BIG "\e[48;5;124m \
Error: too big value. Arguments must be smaller than INTMAX.\e[m\n"
# define WRONG_SETUP "\e[48;5;124m \
Error: try [nb_philo][time_to_die][time_to_eat][time_to_sleep][nb_meals]\e[m\n"
# define NO_ZERO "\e[48;5;124m \
Error: null value. Arguments must be greater than 0.\e[m\n"

int	parse(int nb_args, char **args, int *setup);

#endif
