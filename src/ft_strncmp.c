/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtwobie <student@42>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 21:00:25 by rtwobie           #+#    #+#             */
/*   Updated: 2025/10/10 21:00:29 by rtwobie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

/** Compares the first n bytes of two strings.
 *
 *	@param s1:	The string to compare.
 *	@param s2:	The string to compare against.
 *	@param n:	The number of bytes to compare.
 *
 *	@returns:	0 if equal; A negative value if s1 is less than s2;
 *				A positive value if s1 is greater than s2.
 */
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*us1;
	unsigned char	*us2;

	if (!n)
		return (0);
	us1 = (unsigned char *)s1;
	us2 = (unsigned char *)s2;
	while (*us1 && *us2 && *us1 == *us2 && --n)
	{
		++us1;
		++us2;
	}
	return (*us1 - *us2);
}
