/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 19:18:49 by rha-le            #+#    #+#             */
/*   Updated: 2025/04/28 20:39:26 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "util.h"

static int	init_forks(t_table *table)
{
	t_mutex			*fork;
	unsigned int	i;

	table->fork = malloc(sizeof(*fork) * (table->philo_count + 1));
	fork = table->fork;
	if (!fork)
		return (1);
	memset(fork, 0, sizeof(*fork) * (table->philo_count + 1));
	i = 0;
	while (i < table->philo_count)
	{
		if (pthread_mutex_init(&fork[i++], NULL) != 0)
		{
			destroy_mutex(fork);
			printf("fork init error!\n"); // NOTE: delete after !
			return (2); // destroy at error
		}
	}
	return (0);
}

static int	init_philos(t_table *table)
{
	t_philo			*philo;
	unsigned int	i;

	table->philo = malloc(sizeof(*philo) * table->philo_count);
	philo = table->philo;
	if (!philo)
		return (1);
	memset(philo, 0, sizeof(*philo) * table->philo_count);
	i = 0;
	while (i < table->philo_count)
	{
		philo[i].id = (int)i + 1;
		philo[i].time = &table->time;
		philo[i].table = table;
		philo[i].right_fork = &table->fork[i];
		philo[i].left_fork = &table->fork[(i + 1) % table->philo_count];
		++i;
	}
	return (0);
}

int init_table(t_table *table)
{
	if (pthread_mutex_init(&table->print, NULL) != 0)
		return (1);
	if (init_forks(table) != 0)
		return (2);
	if (init_philos(table) != 0)
		return (3);
	return (0);
}

