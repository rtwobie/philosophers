/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:28:32 by rha-le            #+#    #+#             */
/*   Updated: 2025/05/01 00:54:06 by rha-le           ###   ########.fr       */
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
	t_philo			*philo;

	philo = NULL;
	if (init(&philo, &table, argc, argv))
		return (EXIT_FAILURE);
	if (simulation(philo, &table))
		return (EXIT_FAILURE);
	printf("SUCCESS!\n"); // TODO: delete later!
	return (EXIT_SUCCESS);
}
