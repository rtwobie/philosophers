/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:42:13 by rha-le            #+#    #+#             */
/*   Updated: 2025/04/28 20:38:48 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <pthread.h>
# include <stdbool.h>
# include <stdint.h>

typedef struct s_schedule
{
	uint64_t	start_time;
	uint64_t	_to_die;
	uint64_t	_to_eat;
	uint64_t	_to_sleep;
}	t_schedule;

typedef struct s_philo
{
	int				id;
	pthread_t		tid;
	bool			full;
	uint64_t		last_meal_in_ms;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	t_schedule		*time;
	bool			*all_threads_born;
}	t_philo;

typedef struct s_table
{
	bool			all_threads_born;
	unsigned int	philo_count;
	t_philo			*philo;
	pthread_mutex_t	*fork;
	t_schedule		time;
}	t_table;

#endif //!STRUCTS_H
