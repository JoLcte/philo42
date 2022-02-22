/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 17:23:12 by jlecomte          #+#    #+#             */
/*   Updated: 2022/02/17 18:16:00 by jlecomte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parsing.h"
#include "philo.h"

int	main(int ac, char **av)
{
	int	setup[5];

	if (parse(ac - 1, av + 1, setup))
		return (1);
	printf("Parsing : SUCCESS\n");
	return (0);
}
