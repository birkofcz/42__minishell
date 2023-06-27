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

/* 
FT_CHECKFOREXISTING - loops through minishell env, check if var exists there.
If so, returs index. Else returns erorr.
 */
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
			free_split(split);
			return (i);
		}
		else
			free_split(split);
		i++;
	}
	return (-1);
}

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

/* 
FT_CHECKARG - checks the argument format
 */
char	*ft_checkarg(char *arg)
{
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	if (!ft_isalpha(arg[i]))
		return (NULL);
	while (arg[i] != '\0')
	{
		if (arg[i] == '=')
			flag++;
		i++;
	}
	i = -1;
	while (arg[++i] != '=')
		if ((!ft_isalnum(arg[i])) && arg[i] != '_')
			return (NULL);
	if (flag == 0)
		return (NULL);
	else if (flag == 1 && arg[0] != '=' && arg[i - 1] != '=')
		return (arg);
	else
		return (NULL);
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
