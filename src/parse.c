/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:32:46 by rha-le            #+#    #+#             */
/*   Updated: 2025/10/10 22:03:38 by rtwobie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "strtol.h"
#include "log.h"
#include "structs.h"

int	_parse_input(int argc, char *argv[], t_table *table)
{
	if (argc == 5)
		table->min_num_of_meals = -1;
	else if (argc == 6)
	{
		table->min_num_of_meals = ft_strtoi(argv[5], NULL, 10);
		if (table->min_num_of_meals <= 0)
			return (log_msg(INVALID_MIN_AMOUNT_EAT_MSG), EXIT_FAILURE);
	}
	else
		return (log_msg(WRONG_NUM_OF_ARG_MSG), EXIT_FAILURE);
	table->philo_count = ft_strtoi(argv[1], NULL, 10);
	if (table->philo_count > 200)
		table->philo_count = 200;
	if (table->philo_count <= 0)
		return (log_msg(INVALID_PHILO_SIZE_MSG), EXIT_FAILURE);
	table->time_to_die = ft_strtoi(argv[2], NULL, 10);
	if (table->time_to_die <= 0)
		return (log_msg(INVALID_DIE_TIME_MSG), EXIT_FAILURE);
	table->time_to_eat = ft_strtoi(argv[3], NULL, 10);
	if (table->time_to_eat <= 0)
		return (log_msg(INVALID_EAT_TIME_MSG), EXIT_FAILURE);
	table->time_to_sleep = ft_strtoi(argv[4], NULL, 10);
	if (table->time_to_sleep <= 0)
		return (log_msg(INVALID_SLEEP_TIME_MSG), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
