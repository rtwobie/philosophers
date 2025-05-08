/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 19:04:58 by rha-le            #+#    #+#             */
/*   Updated: 2025/05/02 16:56:17 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "structs.h"
#include "actions.h"
#include "time.h"
#include "log.h"

static int _wait_for_all(t_table *table)
{
	if (!table)
		return (EXIT_FAILURE);
	while(1)
	{
		if (pthread_mutex_lock(&table->in_sync_mutex))
			return (log_msg(ERR_MUTEX_LOCK_MSG), EXIT_FAILURE);
		if (table->in_sync == true)
			break ;
		if (pthread_mutex_unlock(&table->in_sync_mutex))
			return (log_msg(ERR_MUTEX_UNLOCK_MSG), EXIT_FAILURE);
	}
	if (pthread_mutex_unlock(&table->in_sync_mutex))
		return (log_msg(ERR_MUTEX_UNLOCK_MSG), EXIT_FAILURE);
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

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	t_table *table;

	philo = (t_philo *)arg;
	table = philo->table;
	if (_wait_for_all(table))
		return (NULL);
	// TODO: offset of even numbered philos
	while (!_check_alive(table))
	{
		if (_eat(philo, (useconds_t)table->time_to_eat))
			return (NULL);
		if (_sleep(philo, (useconds_t)table->time_to_sleep))
			return (NULL);
		if (_think(philo, 3))
			return (NULL);
	}
	return (NULL);
}
