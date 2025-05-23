/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 20:26:22 by rha-le            #+#    #+#             */
/*   Updated: 2025/05/09 20:52:57 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "structs.h"
#include "log.h"

int	_wait_for_all(t_table *table)
{
	if (!table)
		return (EXIT_FAILURE);
	while (1)
	{
		if (pthread_mutex_lock(&table->in_sync_mutex))
			return (log_msg(ERR_MUTEX_LOCK_MSG), EXIT_FAILURE);
		if (table->in_sync == true)
		{
			if (pthread_mutex_unlock(&table->in_sync_mutex))
				return (log_msg(ERR_MUTEX_UNLOCK_MSG), EXIT_FAILURE);
			return (EXIT_SUCCESS);
		}
		if (pthread_mutex_unlock(&table->in_sync_mutex))
			return (log_msg(ERR_MUTEX_UNLOCK_MSG), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	_check_all_full(t_table *table)
{
	if (pthread_mutex_lock(&table->full_mutex))
		return (log_msg(ERR_MUTEX_LOCK_MSG), 0);
	if (table->amount_full == table->philo_count)
	{
		if (pthread_mutex_unlock(&table->full_mutex))
			return (log_msg(ERR_MUTEX_UNLOCK_MSG), 0);
		return (1);
	}
	if (pthread_mutex_unlock(&table->full_mutex))
		return (log_msg(ERR_MUTEX_UNLOCK_MSG), 0);
	return (0);
}

unsigned int	_check_alive(t_table *table)
{
	if (pthread_mutex_lock(&table->dead_mutex))
		return (log_msg(ERR_MUTEX_LOCK_MSG), 0);
	if (table->dead)
	{
		if (pthread_mutex_unlock(&table->dead_mutex))
			return (log_msg(ERR_MUTEX_UNLOCK_MSG), 0);
		return (1);
	}
	if (pthread_mutex_unlock(&table->dead_mutex))
		return (log_msg(ERR_MUTEX_UNLOCK_MSG), 0);
	return (0);
}

int	_increase_eaten(t_table *table, t_philo *philo)
{
	if (table->min_num_of_meals == -1)
		return (EXIT_SUCCESS);
	++philo->times_eaten;
	if (philo->times_eaten == table->min_num_of_meals)
	{
		if (pthread_mutex_lock(&table->full_mutex))
			return (log_msg(ERR_MUTEX_LOCK_MSG), EXIT_FAILURE);
		++table->amount_full;
		if (pthread_mutex_unlock(&table->full_mutex))
			return (log_msg(ERR_MUTEX_UNLOCK_MSG), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
