/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd_pwd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 15:21:02 by tkajanek          #+#    #+#             */
/*   Updated: 2023/06/26 17:49:30 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_pwd(char **args)
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

void	ft_cd(char **args)
{
	int	argument_count;
	char old_pwd[MAX_PATH_LENGTH];
	char cwd[MAX_PATH_LENGTH];

	argument_count = commands_counting(args);
	if (argument_count > 2)
		printf("cd: too many arguments\n");
	else
	{
		getcwd(old_pwd, MAX_PATH_LENGTH);
		write(1, "old pwd: ", 10);
		write(1, old_pwd, strlen(old_pwd));
		write(1, "\n", 1);
		if (argument_count == 1)
			chdir(getenv("HOME"));//error managment
		else if (chdir(args[1]) == -1)
		{
        	printf("cd: %s:no such file or directory.\n", args[1]);
			exit(1);
    	}
		getcwd(cwd, MAX_PATH_LENGTH);
		write(1, "cwd: ", 6);
		write(1, cwd, strlen(cwd));
		write(1, "\n", 1);
		ft_rewrite(ft_checkforexisting("PWD"), cwd);
		ft_rewrite(ft_checkforexisting("OLDPWD"), old_pwd);
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
		printf("cd: too many arguments\n");
	else
	{
		getcwd(old_pwd, MAX_PATH_LENGTH);
		write(1, "old pwd: ", 10);
		write(1, old_pwd, strlen(old_pwd));
		write(1, "\n", 1);
		if (argument_count == 1)
			chdir(getenv("HOME"));//error managment
		else if (chdir(args[1]) == -1)
		{
        	printf("cd: %s:no such file or directory.\n", args[1]);
			return(1);
    	}
		getcwd(cwd, MAX_PATH_LENGTH);
		write(1, "cwd: ", 6);
		write(1, cwd, strlen(cwd));
		write(1, "\n", 1);
		ft_rewrite(ft_checkforexisting("PWD"), cwd);
		ft_rewrite(ft_checkforexisting("OLDPWD"), old_pwd);
		//PWD=cwd pomoci strjoin
	}
	return(0);
}