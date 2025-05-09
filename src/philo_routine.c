/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 19:04:58 by rha-le            #+#    #+#             */
/*   Updated: 2025/05/09 20:55:19 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "structs.h"
#include "actions.h"
#include "philo_utils.h"
#include "time.h"
#include "log.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	t_table *table;

	philo = (t_philo *)arg;
	table = philo->table;
	if (_wait_for_all(table))
		return (NULL);
	if (philo->id % 2 == 0)
		if (_think(philo, 1))
			return (NULL);
	while (!_check_alive(table))
	{
		if (_eat(philo, (useconds_t)table->time_to_eat))
			return (NULL);
		if (_sleep(philo, (useconds_t)table->time_to_sleep))
			return (NULL);
		if (_think(philo, 3))
			return (NULL);
	}
	return (NULL);
}
