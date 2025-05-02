/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 17:20:14 by rha-le            #+#    #+#             */
/*   Updated: 2025/05/02 16:55:59 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "structs.h"
#include "log.h"

// TODO: _eat(), _sleep(), _think(), _pickup(), _putdown()

static int _pickup(unsigned int id, t_fork *right_fork, t_fork *left_fork)
{
	// WARN: If im stuck at lock how to die at the right time?
	// --> if deadlock how do check death
	if (id % 2 == 0)
	{
		if (pthread_mutex_lock(&right_fork->mutex))
			return (log_msg(ERR_MUTEX_LOCK_MSG), EXIT_FAILURE);
		if (pthread_mutex_lock(&left_fork->mutex))
			return (log_msg(ERR_MUTEX_LOCK_MSG), EXIT_FAILURE);
	}
	else
	{
		if (pthread_mutex_lock(&left_fork->mutex))
			return (log_msg(ERR_MUTEX_LOCK_MSG), EXIT_FAILURE);
		if (pthread_mutex_lock(&right_fork->mutex))
			return (log_msg(ERR_MUTEX_LOCK_MSG), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int _putdown(t_fork *right_fork, t_fork *left_fork)
{
	if (pthread_mutex_unlock(&right_fork->mutex))
		return (log_msg(ERR_MUTEX_UNLOCK_MSG), EXIT_FAILURE);
	if (pthread_mutex_unlock(&left_fork->mutex))
		return (log_msg(ERR_MUTEX_UNLOCK_MSG), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	_philo_dies(t_philo *philo, t_mutex *dead_mutex)
{
	if (pthread_mutex_lock(dead_mutex))
		return (log_msg(ERR_MUTEX_LOCK_MSG), EXIT_FAILURE);
	philo->table->dead = philo->id;
	if (pthread_mutex_unlock(dead_mutex))
		return (log_msg(ERR_MUTEX_UNLOCK_MSG), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	_eat(t_philo *philo, useconds_t time_to_eat)
{
	t_table *table;
	/*useconds_t time_now;*/

	table = philo->table;
	if (_pickup(philo->id, philo->right_fork, philo->left_fork))
		return (EXIT_FAILURE);


	// TODO: save timestamp to last meal
	//		 then compare against timestamp now (now - time_of_last_meal)
	//		 then die depending on time_to_die or set last meal to now
	if (log_philo(get_timestamp(table->start_time), &table->log_mutex, philo->id, EAT))
		return (EXIT_FAILURE);
	if (usleep(time_to_eat * 1000))
		return (EXIT_FAILURE);

	if (_putdown(philo->right_fork, philo->left_fork))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	_sleep(t_philo *philo, useconds_t time_to_sleep)
{
	t_table *table;

	table = philo->table;
	if (log_philo(get_timestamp(table->start_time), &table->log_mutex, philo->id, SLEEP))
		return (EXIT_FAILURE);
	if (usleep(time_to_sleep * 1000))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
