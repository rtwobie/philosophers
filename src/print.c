/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 20:09:01 by rha-le            #+#    #+#             */
/*   Updated: 2025/04/28 20:41:52 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdio.h>
#include <sys/time.h>

uint64_t	get_starttime_ms(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (((uint64_t)tv.tv_sec * 1000) + (uint64_t)(tv.tv_usec / 1000));
}

uint64_t	get_time_ms(uint64_t start_time)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (((uint64_t)tv.tv_sec * 1000) + (uint64_t)(tv.tv_usec / 1000) - (start_time));
}

void	print_status(uint64_t time, int id, char *status)
{
	printf("%lu %d %s\n", time, id, status);
}

