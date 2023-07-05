/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd_pwd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 15:21:02 by tkajanek          #+#    #+#             */
/*   Updated: 2023/07/05 17:08:26 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_pwd_fork(char **args)
{
	char cwd[MAX_PATH_LENGTH];
	(void) args;
	if (getcwd(cwd, MAX_PATH_LENGTH) != NULL) // error managment{
		printf("%s\n", cwd);
	exit(0);
}

int	ft_pwd_nonfork(char **args)
{
	char cwd[MAX_PATH_LENGTH];
	(void) args;
	if (getcwd(cwd, MAX_PATH_LENGTH) != NULL) // error managment{
		printf("%s\n", cwd);
	return(0);
}

char *custom_strjoin_env(char *var, char *value)
{
	char *temp_value;
	int	i;
	int j;
	int	len;

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
	printf("env variable = %s\n", value);
	free(temp_value);
	return(value);
}

void	ft_cd_fork(char **args)
{
	int	argument_count;
	char old_pwd[MAX_PATH_LENGTH];
	char cwd[MAX_PATH_LENGTH];

	argument_count = commands_counting(args);
	if (argument_count > 2)
	{
		printf("cd: too many arguments\n");
		exit (256);
	}
	else
	{
		getcwd(old_pwd, MAX_PATH_LENGTH);
		if (argument_count == 1)
			chdir(getenv("HOME"));
		else if (chdir(args[1]) == -1)
		{
        	printf("cd: %s: no such file or directory.\n", args[1]);
			exit(256);
    	}
		getcwd(cwd, MAX_PATH_LENGTH);
		ft_rewrite(ft_checkforexisting("PWD"), custom_strjoin_env("PWD", cwd));
		ft_rewrite(ft_checkforexisting("OLDPWD"), custom_strjoin_env("OLDPWD",old_pwd));
	}
	exit(0);
}

int	ft_cd_nonfork(char **args)
{
	int	argument_count;
	char old_pwd[MAX_PATH_LENGTH];
	char cwd[MAX_PATH_LENGTH];

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
		else if (chdir(args[1]) == -1)
		{
        	printf("cd: %s: no such file or directory.\n", args[1]);
			return(256);
    	}
		getcwd(cwd, MAX_PATH_LENGTH);
		ft_rewrite(ft_checkforexisting("PWD"), custom_strjoin_env("PWD", cwd));
		ft_rewrite(ft_checkforexisting("OLDPWD"), custom_strjoin_env("OLDPWD",old_pwd));
	}
	return(0);
}