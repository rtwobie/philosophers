/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtol.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwobie <student@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 20:54:11 by rtwobie           #+#    #+#             */
/*   Updated: 2025/10/10 21:54:45 by rtwobie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRTOL_H
# define STRTOL_H

# include <stddef.h>

int		ft_isalnum(int c);
int		ft_isdigit(int c);
int		ft_islower(int c);
int		ft_isspace(int c);
int		ft_isupper(int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strtoi(const char *nptr, char **endptr, int base);

#endif // !STRTOL_H
