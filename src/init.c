/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:15:15 by rha-le            #+#    #+#             */
/*   Updated: 2025/05/01 01:14:58 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "init.h"
#include "cleanup.h"
#include "log.h"

static int	_init_forks(t_table *table)
{
	t_fork	*fork;
	int		i;

	table->fork = malloc(((unsigned long)table->philo_count) * (sizeof(*fork)));
	if (!table->fork)
		return (EXIT_FAILURE);
	fork = table->fork;
	memset(fork, 0, (sizeof(*fork) * (unsigned long)table->philo_count));
	i = 0;
	while (i < table->philo_count)
	{
		if (pthread_mutex_init(&fork[i].mutex, NULL))
		{
			destroy_forks(fork, table->philo_count);
			return (log_msg(ERR_INIT_FORKS_MSG), EXIT_FAILURE);
		}
		fork[i].id = (unsigned int)i + 1;
		++i;
	}
	return (EXIT_SUCCESS);
}

static int	_init_philo(t_philo **philo, t_table *table)
{
	int		i;

	*philo = malloc(((unsigned long)table->philo_count) * sizeof(**philo));
	if (!*philo)
		return (EXIT_FAILURE);
	memset(*philo, 0, ((unsigned long)table->philo_count) * sizeof(**philo));
	i = 0;
	while (i < table->philo_count)
	{
		(*philo)[i].id = (unsigned int)i + 1;
		(*philo)[i].right_fork = &table->fork[i];
		(*philo)[i].left_fork = &table->fork[(i + 1) % table->philo_count];
		(*philo)[i].table = table;
		++i;
	}
	return (EXIT_SUCCESS);
}

static int	_init_mutex(t_table *table)
{
	if (pthread_mutex_init(&table->in_sync_mutex, NULL))
		return (log_msg(ERR_INIT_MUTEX_MSG), EXIT_FAILURE);
	if (pthread_mutex_init(&table->log_mutex, NULL))
		return (log_msg(ERR_INIT_MUTEX_MSG), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/*static int	_calc_think_time(int time_to_eat, int time_to_sleep, int count)*/
/*{*/
/*	int	time_to_think;*/
/**/
/*	time_to_think = 0;*/
/*	if ((count & 1) && )*/
/*	return (time_to_think);*/
/*}*/

int	init(t_philo **philo, t_table *table, int argc, char *argv[])
{
	if (_parse_input(argc, argv, table))
		return (EXIT_FAILURE);
	if (_init_forks(table))
		return (EXIT_FAILURE);
	if (_init_mutex(table))
		return (EXIT_FAILURE);
	if (_init_philo(philo, table))
	{
		destroy_forks(table->fork, table->philo_count);
		return (EXIT_FAILURE);
	}
	// TODO: thinking_time
	//	table->time_to_think = _calc_think_time();
	return (EXIT_SUCCESS);
}
