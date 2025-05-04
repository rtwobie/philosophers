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
// WARNING: FIGURE OUT HOW TO SET DEAD VARIABLE WITHOUT BIG DELAY !
//			+ FIGURE OUT WHY THE PROGRAM IS STUCK ONCE SOMEONE DIED !

// TODO: change parameters to fit for NORMINETTE
static int _pickup(t_philo *philo, t_fork *right_fork, t_fork *left_fork)
{
	t_table *table;

	table = philo->table;
	if (philo->id % 2 == 0)
	{
		if (pthread_mutex_lock(&right_fork->mutex))
			return (log_msg(ERR_MUTEX_LOCK_MSG), EXIT_FAILURE);
		log_philo(get_timestamp(table->start_time), &table->log_mutex, philo->id, DEBUG_FORK_R);
		if (pthread_mutex_lock(&left_fork->mutex))
			return (log_msg(ERR_MUTEX_LOCK_MSG), EXIT_FAILURE);
		log_philo(get_timestamp(table->start_time), &table->log_mutex, philo->id, DEBUG_FORK_L);
	}
	else
	{
		if (pthread_mutex_lock(&left_fork->mutex))
			return (log_msg(ERR_MUTEX_LOCK_MSG), EXIT_FAILURE);
		log_philo(get_timestamp(table->start_time), &table->log_mutex, philo->id, DEBUG_FORK_L);
		if (pthread_mutex_lock(&right_fork->mutex))
			return (log_msg(ERR_MUTEX_LOCK_MSG), EXIT_FAILURE);
		log_philo(get_timestamp(table->start_time), &table->log_mutex, philo->id, DEBUG_FORK_R);
	}
	return (EXIT_SUCCESS);
}

static int _putdown(t_philo *philo, t_fork *right_fork, t_fork *left_fork)
{
	t_table *table;

	table = philo->table;
	if (pthread_mutex_unlock(&right_fork->mutex))
		return (log_msg(ERR_MUTEX_UNLOCK_MSG), EXIT_FAILURE);
	log_philo(get_timestamp(table->start_time), &table->log_mutex, philo->id, DEBUG_FORK_R2);
	if (pthread_mutex_unlock(&left_fork->mutex))
		return (log_msg(ERR_MUTEX_UNLOCK_MSG), EXIT_FAILURE);
	log_philo(get_timestamp(table->start_time), &table->log_mutex, philo->id, DEBUG_FORK_L2);
	return (EXIT_SUCCESS);
}

int	_eat(t_philo *philo, useconds_t time_to_eat)
{
	t_table *table;
	uint64_t time_now;

	table = philo->table;
	if (_pickup(philo, philo->right_fork, philo->left_fork))
		return (EXIT_FAILURE);


	// TODO: save timestamp to last meal
	//		 then compare against timestamp now (now - time_of_last_meal)
	//		 then die depending on time_to_die or set last meal to now

	time_now = get_timestamp(table->start_time);
	if (pthread_mutex_lock(&table->last_meal_mutex))
		return (log_msg(ERR_MUTEX_LOCK_MSG), EXIT_FAILURE);
	philo->time_of_last_meal = time_now;
	if (pthread_mutex_unlock(&table->last_meal_mutex))
		return (log_msg(ERR_MUTEX_UNLOCK_MSG), EXIT_FAILURE);

	if (log_philo(time_now, &table->log_mutex, philo->id, EAT))
		return (EXIT_FAILURE);
	if (usleep(time_to_eat * 1000))
		return (EXIT_FAILURE);

	if (_putdown(philo, philo->right_fork, philo->left_fork))
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
