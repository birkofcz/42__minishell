/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd_pwd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 15:21:02 by tkajanek          #+#    #+#             */
/*   Updated: 2023/05/28 19:31:42 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_pwd(t_env *env)
{
	printf("%s\n", env->pwd);
}

void	ft_cd(t_env *env, char **arg)
{
	//cd -> go home, getent ("HOME")
	char cwd[MAX_PATH_LENGTH]; // current working directory

	printf("arg[0] = %s, arg[1] = %s\n",arg[0],arg[1] );
	if (chdir(arg[1]) == 0)
	{
        printf("Directory changed successfully.\n");
		//replace with proper error managment
    }
    if (getcwd(cwd, MAX_PATH_LENGTH) != NULL)
	{
		ft_strlcpy(env->pwd, cwd, ft_strlen(cwd) + 1); //nealokuje
		printf("\n%s\n", env->pwd); //test
	}
}