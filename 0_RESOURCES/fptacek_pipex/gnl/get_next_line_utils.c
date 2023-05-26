/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fptacek <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:30:18 by fptacek           #+#    #+#             */
/*   Updated: 2023/03/22 15:30:21 by fptacek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int		i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*res;

	i = 0;
	j = 0;
	res = (char *)malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(s2)) + 1));
	if (res == NULL)
		return (NULL);
	while (s1 && i < (size_t) ft_strlen(s1))
	{
		res[i] = s1[i];
		i++;
	}
	while (s2 && i < (size_t)(ft_strlen(s1) + ft_strlen(s2)))
		res[i++] = s2[j++];
	res[i] = '\0';
	return (res);
}

char	*ft_new_str(char *static_ptr, char n)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	while (static_ptr[i] != n)
	{
		if (static_ptr[i] == '\0')
			return (0);
		i++;
	}
	if (!static_ptr[i] || (static_ptr[i] == n && static_ptr[i + 1] == '\0'))
		return (NULL);
	new = (char *)malloc(sizeof(char) * ((ft_strlen(static_ptr) - i) + 1));
	if (new == NULL)
		return (NULL);
	i++;
	while (i < ft_strlen(static_ptr))
		new[j++] = static_ptr[i++];
	new[j] = '\0';
	return (new);
}
