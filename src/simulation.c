/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 19:14:57 by rha-le            #+#    #+#             */
/*   Updated: 2025/05/01 00:49:13 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "structs.h"
#include "routine.h"
#include "cleanup.h"

static int _set_in_sync(t_table *table)
{
	if (pthread_mutex_lock(&table->in_sync_mutex))
		return (EXIT_FAILURE);
	table->in_sync = true;
	if (pthread_mutex_unlock(&table->in_sync_mutex))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	_spawn_philo(t_philo *philo, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (pthread_create(&philo[i].thread, NULL, routine, &philo[i]))
		{
			destroy_forks(philo->table->fork, count);
			free(philo);
			return (EXIT_FAILURE);
		}
		++i;
	}
	return (EXIT_SUCCESS);
}

#include <stdio.h>
int	simulation(t_philo *philo, t_table *table)
{
	for (int i = 0; i < table->philo_count; i++)
		printf("%i has fork %i and %i\n", philo[i].id, philo[i].right_fork->id, philo[i].left_fork->id);
	if (_spawn_philo(philo, table->philo_count))
		return (EXIT_FAILURE);
	philo->table->start_time = get_time();
	if (_set_in_sync(philo->table))
		return (EXIT_FAILURE);
	for (int i = 0; i < table->philo_count; i++)
		pthread_join(philo[i].thread, NULL);
	at_exit(philo, table);
	// TODO:
	// wait for all threads to be created;
	// start simulation;
	// cleanup;
	return (EXIT_SUCCESS);
}
