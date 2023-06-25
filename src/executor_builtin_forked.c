/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_builtin_forked.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:28:16 by tkajanek          #+#    #+#             */
/*   Updated: 2023/06/25 14:10:43 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	builtin_redirection(char *command, char **args)
{
	//if (ft_strncmp(command, "echo", ft_strlen("echo") + 1) == 0)
    //	ft_echo(args);
	if (ft_strncmp(command, "pwd", ft_strlen("pwd") + 1) == 0) // $blabla pwd -> by melo fungovat
		ft_pwd(args);
	else if (ft_strncmp(command, "cd", ft_strlen("cd") + 1) == 0)
		ft_cd(args);
	//else if (ft_strncmp(command, "env", ft_strlen("env") + 1) == 0)
	//	ft_env(args);
	//else if (ft_strncmp(command, "export", ft_strlen("export") + 1) == 0)
	//	ft_export(args);
	//else if (ft_strncmp(command, "unset", ft_strlen("unset") + 1) == 0)
	//	ft_unset(args);
	else if (ft_strncmp(command, "exit", ft_strlen("exit") + 1) == 0)
		return ;
}