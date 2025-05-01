/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:45:56 by rha-le            #+#    #+#             */
/*   Updated: 2025/05/01 17:17:18 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "structs.h"
#include "log.h"

static unsigned int	_check_alive(t_table *table)
{
	pthread_mutex_lock(&table->dead_mutex);
	if (table->dead)
		return (table->dead);
	pthread_mutex_unlock(&table->dead_mutex);
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_philo			*philos;
	t_table			*table;
	unsigned int	dead;

	philos = (t_philo *)arg;
	table = philos->table;

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
