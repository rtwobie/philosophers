/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:21:01 by rha-le            #+#    #+#             */
/*   Updated: 2025/04/29 20:35:51 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "print.h"
#include <stdio.h>

static unsigned int	check_death(t_table *table, t_schedule *time)
{
	unsigned int	i;
	uint64_t x;

	i = 0;
	while (i < table->philo_count)
	{
		x = get_time_ms() - table->philo[i].last_meal_in_ms;
		if (x > (time->_to_die / 1000))
			return(i);
		++i;
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_table			*table;
	unsigned int	death;

	table = (t_table *)arg;
	while (1)
	{
		death = check_death(table, &table->time);
		if (death)
		{
			print_status(get_timestamp(table->time.start_time), &table->print, (int)death, DIE);
			break ;
		}
	}
	return (NULL);
}

