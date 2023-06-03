/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd_pwd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 15:21:02 by tkajanek          #+#    #+#             */
/*   Updated: 2023/06/03 18:15:29 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_pwd(t_env *env, int words_count)
{
	if (words_count == 1)
		printf("%s\n", env->pwd);
	else
		printf("pwd: too many arguments\n");
}
/*
	if there is only cd command -> change directory to home,
	else if there is + 1 argument -> change directory to desired destination.
	3+ -> error;
	*/
void	ft_cd(t_env *env, char **arg, int words_count)
{
	char cwd[MAX_PATH_LENGTH];

	if (words_count > 3)
		printf("cd: too many arguments\n");
	else if (words_count == 3)
		printf("OPRAVIT cd: no such file or directory: %s\n", arg[1]); //zjistit co dela cd s 2 argumenty
	else if (words_count < 3)
	{
		if (words_count == 1)
			chdir(env->home);//error managment
		else if (chdir(arg[1]) == -1)
		{
        	printf("cd: no such file or directory: %s.\n", arg[1]);
    	}
		/* update the PWD */
   		if (getcwd(cwd, MAX_PATH_LENGTH) != NULL) // error managment
		{
			ft_strlcpy(env->pwd, cwd, ft_strlen(cwd) + 1); //nealokuje
		}
	}
}