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
#include "structs.h"
#include "log.h"

static unsigned int	_check_alive(t_table *table)
{
	if (pthread_mutex_lock(&table->dead_mutex))
		return (log_msg(ERR_MUTEX_LOCK_MSG), 0);
	if (table->dead)
		return (table->dead);
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
			// TODO: exit and stop all threads
			log_philo(get_timestamp(table->start_time), &table->log_mutex, dead, DIE);
			return (NULL);
		}
	}
	return (NULL);
}
