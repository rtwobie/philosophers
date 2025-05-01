/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 19:14:57 by rha-le            #+#    #+#             */
/*   Updated: 2025/05/01 17:24:28 by rha-le           ###   ########.fr       */
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

static int	_spawn_philos(t_philo *philos, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (pthread_create(&philos[i].thread, NULL, philo_routine, &philos[i]))
		{
			// WARN: propably reduntant due to at_exit() in simulation()
			destroy_forks(philos->table->fork, count);
			free(philos);
			return (EXIT_FAILURE);
		}
		++i;
	}
	return (EXIT_SUCCESS);
}

static int	_spawn_monitor(pthread_t *monitor_thread, t_philo *philos)
{
	if (pthread_create(monitor_thread, NULL, monitor_routine, philos))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	simulation(t_philo *philos, t_table *table, pthread_t *monitor_thread)
{
	for (int i = 0; i < table->philo_count; i++)
		printf("%i has fork %i and %i\n", philos[i].id, philos[i].right_fork->id, philos[i].left_fork->id);
	if (_spawn_philos(philos, table->philo_count))
		return (EXIT_FAILURE);
	philos->table->start_time = get_time();
	if (_set_in_sync(philos->table))
		return (EXIT_FAILURE);
	if (_spawn_monitor(monitor_thread, philos))
		return (EXIT_FAILURE);
	for (int i = 0; i < table->philo_count; i++)
		pthread_join(philos[i].thread, NULL);
	pthread_join(*monitor_thread, NULL);
	at_exit(philos, table);
	// TODO:
	// wait for all threads to be created;
	// start simulation;
	// cleanup;
	return (EXIT_SUCCESS);
}
