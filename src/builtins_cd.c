/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 15:21:02 by tkajanek          #+#    #+#             */
/*   Updated: 2023/07/11 15:55:34 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*join_env(char *var, char *value)
{
	char	*temp_value;
	int		i;
	int		j;
	int		len;

	i = -1;
	j = 0;
	len = ft_strlen(var) + ft_strlen(value) + 1;
	temp_value = ft_strdup(value);
	value[len] = '\0';
	while (++i < len && var[i] != '\0')
		value[i] = var[i];
	value[i++] = '=';
	while (i < len && value[j] != '\0')
		value[i++] = temp_value[j++];
	value[i] = '\0';
	free(temp_value);
	return (value);
}

static void	ft_errorandexit(char *arg, t_data *data)
{
	printf("cd: %s: no such file or directory.\n", arg);
	fork_exit(1, data);
}

void	ft_cd_fork(char **args, t_data * data)
{
	int		argument_count;
	char	old_pwd[MAX_PATH_LENGTH];
	char	cwd[MAX_PATH_LENGTH];

	argument_count = commands_counting(args);
	if (argument_count > 2)
	{
		printf("cd: too many arguments\n");
		fork_exit(1, data);
	}
	else
	{
		getcwd(old_pwd, MAX_PATH_LENGTH);
		if (argument_count == 1)
			chdir(getenv("HOME"));
		else if (args[1][0] == '-')
			chdir(getenv("OLDPWD"));
		else if (chdir(args[1]) == -1)
			ft_errorandexit(args[1], data);
		getcwd(cwd, MAX_PATH_LENGTH);
		ft_rewrite(ft_checkforexisting("PWD"), join_env("PWD", cwd), data);
		ft_rewrite(ft_checkforexisting("OLDPWD"), join_env("OLDPWD", old_pwd), data);
	}
	fork_exit(0, data);
}

int	ft_cd_nonfork(char **args, t_data * data)
{
	int		argument_count;
	char	old_pwd[MAX_PATH_LENGTH];
	char	cwd[MAX_PATH_LENGTH];

	argument_count = commands_counting(args);
	if (argument_count > 2)
	{
		printf("cd: too many arguments\n");
		return (256);
	}
	else
	{
		getcwd(old_pwd, MAX_PATH_LENGTH);
		if (argument_count == 1)
			chdir(getenv("HOME"));
		else if (args[1][0] == '-')
			chdir(getenv("OLDPWD"));
		else if (chdir(args[1]) == -1)
			return (printf("cd: %s: no such file or directory.\n", args[1]),
				256);
		getcwd(cwd, MAX_PATH_LENGTH);
		ft_rewrite(ft_checkforexisting("PWD"), join_env("PWD", cwd), data);
		ft_rewrite(ft_checkforexisting("OLDPWD"), join_env("OLDPWD", old_pwd), data);
	}
	return (0);
}
