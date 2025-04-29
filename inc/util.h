/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 15:16:10 by rha-le            #+#    #+#             */
/*   Updated: 2025/04/27 19:47:25 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

#include "structs.h"
# include <pthread.h>
# include <stdint.h>

unsigned int	atoui(const char *nptr);
uint64_t	atoui64(const char *nptr);
void	destroy_mutex(t_mutex *mutex);
void	free_all(t_table *table);

#endif //!UTILS_H
