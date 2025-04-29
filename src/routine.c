/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 20:39:28 by rha-le            #+#    #+#             */
/*   Updated: 2025/04/29 20:30:10 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"
#include "structs.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>

static void	philo_eat(t_philo *philo, uint64_t time_to_eat)
{
	pthread_mutex_lock(philo->right_fork);
	print_status(get_timestamp(philo->time->start_time), &philo->table->print, philo->id, FORK);
	pthread_mutex_lock(philo->left_fork);
	print_status(get_timestamp(philo->time->start_time), &philo->table->print, philo->id, FORK);
	philo->last_meal_in_ms = get_time_ms();
	print_status(get_timestamp(philo->time->start_time), &philo->table->print, philo->id, EAT);
	usleep((useconds_t)time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

static void	philo_sleep(t_philo *philo, uint64_t time_to_sleep)
{
	print_status(get_timestamp(philo->time->start_time), &philo->table->print, philo->id, SLEEP);
	usleep((useconds_t)time_to_sleep);
}

static void	philo_think(t_philo *philo)
{
	print_status(get_timestamp(philo->time->start_time), &philo->table->print, philo->id, THINK);
}

void	*routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	while (philo->table->all_threads_born == false)
		;
	if (philo->id % 2 == 0)
		philo_think(philo);
	while(1)
	{
		philo_eat(philo, philo->time->_to_eat);
		philo_sleep(philo, philo->time->_to_sleep);
		philo_think(philo);
	}
	return (NULL);
}
