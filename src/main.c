/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:28:32 by rha-le            #+#    #+#             */
/*   Updated: 2025/04/30 20:04:20 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "init.h"
#include "simulation.h"

#include <stdio.h>
int	main(int argc, char *argv[])
{
	t_table	table;
	t_philo	*philo;

	philo = NULL;
	memset(&table, 0, sizeof(table));
	if (init(&philo, &table, argc, argv))
		return (EXIT_FAILURE);
	if (simulation(philo, &table))
		return (EXIT_FAILURE);
	printf("SUCCESS!\n");
	return (EXIT_SUCCESS);
}
