/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlecomte <jlecomte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 17:08:15 by jlecomte          #+#    #+#             */
/*   Updated: 2022/03/03 17:45:28 by jlecomte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	_get_time()
{
	long int	now;
	struct timeval time;

	gettimeofday(&time, NULL);
	now = time.tv_sec * 1000 + time.tv_usec * 0.001;
	return (now);
}
