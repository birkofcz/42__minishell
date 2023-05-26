/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fptacek <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 18:24:11 by fptacek           #+#    #+#             */
/*   Updated: 2023/02/01 21:07:36 by fptacek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*p;
	unsigned char	*d;

	i = 0;
	p = (unsigned char *)s1;
	d = (unsigned char *)s2;
	while (p[i] && d[i] && (i < n))
	{
		if (p[i] != d[i])
			return (p[i] - d[i]);
		i++;
	}
	if (i == n)
		return (0);
	return (p[i] - d[i]);
}
