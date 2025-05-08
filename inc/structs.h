/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:11:19 by rha-le            #+#    #+#             */
/*   Updated: 2025/05/02 16:46:44 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

#include <stdio.h> // TODO: delete after!

# include <pthread.h>
# include <stdbool.h>

typedef pthread_mutex_t	t_mutex;

typedef struct s_table
{
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_think;
	uint64_t		start_time;
	bool			in_sync;
	unsigned int	dead;
	t_mutex			in_sync_mutex;
	t_mutex			dead_mutex;
	t_mutex			last_meal_mutex;
	t_mutex			log_mutex;
	struct s_fork	*fork;
}		t_table;

typedef struct s_fork
{
	unsigned int	id;
	t_mutex			mutex;
}		t_fork;

typedef struct s_philo
{
	unsigned int	id;
	pthread_t		thread;
	t_table			*table;
	t_fork			*right_fork;
	t_fork			*left_fork;
	uint64_t		time_of_last_meal;
}		t_philo;

#endif //!STRUCTS_H
