/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 20:12:14 by rha-le            #+#    #+#             */
/*   Updated: 2025/04/28 20:44:46 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_H
# define PRINT_H

# include <stdint.h>

# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "died"
# define FORK "has taken a fork"

uint64_t	get_time_ms(uint64_t start_time);
uint64_t	get_starttime_ms(void);
void		print_status(uint64_t time, int id, char *status);

#endif // !PRINT_H

