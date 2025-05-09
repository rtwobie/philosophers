/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 23:42:00 by rha-le            #+#    #+#             */
/*   Updated: 2025/05/01 00:47:10 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdint.h>
#include <sys/time.h>

uint64_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (((uint64_t)tv.tv_sec * 1000) + (uint64_t)tv.tv_usec / 1000);
}

uint64_t	get_timestamp(uint64_t start_time)
{
	return (get_time() - start_time);
}
