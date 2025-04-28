/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 20:39:28 by rha-le            #+#    #+#             */
/*   Updated: 2025/04/28 20:49:03 by rha-le           ###   ########.fr       */
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
	print_status(get_time_ms(philo->time->start_time), philo->id, FORK);
	pthread_mutex_lock(philo->left_fork);
	// TODO: calculate time_of_death
	print_status(get_time_ms(philo->time->start_time), philo->id, EAT);
	usleep((useconds_t)time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

static void	philo_sleep(t_philo *philo, uint64_t time_to_sleep)
{
	print_status(get_time_ms(philo->time->start_time), philo->id, SLEEP);
	usleep((useconds_t)time_to_sleep);
}

static void	philo_think(t_philo *philo)
{
	print_status(get_time_ms(philo->time->start_time), philo->id, THINK);
}

void	*routine(void *arg)
{
	t_philo		*philo;
	useconds_t	offset;

	philo = (t_philo *)arg;
	while (philo->all_threads_born == false)
		;
	offset = 0;
	if (philo->id % 2 == 0)
		offset = (useconds_t)philo->time->_to_eat;
	usleep(offset);
	while(1)
	{
		philo_think(philo);
		philo_eat(philo, philo->time->_to_eat);
		philo_sleep(philo, philo->time->_to_sleep);
	}
	return (NULL);
}
