/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:42:13 by rha-le            #+#    #+#             */
/*   Updated: 2025/04/29 19:34:46 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <pthread.h>
# include <stdbool.h>
# include <stdint.h>

typedef pthread_mutex_t t_mutex;

typedef struct s_schedule
{
	uint64_t	start_time;
	uint64_t	_to_die;
	uint64_t	_to_eat;
	uint64_t	_to_sleep;
	uint64_t	_to_think;
}	t_schedule;

typedef struct s_philo
{
	int				id;
	pthread_t		tid;
	uint64_t		last_meal_in_ms;
	t_mutex			*right_fork;
	t_mutex			*left_fork;
	t_schedule		*time;
	struct s_table	*table;
}	t_philo;

typedef struct s_table
{
	bool			all_threads_born;
	unsigned int	philo_count;
	t_philo			*philo;
	t_mutex			*fork;
	t_mutex			print;
	t_schedule		time;
	pthread_t		monitor;
}	t_table;

#endif //!STRUCTS_H
