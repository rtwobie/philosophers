/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwobie <student@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 20:37:49 by rtwobie           #+#    #+#             */
/*   Updated: 2025/10/10 21:57:12 by rtwobie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <errno.h>
#include <stdlib.h>

#include "strtol.h"

static int	_num(int c)
{
	int	num;

	num = 0;
	if (ft_isdigit(c))
		num = c - '0';
	else if (ft_isupper(c))
		num = c - 55;
	else if (ft_islower(c))
		num = c - 87;
	return (num);
}

static int	_signed(const char **nptr, int base)
{
	int	sign;

	sign = 1;
	if (**nptr == '+' || **nptr == '-')
	{
		if (**nptr == '-')
			sign = -1;
		++(*nptr);
	}
	if (base == 0 || base == 16)
		if (!ft_strncmp(*nptr, "0x", 2) || !ft_strncmp(*nptr, "0X", 2))
			*nptr += 2;
	return (sign);
}

static int	_check_erange(int sign, int num, int c, int base)
{
	if (sign == 1 && (num > INT_MAX / base
			|| (num == INT_MAX / base && _num(c) > INT_MAX % base)))
	{
		errno = ERANGE;
		return (INT_MAX);
	}
	else if (sign == -1 && (num > INT_MAX / base
			|| (num == INT_MAX / base && _num(c) > (INT_MAX % base + 1))))
	{
		errno = ERANGE;
		return (INT_MIN);
	}
	return (num);
}

static int	_erange(char *current_ptr, char **endptr, int erange)
{
	if (endptr)
		*endptr = current_ptr;
	(void)erange;
	return (-1);
}

int	ft_strtoi(const char *nptr, char **endptr, int base)
{
	size_t	i;
	int		num;
	int		sign;
	int		erange;

	if (endptr)
		*endptr = (char *)(nptr);
	if (base > 36 || base == 1)
		return (errno = EINVAL, -1);
	while (ft_isspace(*nptr))
		++nptr;
	sign = _signed(&nptr, base);
	num = 0;
	i = 0;
	while (ft_isalnum(nptr[i]) && _num(nptr[i]) < base)
	{
		erange = _check_erange(sign, num, nptr[i], base);
		if (errno == ERANGE && (erange == INT_MAX || erange == INT_MIN))
			return (_erange((char *)(nptr + i), endptr, erange));
		num = (num * base) + _num(nptr[i]);
		++i;
	}
	if (endptr && i != 0)
		*endptr = (char *)(nptr + i);
	return (num * sign);
}
