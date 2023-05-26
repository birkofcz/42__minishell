/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fptacek <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:57:58 by fptacek           #+#    #+#             */
/*   Updated: 2023/01/20 20:39:56 by fptacek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "pipex.h"

char	*ft_strdup(const char *s)
{
	char	*p;
	int		l;
	int		i;

	i = 0;
	l = ft_strlen(s) + 1;
	p = (char *)malloc(l * sizeof(char));
	if (p != NULL)
	{
		while (s[i])
		{
			p[i] = s[i];
			i++;
		}
		p[i] = '\0';
		return (p);
	}
	return (NULL);
}
