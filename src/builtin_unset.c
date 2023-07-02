/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 13:45:53 by sbenes            #+#    #+#             */
/*   Updated: 2023/07/02 20:01:00 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* Unset - deleting the env variable */
/*  */
void	ft_delenv(int index)
{
	char	**new_environ;
	int		size;
	int		i;
	int		j;

	size = 0;
	i = 0;
	j = 0;
	while (environ[size] != NULL)
		size++;
	new_environ = malloc((size) * sizeof(char *));
	while (i < size)
	{
		if (i != index)
		{
			new_environ[j] = ft_strdup(environ[i]);
			j++;
		} 
		i++;
	}
	new_environ[j] = NULL;
	free_split(environ);
	environ = new_environ;
}

void	ft_unset_fork(char **words)
{
	int	i;
	int	index;

	i = 1;
	while (words[i] != NULL)
	{
		index = ft_checkforexisting(words[i]);
		if (index != -1)
			ft_delenv(index);
		i++;
	}
	exit(0);
}

int	ft_unset_nonfork(char **words)
{
	int	i;
	int	index;

	i = 1;
	while (words[i] != NULL)
	{
		index = ft_checkforexisting(words[i]);
		if (index != -1)
			ft_delenv(index);
		i++;
	}
	return (0);
}