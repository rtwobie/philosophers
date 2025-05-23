/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 17:20:14 by rha-le            #+#    #+#             */
/*   Updated: 2025/05/09 21:05:12 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "structs.h"
#include "log.h"
#include "philo_utils.h"

int	_pickup(t_philo *philo, t_fork *right_fork, t_fork *left_fork);
int	_putdown(t_fork *right_fork, t_fork *left_fork);

int	_eat(t_philo *philo, useconds_t time_to_eat)
{
	t_table	*table;

	table = philo->table;
	if (_check_alive(table))
		return (1);
	if (_pickup(philo, philo->right_fork, philo->left_fork))
		return (1);
	if (pthread_mutex_lock(&table->last_meal_mutex))
		return (log_msg(ERR_MUTEX_LOCK_MSG), EXIT_FAILURE);
	philo->time_of_last_meal = get_timestamp(table->start_time);
	if (pthread_mutex_unlock(&table->last_meal_mutex))
		return (log_msg(ERR_MUTEX_UNLOCK_MSG), EXIT_FAILURE);
	if (log_philo(philo->time_of_last_meal, &table->log_mutex, philo->id, EAT))
		return (EXIT_FAILURE);
	if (usleep(time_to_eat * 1000))
		return (EXIT_FAILURE);
	if (_increase_eaten(table, philo))
		return (EXIT_FAILURE);
	_putdown(philo->right_fork, philo->left_fork);
	return (EXIT_SUCCESS);
}

int	_sleep(t_philo *philo, useconds_t time_to_sleep)
{
	t_table	*table;

	table = philo->table;
	if (_check_alive(table))
		return (1);
	if (log_philo(get_timestamp(table->start_time), &table->log_mutex, \
			philo->id, SLEEP))
		return (EXIT_FAILURE);
	if (usleep(time_to_sleep * 1000))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	_think(t_philo *philo, useconds_t time_to_think)
{
	t_table	*table;

	table = philo->table;
	if (_check_alive(table))
		return (1);
	if (log_philo(get_timestamp(table->start_time), &table->log_mutex, \
			philo->id, THINK))
		return (EXIT_FAILURE);
	if (usleep(time_to_think * 1000))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
