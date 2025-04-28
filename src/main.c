/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:32:11 by rha-le            #+#    #+#             */
/*   Updated: 2025/04/28 20:43:02 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "init.h"
#include "util.h"
#include "routine.h"
#include "print.h"

int	get_input(t_table *table, char *argv[])
{
	table->philo_count = atoui(argv[1]);
	table->time._to_die = atoui64(argv[2]) * 1000;
	table->time._to_eat = atoui64(argv[3]) * 1000;
	table->time._to_sleep = atoui64(argv[4]) * 1000;
	if (table->philo_count == 0 || table->time._to_die == 0 || \
		table->time._to_sleep == 0 || table->time._to_eat == 0)
		return (1);
	// TODO: check int_max
	return (0);
}

void	start(t_table *table)
{
	unsigned int	i;

	i = 0;
	while (i < table->philo_count)
	{
		pthread_create(&table->philo[i].tid, NULL, routine, &table->philo[i]);
		++i;
		// TODO: maybe add threat protection
	}
	table->all_threads_born = true;
	table->time.start_time = get_starttime_ms();
}

int	main(int argc, char *argv[])
{
	t_table	table;

	if (argc != 5)
		return (1);
	memset(&table, 0, sizeof(table));
	if (get_input(&table, argv) != 0)
	{
		free_all(&table);
		return (1);
	}
	if (init_table(&table) != 0)
	{
		free_all(&table);
		return (1);
	}
	start(&table);
	for (unsigned int i = 0; i < table.philo_count; i++)
		pthread_join(table.philo[i].tid, NULL);

}
