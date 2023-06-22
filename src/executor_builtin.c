/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:28:16 by tkajanek          #+#    #+#             */
/*   Updated: 2023/06/22 16:32:37 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	builtin_redirection(char *command, char **args)
{
	if (ft_strncmp(command, "echo", ft_strlen("echo") + 1) == 0)
    	ft_echo(args);
/* 	else if (ft_strncmp(command, "pwd", ft_strlen("pwd") + 1) == 0) // $blabla pwd -> by melo fungovat
		ft_pwd(args);
	else if (ft_strncmp(command, "cd", ft_strlen("cd") + 1) == 0)
		ft_cd(args); */
	else if (ft_strncmp(command, "env", ft_strlen("env") + 1) == 0)
		ft_env();
	else if (ft_strncmp(command, "export", ft_strlen("export") + 1) == 0)
		ft_export(args);
	else if (ft_strncmp(command, "unset", ft_strlen("unset") + 1) == 0)
		ft_unset(args);
	else if (ft_strncmp(command, "exit", ft_strlen("exit") + 1) == 0)
		return ;
}