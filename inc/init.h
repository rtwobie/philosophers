/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:35:44 by rha-le            #+#    #+#             */
/*   Updated: 2025/04/30 15:25:05 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include "structs.h"

int	parse_input(int argc, char *argv[], t_table *table);
int	init(t_philo *philo, t_table *table);

#endif // !INIT_H
