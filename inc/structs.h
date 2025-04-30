/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 14:11:19 by rha-le            #+#    #+#             */
/*   Updated: 2025/04/30 17:45:45 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <pthread.h>
# include <stdbool.h>

typedef pthread_mutex_t	t_mutex;

typedef struct s_table
{
	int				philo_count;
	int				start_time;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_think;
	bool			end_dining;
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
	pthread_t		*philo;
	t_table			*table;
	t_fork			*right_fork;
	t_fork			*left_fork;
}		t_philo;

#endif //!STRUCTS_H
