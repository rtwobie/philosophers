/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:28:32 by rha-le            #+#    #+#             */
/*   Updated: 2025/05/09 20:45:32 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <pthread.h>

#include "init.h"
#include "simulation.h"
#include "structs.h"

int	main(int argc, char *argv[])
{
	t_philo			*philos;
	pthread_t		monitor_thead;
	static t_table	table = {
		PTHREAD_MUTEX_INITIALIZER,
		PTHREAD_MUTEX_INITIALIZER,
		PTHREAD_MUTEX_INITIALIZER,
		PTHREAD_MUTEX_INITIALIZER,
		PTHREAD_MUTEX_INITIALIZER,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	};

	philos = NULL;
	if (init(&philos, &table, argc, argv))
		return (EXIT_FAILURE);
	if (simulation(philos, &table, &monitor_thead))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
