/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 13:45:53 by sbenes            #+#    #+#             */
/*   Updated: 2023/06/25 16:22:05 by sbenes           ###   ########.fr       */
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

	size = 0;
	i = -1;
	while (environ[size] != NULL)
		size++;
	new_environ = malloc((size) * sizeof(char *));
	free(environ[index]);
	while (++i < size - 1)
		new_environ[i] = ft_strdup(environ[i]);
	new_environ[size + 1] = NULL;
	//Musime tohle nekde vypustit  - probehl malloc. Mozna free(environ) pri exitu?make
	environ = new_environ;
}

void	ft_unset(char **words)
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