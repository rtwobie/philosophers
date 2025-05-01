/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:48:42 by rha-le            #+#    #+#             */
/*   Updated: 2025/05/01 17:17:05 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOG_H
# define LOG_H

# include "structs.h"

//******************* STATUS MESSAGES *******************//
# define DIE "died"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define FORK "has taken a fork"
# define DEBUG_FORK_R "has taken the right fork"
# define DEBUG_FORK_L "has taken the left fork"

//******************* ERROR MESSAGES *******************//
# define WRONG_NUM_OF_ARG_MSG "Wrong amount of arguments! Expected: 4"
# define INVALID_PHILO_SIZE_MSG "Invalid number of Philosophers!"
# define INVALID_DIE_TIME_MSG "Invalid time_to_die!"
# define INVALID_EAT_TIME_MSG "Invalid time_to_eat!"
# define INVALID_SLEEP_TIME_MSG "Invalid time_to_sleep!"
# define ERR_INIT_FORKS_MSG "Failed to initialize forks!"
# define ERR_INIT_MUTEX_MSG "Failed to initialize mutex!"

void	log_msg(char *msg);
int		log_philo(uint64_t timestamp, t_mutex *log_mutex, unsigned int id, char *status);

#endif // !LOG_H
