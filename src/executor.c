/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 15:11:12 by tkajanek          #+#    #+#             */
/*   Updated: 2023/07/10 15:59:34 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	execute(char *command, int position, t_data *data)
{
	if (ft_is_builtin(command))
		builtin_redirection_fork(command, data->args[position], data);
	else
	{
		if (execve(command, data->args[position], environ) == -1)
		{
			write(2, "[TS]minishell: Command not found: ", 35);
			write(2, command, ft_strlen(command));
			write(2, "\n", 1);
			free_command_table(data);
			free_split(data->minishell_env);
			exit(127);
		}
	}
}

static void	ft_error(void)
{
	perror("fork");
	exit(1);
}

/* 
Read end fd[0]
Write end fd[1]
 */
void	child(char *command, int position, t_data *data)
{
	int	pid;
	int	fd[2];

	pipe(fd);
	if (pipe(fd) == -1)
		ft_error();
	pid = fork();
	if (pid == -1)
		ft_error();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execute(command, position, data);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		waitpid(pid, &g_exit, 0);
	}
}

void	ft_executor(t_data *data)
{
	int		i;
	pid_t	pid;

	i = -1;
	save_restore_std(data, 0);
	set_infile(data);
	while (++i < data->last_command)
		child(data->commands[i], i, data);
	set_outfile(data);
	if (ft_is_builtin(data->commands[data->last_command]))
		builtin_nonfork_redirection(data->commands[data->last_command],
			data->args[data->last_command], data);
	else
	{
		pid = fork();
		if (pid == -1)
			ft_error();
		else if (pid == 0)
			execute(data->commands[data->last_command],
				data->last_command, data);
		else
			waitpid(pid, &g_exit, 0);
	}
	save_restore_std(data, 1);
	free_command_table(data);
}
