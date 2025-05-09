/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:45:48 by rha-le            #+#    #+#             */
/*   Updated: 2025/05/01 16:09:52 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "structs.h"

void	log_msg(char *msg)
{
	printf("%s\n", msg);
}

int	log_philo(uint64_t timestamp, \
				t_mutex *log_mutex, \
				unsigned int id, \
				char *status)
{
	if (pthread_mutex_lock(log_mutex))
		return (EXIT_FAILURE);
	printf("%lu %i %s\n", timestamp, id, status);
	if (pthread_mutex_unlock(log_mutex))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
