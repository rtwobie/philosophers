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

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	t_table *table;

	philo = (t_philo *)arg;
	table = philo->table;
	if (_wait_for_all(table))
		return (NULL);
	// TODO: offset of even numbered philos
	while (1)
	{
		/*if (philo->id == 1 && get_timestamp(table->start_time) >= 4000)*/
		/*{*/
		/*	if (_philo_dies(philo, &table->dead_mutex))*/
		/*		return (NULL);*/
		/*}*/

		_sleep(philo, (useconds_t)table->time_to_sleep);
		_eat(philo, (useconds_t)table->time_to_eat);
		/*log_philo(get_timestamp(table->start_time), &table->log_mutex, philo->id, THINK);*/
		/*usleep(1000 * 1000);*/
		// TODO: eat, sleep, think, pickup, putdown;
		// for reference
		// check:
		// https://web.eecs.utk.edu/~mbeck/classes/cs560/560/notes/Dphil/lecture.html
		// https://www.cs.yale.edu/homes/aspnes/pinewiki/Deadlock.html
	}
	return (NULL);
}
