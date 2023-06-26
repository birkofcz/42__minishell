/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd_pwd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 15:21:02 by tkajanek          #+#    #+#             */
/*   Updated: 2023/06/25 17:13:11 by tkajanek         ###   ########.fr       */
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
	//char cwd[MAX_PATH_LENGTH];
	int	argument_count;

	argument_count = commands_counting(args);
	if (argument_count > 2)
		printf("cd: too many arguments\n");
	else
	{
		if (argument_count == 1)
			chdir(getenv("HOME"));//error managment
		else if (chdir(args[1]) == -1)
		{
        	printf("cd: %s:no such file or directory.\n", args[1]);
    	}
   		/*if (getcwd(cwd, MAX_PATH_LENGTH) != NULL) // error managment
		{
			ft_strlcpy(env->pwd, cwd, ft_strlen(cwd) + 1); //nealokuje
		}*/
	}
	exit(0);
}

int	ft_cd_nonfork(char **args)
{
	//char cwd[MAX_PATH_LENGTH];
	int	argument_count;

	argument_count = commands_counting(args);
	if (argument_count > 2)
		printf("cd: too many arguments\n");
	else
	{
		if (argument_count == 1)
			chdir(getenv("HOME"));//error managment
		else if (chdir(args[1]) == -1)
		{
        	printf("cd: %s:no such file or directory.\n", args[1]);
    	}
   		/*if (getcwd(cwd, MAX_PATH_LENGTH) != NULL) // error managment
		{
			ft_strlcpy(env->pwd, cwd, ft_strlen(cwd) + 1); //nealokuje
		}*/
	}
	return(0);
}