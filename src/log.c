/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:45:48 by rha-le            #+#    #+#             */
/*   Updated: 2025/05/01 00:27:24 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "structs.h"

void	log_msg(char *msg)
{
	printf("%s\n", msg);
}

int	log_philo(uint64_t timestamp, t_philo *philo, char *status)
{
	if (pthread_mutex_lock(&philo->table->log_mutex))
		return (EXIT_FAILURE);
	printf("%lu %i %s\n", timestamp, philo->id, status);
	if (pthread_mutex_unlock(&philo->table->log_mutex))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
