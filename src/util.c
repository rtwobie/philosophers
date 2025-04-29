/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:23:20 by rha-le            #+#    #+#             */
/*   Updated: 2025/04/28 20:40:31 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include <pthread.h>
#include <stdint.h>
#include <stdlib.h>

unsigned int	atoui(const char *nptr)
{
	int		num;

	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		++nptr;
	if (*nptr == '-')
		return (0);
	if (*nptr == '+' || *nptr == '-')
		++nptr;
	num = 0;
	while (*nptr >= '0' && *nptr <= '9')
	{
		num = (num * 10) + (*nptr - '0');
		++nptr;
	}
	return ((unsigned)num);
}

uint64_t	atoui64(const char *nptr)
{
	int64_t	num;

	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		++nptr;
	if (*nptr == '-')
		return (0);
	if (*nptr == '+' || *nptr == '-')
		++nptr;
	num = 0;
	while (*nptr >= '0' && *nptr <= '9')
	{
		num = (num * 10) + (*nptr - '0');
		++nptr;
	}
	return ((uint64_t)num);
}

void	destroy_mutex(t_mutex *mutex)
{
	while (mutex)
		pthread_mutex_destroy(mutex++);
}

void	free_all(t_table *table)
{
	if (table->fork)
	{
		destroy_mutex(table->fork);
		free(table->fork);
	}
	if (table->philo)
		free(table->philo);
}
