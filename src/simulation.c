/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 19:14:57 by rha-le            #+#    #+#             */
/*   Updated: 2025/05/02 16:22:25 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "structs.h"
#include "routine.h"
#include "log.h"
#include "cleanup.h"

static int	_set_in_sync(t_table *table)
{
	if (pthread_mutex_lock(&table->in_sync_mutex))
		return (log_msg(ERR_MUTEX_LOCK_MSG), EXIT_FAILURE);
	table->in_sync = true;
	if (pthread_mutex_unlock(&table->in_sync_mutex))
		return (log_msg(ERR_MUTEX_UNLOCK_MSG), EXIT_FAILURE);
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
			destroy_forks(philos->table->fork, count);
			free(philos);
			return (log_msg(ERR_PTHREAD_CREATE_MSG), EXIT_FAILURE);
		}
		++i;
	}
	return (EXIT_SUCCESS);
}

static int	_spawn_monitor(pthread_t *monitor_thread, t_philo *philos)
{
	if (pthread_create(monitor_thread, NULL, monitor_routine, philos))
		return (log_msg(ERR_PTHREAD_CREATE_MSG), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	simulation(t_philo *philos, t_table *table, pthread_t *monitor_thread)
{
	int	i;

	if (_spawn_philos(philos, table->philo_count))
		return (EXIT_FAILURE);
	philos->table->start_time = get_time();
	if (_set_in_sync(philos->table))
		return (EXIT_FAILURE);
	if (_spawn_monitor(monitor_thread, philos))
		return (EXIT_FAILURE);
	i = 0;
	while (i < table->philo_count)
	{
		pthread_join(philos[i].thread, NULL);
		++i;
	}
	pthread_join(*monitor_thread, NULL);
	at_exit(philos, table);
	return (EXIT_SUCCESS);
}
