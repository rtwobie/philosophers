/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:32:46 by rha-le            #+#    #+#             */
/*   Updated: 2025/04/30 17:46:44 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "log.h"
#include "structs.h"

static int	_ft_atoi(const char *nptr)
{
	int		num;
	int		prev_num;

	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		++nptr;
	if (*nptr == '-')
		return (-1);
	if (*nptr == '+')
		++nptr;
	num = 0;
	prev_num = 0;
	while (*nptr >= '0' && *nptr <= '9')
	{
		num = (num * 10) + (*nptr - '0');
		if (prev_num > num)
			return (-1);
		prev_num = num;
		++nptr;
	}
	return (num);
}

int	parse_input(int argc, char *argv[], t_table *table)
{
	if (argc != 5)
		return (log_msg(WRONG_NUM_OF_ARG_MSG), EXIT_FAILURE);
	table->philo_count = _ft_atoi(argv[1]);
	if (table->philo_count == -1)
		return (log_msg(INVALID_PHILO_SIZE_MSG), EXIT_FAILURE);
	table->time_to_die = _ft_atoi(argv[2]);
	if (table->time_to_die == -1)
		return (log_msg(INVALID_DIE_TIME_MSG), EXIT_FAILURE);
	table->time_to_eat = _ft_atoi(argv[3]);
	if (table->time_to_eat == -1)
		return (log_msg(INVALID_EAT_TIME_MSG), EXIT_FAILURE);
	table->time_to_sleep = _ft_atoi(argv[4]);
	if (table->time_to_sleep == -1)
		return (log_msg(INVALID_SLEEP_TIME_MSG), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
