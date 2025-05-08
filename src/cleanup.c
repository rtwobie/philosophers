/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:38:43 by rha-le            #+#    #+#             */
/*   Updated: 2025/05/01 17:25:16 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <pthread.h>
#include "structs.h"

void	destroy_forks(t_fork *fork, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&fork[i].mutex);
		++i;
	}
	free(fork);
}

void	at_exit(t_philo *philos, t_table *table)
{
	if (table->fork)
		destroy_forks(table->fork, table->philo_count);
	pthread_mutex_destroy(&table->in_sync_mutex);
	pthread_mutex_destroy(&table->log_mutex);
	pthread_mutex_destroy(&table->dead_mutex);
	pthread_mutex_destroy(&table->last_meal_mutex);
	if (philos)
		free(philos);
}
