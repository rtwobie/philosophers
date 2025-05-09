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

unsigned int	_check_alive(t_table *table)
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
