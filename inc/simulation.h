/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 19:14:36 by rha-le            #+#    #+#             */
/*   Updated: 2025/05/01 17:28:58 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMULATION_H
# define SIMULATION_H

# include "structs.h"

int	simulation(t_philo *philos, t_table *table, pthread_t *monitor_thread);

#endif // !SIMULATION_H
