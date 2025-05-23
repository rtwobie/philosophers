/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:48:03 by rha-le            #+#    #+#             */
/*   Updated: 2025/05/09 21:12:06 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "log.h"
#include "structs.h"
#include "philo_utils.h"

static int	_pickup_right_first(t_philo *philo, \
								t_fork *right_fork, \
								t_fork *left_fork)
{
	t_table	*tbl;

	tbl = philo->table;
	if (pthread_mutex_lock(&right_fork->mutex))
		return (log_msg(ERR_MUTEX_LOCK_MSG), EXIT_FAILURE);
	if (_check_alive(tbl))
	{
		if (pthread_mutex_unlock(&right_fork->mutex))
			return (log_msg(ERR_MUTEX_UNLOCK_MSG), EXIT_FAILURE);
		return (1);
	}
	log_philo(get_timestamp(tbl->start_time), &tbl->log_mutex, philo->id, FORK);
	if (pthread_mutex_lock(&left_fork->mutex))
		return (log_msg(ERR_MUTEX_LOCK_MSG), EXIT_FAILURE);
	if (_check_alive(tbl))
	{
		if (pthread_mutex_unlock(&left_fork->mutex))
			return (log_msg(ERR_MUTEX_UNLOCK_MSG), EXIT_FAILURE);
		if (pthread_mutex_unlock(&right_fork->mutex))
			return (log_msg(ERR_MUTEX_UNLOCK_MSG), EXIT_FAILURE);
		return (1);
	}
	log_philo(get_timestamp(tbl->start_time), &tbl->log_mutex, philo->id, FORK);
	return (EXIT_SUCCESS);
}

static int	_single_philo(t_philo *philo)
{
	if (philo->left_fork == philo->right_fork)
	{
		usleep((useconds_t)philo->table->time_to_die * 1000);
		if (pthread_mutex_unlock(&philo->left_fork->mutex))
			return (log_msg(ERR_MUTEX_UNLOCK_MSG), EXIT_FAILURE);
		return (1);
	}
	return (0);
}

static int	_pickup_left_first(t_philo *philo, \
								t_fork *right_fork, \
								t_fork *left_fork)
{
	t_table	*tbl;

	tbl = philo->table;
	if (pthread_mutex_lock(&left_fork->mutex))
		return (log_msg(ERR_MUTEX_LOCK_MSG), EXIT_FAILURE);
	if (_check_alive(tbl))
	{
		pthread_mutex_unlock(&left_fork->mutex);
		return (1);
	}
	log_philo(get_timestamp(tbl->start_time), &tbl->log_mutex, philo->id, FORK);
	if (_single_philo(philo))
		return (1);
	if (pthread_mutex_lock(&right_fork->mutex))
		return (log_msg(ERR_MUTEX_LOCK_MSG), EXIT_FAILURE);
	if (_check_alive(tbl))
	{
		if (pthread_mutex_unlock(&right_fork->mutex))
			return (log_msg(ERR_MUTEX_UNLOCK_MSG), EXIT_FAILURE);
		if (pthread_mutex_unlock(&left_fork->mutex))
			return (log_msg(ERR_MUTEX_UNLOCK_MSG), EXIT_FAILURE);
		return (1);
	}
	log_philo(get_timestamp(tbl->start_time), &tbl->log_mutex, philo->id, FORK);
	return (EXIT_SUCCESS);
}

int	_pickup(t_philo *philo, t_fork *right_fork, t_fork *left_fork)
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

int	_putdown(t_fork *right_fork, t_fork *left_fork)
{
	if (pthread_mutex_unlock(&right_fork->mutex))
		return (log_msg(ERR_MUTEX_UNLOCK_MSG), EXIT_FAILURE);
	if (pthread_mutex_unlock(&left_fork->mutex))
		return (log_msg(ERR_MUTEX_UNLOCK_MSG), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
