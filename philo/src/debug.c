/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 15:08:05 by jlecomte          #+#    #+#             */
/*   Updated: 2022/03/02 15:14:38 by jlecomte         ###   ########.fr       */
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
