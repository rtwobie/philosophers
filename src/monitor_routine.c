/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:45:56 by rha-le            #+#    #+#             */
/*   Updated: 2025/05/02 16:48:21 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "structs.h"
#include "log.h"
#include "time.h"

static int	_last_time_eaten(t_philo *philo, t_table *table)
{
	uint64_t	time_now;

	time_now = get_timestamp(table->start_time);
	if (pthread_mutex_lock(&table->last_meal_mutex))
		return (log_msg(ERR_MUTEX_LOCK_MSG), EXIT_FAILURE);
	if (time_now - philo->time_of_last_meal >= (uint64_t)table->time_to_die)
	{
		if (pthread_mutex_unlock(&table->last_meal_mutex))
			return (log_msg(ERR_MUTEX_UNLOCK_MSG), EXIT_FAILURE);
		return (1);
	}
	if (pthread_mutex_unlock(&table->last_meal_mutex))
		return (log_msg(ERR_MUTEX_UNLOCK_MSG), EXIT_FAILURE);
	return (0);
}

static int	_philo_dies(t_philo *philo, t_mutex *dead_mutex)
{
	if (pthread_mutex_lock(dead_mutex))
		return (log_msg(ERR_MUTEX_LOCK_MSG), EXIT_FAILURE);
	philo->table->dead = philo->id;
	if (pthread_mutex_unlock(dead_mutex))
		return (log_msg(ERR_MUTEX_UNLOCK_MSG), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	_check_death(t_philo *philos, t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_count)
	{
		if (_last_time_eaten(&philos[i], table))
			if (_philo_dies(&philos[i], &table->dead_mutex))
				return (EXIT_FAILURE);
		++i;
	}
	return (EXIT_SUCCESS);
}

static unsigned int	_check_alive(t_table *table)
{
	if (pthread_mutex_lock(&table->dead_mutex))
		return (log_msg(ERR_MUTEX_LOCK_MSG), 0);
	if (table->dead)
	{
		if (pthread_mutex_unlock(&table->dead_mutex))
			return (log_msg(ERR_MUTEX_UNLOCK_MSG), 0);
		return (table->dead);
	}
	if (pthread_mutex_unlock(&table->dead_mutex))
		return (log_msg(ERR_MUTEX_UNLOCK_MSG), 0);
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_philo			*philos;
	t_table			*table;
	unsigned int	dead;

	philos = (t_philo *)arg;
	table = philos->table;
	dead = 0;
	while (1)
	{
		dead = _check_alive(table);
		if (dead)
		{
			log_philo(get_timestamp(table->start_time), &table->log_mutex, \
						dead, DIE);
			return (NULL);
		}
		_check_death(philos, table);
		usleep(1 * 1000);
	}
	return (NULL);
}
