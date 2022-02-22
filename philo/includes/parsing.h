/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 13:58:30 by jlecomte          #+#    #+#             */
/*   Updated: 2022/02/17 18:02:07 by jlecomte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <unistd.h>
# include <stdio.h>
//BAD COMMENT TO ERASE STDIO

# ifndef INT32_MAX
#  define INT32_MAX 2147483647
# endif

# define WRONG_VAL "Error: wrong value. Arguments must be positive numbers.\n"
# define TOO_BIG "Error: too big value. Arguments must be lower than INTMAX.\n"
# define WRONG_SETUP "Error: try [nb_philo][die_time][eat_time][sleep_time]\
[nb_meals]\n"

int	parse(int nb_args, char **args, int *setup);

#endif
