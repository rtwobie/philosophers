/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:48:03 by rha-le            #+#    #+#             */
/*   Updated: 2025/05/08 17:03:22 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "log.h"
#include "structs.h"

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

static int _pickup_right_first(t_philo *philo, t_fork *right_fork, t_fork *left_fork)
{
	t_table *table;

	table = philo->table;
	if (pthread_mutex_lock(&right_fork->mutex))
		return (log_msg(ERR_MUTEX_LOCK_MSG), EXIT_FAILURE);
	if (_check_alive(table))
	{
		if (pthread_mutex_unlock(&right_fork->mutex))
			return (log_msg(ERR_MUTEX_UNLOCK_MSG), EXIT_FAILURE);
		return (1);
	}
	log_philo(get_timestamp(table->start_time), &table->log_mutex, philo->id, FORK); // NOTE: Change later!
	if (pthread_mutex_lock(&left_fork->mutex))
		return (log_msg(ERR_MUTEX_LOCK_MSG), EXIT_FAILURE);
	if (_check_alive(table))
	{
		if (pthread_mutex_unlock(&left_fork->mutex))
			return (log_msg(ERR_MUTEX_UNLOCK_MSG), EXIT_FAILURE);
		if (pthread_mutex_unlock(&right_fork->mutex))
			return (log_msg(ERR_MUTEX_UNLOCK_MSG), EXIT_FAILURE);
		return (1);
	}
	log_philo(get_timestamp(table->start_time), &table->log_mutex, philo->id, FORK); // NOTE: Change later!
	return (EXIT_SUCCESS);
}

static int _pickup_left_first(t_philo *philo, t_fork *right_fork, t_fork *left_fork)
{
	t_table *table;

	table = philo->table;
	if (pthread_mutex_lock(&left_fork->mutex))
		return (log_msg(ERR_MUTEX_LOCK_MSG), EXIT_FAILURE);
	if (_check_alive(table))
	{
		if (pthread_mutex_unlock(&left_fork->mutex))
			return (log_msg(ERR_MUTEX_UNLOCK_MSG), EXIT_FAILURE);
		return (1);
	}
	log_philo(get_timestamp(table->start_time), &table->log_mutex, philo->id, FORK); // NOTE: Change later!
	if (philo->left_fork == philo->right_fork)
	{
		usleep((useconds_t)table->time_to_die * 1000);
		if (pthread_mutex_unlock(&left_fork->mutex))
			return (log_msg(ERR_MUTEX_UNLOCK_MSG), EXIT_FAILURE);
		return (1);
	}
	if (pthread_mutex_lock(&right_fork->mutex))
		return (log_msg(ERR_MUTEX_LOCK_MSG), EXIT_FAILURE);
	if (_check_alive(table))
	{
		if (pthread_mutex_unlock(&right_fork->mutex))
			return (log_msg(ERR_MUTEX_UNLOCK_MSG), EXIT_FAILURE);
		if (pthread_mutex_unlock(&left_fork->mutex))
			return (log_msg(ERR_MUTEX_UNLOCK_MSG), EXIT_FAILURE);
		return (1);
	}
	log_philo(get_timestamp(table->start_time), &table->log_mutex, philo->id, FORK); // NOTE: Change later!
	return (EXIT_SUCCESS);
}

int _pickup(t_philo *philo, t_fork *right_fork, t_fork *left_fork)
{
	if (philo->id % 2 == 0)
	{
		if (_pickup_right_first(philo, right_fork, left_fork))
			return (1);
	}
	else
	{
		if (_pickup_left_first(philo, right_fork, left_fork))
			return (1);
	}
	return (EXIT_SUCCESS);
}

int _putdown(t_philo *philo, t_fork *right_fork, t_fork *left_fork)
{
	/*t_table *table;*/
	/**/
	/*table = philo->table;*/
	(void)philo;
	if (pthread_mutex_unlock(&right_fork->mutex))
		return (log_msg(ERR_MUTEX_UNLOCK_MSG), EXIT_FAILURE);
	/*log_philo(get_timestamp(table->start_time), &table->log_mutex, philo->id, DEBUG_FORK_R2); // NOTE: Delete later!*/
	if (pthread_mutex_unlock(&left_fork->mutex))
		return (log_msg(ERR_MUTEX_UNLOCK_MSG), EXIT_FAILURE);
	/*log_philo(get_timestamp(table->start_time), &table->log_mutex, philo->id, DEBUG_FORK_L2); // NOTE: Delete later!*/
	return (EXIT_SUCCESS);
}

