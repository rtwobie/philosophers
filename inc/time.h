/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rha-le <rha-le@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 00:17:51 by rha-le            #+#    #+#             */
/*   Updated: 2025/05/01 00:34:46 by rha-le           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIME_H
# define TIME_H

# include <stdint.h>

uint64_t	get_time(void);
uint64_t	get_timestamp(uint64_t start_time);

#endif // !TIME_H
