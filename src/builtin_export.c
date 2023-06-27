/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 14:22:34 by sbenes            #+#    #+#             */
/*   Updated: 2023/06/26 17:43:49 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


int	ft_checkforexisting(char *var)
{
	int		i;
	char	**split;

	i = 0;
	while (environ[i] != NULL)
	{
		split = ft_split(environ[i], '=');
		if (ft_strncmp(split[0], var, ft_strlen(var)) == 0)
		{
			free(split[0]);
			free(split);
			return (i);
		}
		else
		{
			free(split[0]);
			free(split);
		}
		i++;
	}
	return (-1);
}

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
	//Musime tohle nekde vypustit  - probehl malloc. Mozna free(environ) pri exitu?make
	environ = new_environ;
}

char	*ft_checkarg(char *arg)
{
	int		i;
	int		flag;
	char	**split;

/* FREE SPLIT!!!! POMOCI TOMASOVI FUNKCE FREEARG */
	i = 0;
	flag = 0;
	split = ft_split(arg, '=');
	if (!ft_isalpha(arg[i]))
		return (printf("export: error %s\n", split[0]), free(split[0]),
			free(split), NULL);
	while (arg[i] != '\0')
	{
		if (arg[i] == '=')
			flag++;
		i++;
	}
	i = 0;
	while (arg[i] != '=')
	{
		if ((!ft_isalnum(arg[i])) && arg[i] != '_')
			return (printf("export: error %s\n", split[0]), NULL);
		i++;
	}
	if (flag == 0)
		return (free(split[0]), free(split), NULL);
	else if (flag == 1 && arg[0] != '=' && arg[i - 1] != '=')
		return (free(split[0]), free(split), arg);
	else
		return (free(split[0]), free(split), NULL);
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
			free(split[0]);
			free(split);
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
			free(split[0]);
			free(split);
		}
		i++;
	}
	return (0);
}
