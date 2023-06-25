/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_builtin_nonforked.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 14:11:35 by tkajanek          #+#    #+#             */
/*   Updated: 2023/06/25 16:05:25 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void builtin_nonfork_redirection(char *command, char **args)
{
	if (ft_strncmp(command, "echo", ft_strlen("echo") + 1) == 0)
    	ft_echo_nonfork(args);
	if (ft_strncmp(command, "pwd", ft_strlen("pwd") + 1) == 0) // $blabla pwd -> by melo fungovat
		ft_pwd_nonfork(args);
	else if (ft_strncmp(command, "cd", ft_strlen("cd") + 1) == 0)
		ft_cd_nonfork(args);
	else if (ft_strncmp(command, "env", ft_strlen("env") + 1) == 0)
		ft_env_nonfork(args);
	else if (ft_strncmp(command, "export", ft_strlen("export") + 1) == 0)
		ft_export_nonfork(args);
	else if (ft_strncmp(command, "unset", ft_strlen("unset") + 1) == 0)
		ft_unset_nonfork(args);
	else if (ft_strncmp(command, "exit", ft_strlen("exit") + 1) == 0)
		return ;
}