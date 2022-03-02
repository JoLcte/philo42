/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 17:31:36 by jlecomte          #+#    #+#             */
/*   Updated: 2022/02/24 16:26:21 by jlecomte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	print_error(char const *msg, int size)
{
	write(2, msg, size);
	return (-1);
}

static int	fake_atoui(char const *str)
{
	long long		n;
	unsigned char	c;

	n = 0;
	while (*str == ' ' || (unsigned)*str - '\t' < 5)
		++str;
	if (*str == '-')
		return (print_error(WRONG_VAL, 56));
	str += (*str == '+');
	while (*str)
	{
		c = (unsigned)*str++ - '0';
		if (c > 9)
			return (print_error(WRONG_VAL, 56));
		if (n > INT32_MAX)
			return (print_error(TOO_BIG, 59));
		n = (n << 1) + (n << 3) + c;
	}
	if (!n)
		return (print_error(NO_ZERO, 53)); 
	return ((int)n);
}

static int	get_setup(int *setup, char **args)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		setup[i] = fake_atoui(args[i]);
		if (setup[i] <= 0)
			return (1);
		++i;
	}
	if (args[i])
	{
		setup[i] = fake_atoui(args[i]);
		if (setup[i] <= 0)
			return (1);
	}
	else
		setup[i] = -1;
	return (0);
}

int	parse(int nb_args, char **args, int *setup)
{
	if (nb_args < 4 || nb_args > 5)
		return (print_error(WRONG_SETUP, 64));
	if (get_setup(setup, args))
		return (1);
	return (0);
}