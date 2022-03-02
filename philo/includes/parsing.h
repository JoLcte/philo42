/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 13:58:30 by jlecomte          #+#    #+#             */
/*   Updated: 2022/03/02 15:22:20 by jlecomte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <unistd.h>
# include <stdio.h>

# ifndef INT32_MAX
#  define INT32_MAX 2147483647
# endif

# define WRONG_VAL "Error: wrong value. Arguments must be unsigned integers.\n"
# define TOO_BIG "Error: too big value. Arguments must be smaller than INTMAX.\n"
# define WRONG_SETUP "Error: try [nb_philo][time_to_die][time_to_eat]\
[time_to_sleep][nb_meals]\n"
# define NO_ZERO "Error: null value. Arguments must be greater than 0.\n"

int	parse(int nb_args, char **args, int *setup);

#endif
