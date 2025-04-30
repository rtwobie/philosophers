/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 19:04:58 by rha-le            #+#    #+#             */
/*   Updated: 2025/05/01 01:13:56 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "structs.h"
#include "time.h"
#include "log.h"

static int _wait_for_all(t_table *table)
{
	if (!table)
		return (EXIT_FAILURE);
	while(1)
	{
		if (pthread_mutex_lock(&table->in_sync_mutex))
			return (EXIT_FAILURE);
		if (table->in_sync == true)
			break ;
		if (pthread_mutex_unlock(&table->in_sync_mutex))
			return (EXIT_FAILURE);
	}
	if (pthread_mutex_unlock(&table->in_sync_mutex))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (_wait_for_all(philo->table))
		return (NULL);
	// TODO: offset of even numbered philos
	while (philo->table->end == false)
	{
		log_philo(get_timestamp(philo->table->start_time), philo, "says hello");
		sleep(1);
		// TODO: eat, sleep, think, pickup, putdown;
		// for reference
		// check:
		// https://web.eecs.utk.edu/~mbeck/classes/cs560/560/notes/Dphil/lecture.html
		// https://www.cs.yale.edu/homes/aspnes/pinewiki/Deadlock.html
	}
	return (NULL);
}
