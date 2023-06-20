/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:44:40 by sbenes            #+#    #+#             */
/*   Updated: 2023/06/20 17:23:16 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_is_builtin(char *command)
{
	//otestuje, zda je command builtin.
	if (ft_strncmp(command, "echo", ft_strlen("echo") + 1) == 0)
		return (0);
	else if (ft_strncmp(command, "pwd", ft_strlen("pwd") + 1) == 0)
		return (0);
	else if (ft_strncmp(command, "cd", ft_strlen("cd") + 1) == 0)
		return (0);
	else if (ft_strncmp(command, "env", ft_strlen("env") + 1) == 0)
		return (0);
	else if (ft_strncmp(command, "export", ft_strlen("export") + 1) == 0)
		return (0);
	else if (ft_strncmp(command, "unset", ft_strlen("unset") + 1) == 0)
		return (0);
	else if (ft_strncmp(command, "exit", ft_strlen("exit") + 1) == 0)
		return (0);
	else
		return (1);
}

int	ft_is_pathexec(char *command)
{
	//otestuje, zda jde o command s cestou
	int	test;

	test = access(command, X_OK);
	if (test == 0)
		return (0);
	else
		return (1);
}

int	ft_is_nopathexec(char *command);
{
	
}

char	*ft_return_path(char *command);
//vraci cestu ke commandu, kterou nasel.

void	ft_command_check(char **commands)
/* 
vezme command table, projde commandy, vrati upravy command table:
pokud neni builtin a pokud to neni executable path, zacne to hledat v $PATH.
Pokud najde, upravi command table - na spravne misto zapise nalezeny executable jako cestu (pouzitelnou pro execve).
Predpokladame, ze v command table uz jsou je executable.
	int	i;

	i = 0;
	while (data->commands[i] != NULL)
	{

	}
 */
