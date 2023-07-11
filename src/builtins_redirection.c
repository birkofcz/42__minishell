/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_redirection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:28:16 by tkajanek          #+#    #+#             */
/*   Updated: 2023/07/11 14:59:35 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	builtin_redirection_fork(char *command, char **args, t_data	*data)
{
	if (ft_strncmp(command, "echo", ft_strlen("echo") + 1) == 0)
		ft_echo_fork(args, data);
	else if (ft_strncmp(command, "pwd", ft_strlen("pwd") + 1) == 0)
		ft_pwd_fork(args, data);
	else if (ft_strncmp(command, "cd", ft_strlen("cd") + 1) == 0)
		ft_cd_fork(args, data);
	else if (ft_strncmp(command, "env", ft_strlen("env") + 1) == 0)
		ft_env_fork(data);
	else if (ft_strncmp(command, "export", ft_strlen("export") + 1) == 0)
		ft_export_fork(args, data);
	else if (ft_strncmp(command, "unset", ft_strlen("unset") + 1) == 0)
		ft_unset_fork(args, data);
	else if (ft_strncmp(command, "exit", ft_strlen("exit") + 1) == 0)
	{
		ft_exit(data);
		exit(1);
	}
}

void	builtin_nonfork_redirection(char *command, char **args, t_data	*data)
{
	if (ft_strncmp(command, "echo", ft_strlen("echo") + 1) == 0)
		g_exit = ft_echo_nonfork(args);
	else if (ft_strncmp(command, "pwd", ft_strlen("pwd") + 1) == 0)
		g_exit = ft_pwd_nonfork(args);
	else if (ft_strncmp(command, "cd", ft_strlen("cd") + 1) == 0)
		g_exit = ft_cd_nonfork(args, data);
	else if (ft_strncmp(command, "env", ft_strlen("env") + 1) == 0)
		g_exit = ft_env_nonfork();
	else if (ft_strncmp(command, "export", ft_strlen("export") + 1) == 0)
		g_exit = ft_export_nonfork(args, data);
	else if (ft_strncmp(command, "unset", ft_strlen("unset") + 1) == 0)
		g_exit = ft_unset_nonfork(args, data);
	else if (ft_strncmp(command, "exit", ft_strlen("exit") + 1) == 0)
		ft_exit(data);
}
