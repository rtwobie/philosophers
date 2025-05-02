/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:03:26 by rha-le            #+#    #+#             */
/*   Updated: 2025/05/02 16:56:58 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ACTIONS_H
# define ACTIONS_H


# include <unistd.h>
# include "structs.h"

int	_sleep(t_philo *philo, useconds_t time_to_sleep);
int	_eat(t_philo *philo, useconds_t time_to_eat);
int	_philo_dies(t_philo *philo, t_mutex *dead_mutex);

#endif // !ACTIONS_H
