/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fptacek <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 17:19:32 by fptacek           #+#    #+#             */
/*   Updated: 2023/01/25 19:41:17 by fptacek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>
#include "pipex.h"

int	wordcount(char const *s, char c)
{
	int	dl;
	int	i;

	dl = 0;
	i = 0;
	while (s[i])
	{
		if (s[++i] == c && s[i - 1] != c)
			dl++;
	}
	return (dl + 1);
}

char	**ft_mysplit(char **split, char const *s, char c)
{
	int		i;
	int		j;
	int		sub;

	i = 0;
	j = 0;
	sub = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			while (s[i] && s[i] != c)
			{
				j++;
				i++;
			}
			split[sub] = ft_substr(s, i - j, j);
			sub++;
			j = 0;
		}
	}
	split[sub] = NULL;
	return (split);
}

char	**ft_split(char const *s, char c)
{
	char	**split;

	split = (char **)malloc(sizeof(char *) * (wordcount(s, c) + 1));
	if (split == NULL)
		return (NULL);
	return (ft_mysplit(split, s, c));
}
