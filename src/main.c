/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:28:32 by rha-le            #+#    #+#             */
/*   Updated: 2025/04/30 17:46:11 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "init.h"

int	main(int argc, char *argv[])
{
	t_table	table;
	t_philo	*philo;

	philo = NULL;
	memset(&table, 0, sizeof(table));
	if (parse_input(argc, argv, &table))
		return (EXIT_FAILURE);
	if (init(philo, &table))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
