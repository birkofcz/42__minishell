/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_binary2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:53:38 by sbenes            #+#    #+#             */
/*   Updated: 2023/06/16 16:18:28 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_exe_exe(char *command, int command_group, t_data *data)
{
	int		pid;
	int		counter;
	char	**args;
	char	**args_execve;

	counter = 0;
	args = data->args[command_group];
	while (args[counter++])
		;
	args_execve = malloc((counter + 2) * sizeof(char *));
	counter = 0;
	args_execve[0] = command;
	printf("TEST1: args_execve[0]: %s\n", command);
	while (args[counter])
	{
		printf("args[%d][%d]: %s\n", command_group, counter, args[counter]);
		args_execve[counter + 1] = ft_strdup(args[counter]);
		counter++;
	}
	args_execve[counter + 1] = NULL;
	pid = fork();
	if (pid < 0)
		return (1);
	if (pid == 0)
	{
		execve(command, args_execve, environ);
		exit(1);
	}
	else
		wait(NULL);
	while (counter >= 0)
		free(args_execve[counter--]);
	return (0);
}

int	ft_exe_builtin(char *command, int command_group, t_data *data, int fd)
{
	if (ft_strncmp(command, "echo", ft_strlen("echo") + 1) == 0)
		ft_echo(data->args[command_group], fd);
/* 	else if (ft_strncmp(command, "pwd", ft_strlen("pwd") + 1) == 0) // $blabla pwd -> by melo fungovat
		ft_pwd(enviro, data->args[command_group]_count);
	else if (ft_strncmp(command, "cd", ft_strlen("cd") + 1) == 0)
		ft_cd(env, data->args[command_group], data->args[command_group]_count); */
	else if (ft_strncmp(command, "env", ft_strlen("env") + 1) == 0)
		ft_env(1);
	else if (ft_strncmp(command, "export", ft_strlen("export") + 1) == 0)
		ft_export(data->args[command_group]);
	else if (ft_strncmp(command, "unset", ft_strlen("unset") + 1) == 0)
		ft_unset(data->args[command_group]);
	else if (ft_strncmp(command, "clear", ft_strlen(command)) == 0)
		printf("\033[2J\033[1;1H");
	else if (ft_strncmp(command, "exit", ft_strlen("exit") + 1) == 0)
		return (free_args(data->args[command_group]), 0);
	return (0);
}


void	ft_exec_simple(char *command, int command_group, t_data *data)
{
	int	is_exe;

	is_exe = access(command, X_OK);
	if (is_exe == 0)
		ft_exe_exe(command, command_group, data);
	else if (is_exe != 0)
		ft_exe_builtin(command, command_group, data, 1);
}

void	ft_exe_redir(char *command, int command_group, t_data *data)
{
	int	i;

	i = 0;
	if (data->outfile[i] != -1)
	{
		printf("TEST: outfile[0] = %d\n", data->outfile[i]);
		ft_exe_builtin(command, command_group, data, data->outfile[i]);
	}
}


void	ft_exec_multiple(char *command, int command_group, t_data *data)
{
	int	i;

	i = 0;
	while (data->redirs[i])
	{
		printf("TEST1: we are in mutiple\n");
		if (ft_strchr(data->redirs[i], '>') != NULL)
			ft_exe_redir(command, command_group, data);

	}
}

void	exe(t_data *data)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	/// promzslet, jak to tady udelat - redirs mohou byt kdekoliv, muze jich byt libovolny pocet....
	while (data->commands[count])
		count++;
	printf("TEST1: number of commands: %d\n", count);
	if (count == 1 && !data->redirs[0])
		ft_exec_simple(data->commands[i], i, data);
	else if (count == 1 && data->redirs[0])
	{
		while (data->commands[i])
			ft_exec_multiple(data->commands[i], i, data);
	}

}
