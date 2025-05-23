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
#include <string.h>
#include "structs.h"
#include "init.h"
#include "simulation.h"

int	main(int argc, char *argv[])
{
	static t_table	table = {0};
	t_philo			*philos;
	pthread_t		monitor_thead;

	philos = NULL;
	if (init(&philos, &table, argc, argv))
		return (EXIT_FAILURE);
	if (simulation(philos, &table, &monitor_thead))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
