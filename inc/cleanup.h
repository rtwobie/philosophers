/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 16:47:24 by rha-le            #+#    #+#             */
/*   Updated: 2025/04/30 17:11:01 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLEANUP_H
# define CLEANUP_H

# include "structs.h"

void	destroy_forks(t_fork *fork, int count);
void	at_exit(t_philo *philo, t_table *table);

#endif // !CLEANUP_H
