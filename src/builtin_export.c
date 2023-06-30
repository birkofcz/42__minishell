/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 14:22:34 by sbenes            #+#    #+#             */
/*   Updated: 2023/06/30 16:16:48 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* 
FT_REWRITE - rewrite the envvar on found index (found by ft_checkforexisting)
 */
void	ft_rewrite(int index, char *var)
{
	free(environ[index]);
	environ[index] = ft_strdup(var);
}

void	ft_add(char *var)
{
	char	**new_environ;
	char	*new_var;
	int		size;
	int		i;

	size = 0;
	i = -1;
	new_var = ft_strdup(var);
	while (environ[size] != NULL)
		size++;
	new_environ = malloc((size + 2) * sizeof(char *));
	while (++i < size)
		new_environ[i] = ft_strdup(environ[i]);
	new_environ[size] = new_var;
	new_environ[size + 1] = NULL;
	free_split(environ);
	environ = new_environ;
}

void	ft_export(char **words)
{
	char	**split;
	int		i;
	int		existing_index;
	char	*arg;

	i = 1;
	while (words[i] != NULL)
	{
		if ((ft_checkarg(words[i])) != NULL)
		{
			split = ft_split(words[i], '=');
			existing_index = ft_checkforexisting(split[0]);
			arg = ft_checkarg(words[i]);
			if (existing_index != -1)
				ft_rewrite(existing_index, arg);
			else
				ft_add(arg);
			free_split(split);
			free(arg);
		}
		i++;
	}
	exit(0);
}

int	ft_export_nonfork(char **words)
{
	char	**split;
	int		i;
	int		existing_index;
	char	*arg;

	i = 1;
	while (words[i] != NULL)
	{
		if ((ft_checkarg(words[i])) != NULL)
		{
			split = ft_split(words[i], '=');
			existing_index = ft_checkforexisting(split[0]);
			arg = ft_checkarg(words[i]);
			if (existing_index != -1)
				ft_rewrite(existing_index, arg);
			else
				ft_add(arg);
			free_split(split);
			free(arg);
		}
		i++;
	}
	return (0);
}
