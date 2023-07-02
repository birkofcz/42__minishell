/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 15:11:12 by tkajanek          #+#    #+#             */
/*   Updated: 2023/07/02 20:54:50 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	execute(char *command, int position, t_data *data)
{
	if (ft_is_builtin(command))
		builtin_redirection_fork(command,data->args[position], data);
	else
	{
		write(2, "executing command: ", 19);
		write(2, command, ft_strlen(command));
		write(2, "\n", 1);
		if (execve(command, data->args[position], environ) == -1)
		{
			write(2, "[TS]minishell: Command not found: ", 35);
			write(2, command, ft_strlen(command));
			write(2, "\n", 1);
			g_exit = 127 << 8;
		}
	}
}

void	child(char *command, int position, t_data *data)
{
	int	pid;
	int	fd[2];

	pipe(fd);
	/*if (pipe(fd) == -1)
		error();*/
	pid = fork();
	/*if (pid == -1)
		error();*/
	
	if (pid == 0)
	{
		close(fd[0]); //read end
		dup2(fd[1], STDOUT_FILENO);
		execute(command, position, data);
	}
	else
	{
		close(fd[1]); //write end
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, &g_exit, 0);
	}
}

void	ft_executor(t_data *data)
{
	int		i;
	pid_t	pid;
	int saved_stdin;
	int saved_stdout;

	i = 0;
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (data->infile != - 1)
	{
		printf("we are inside infile redirection\n");
		dup2(data->infile, STDIN_FILENO);
		close(data->infile);
	}
	else if (data->delimiter != NULL)
		ft_heredoc(data->delimiter);
	while (i < data->last_command)
	{
		printf("we are inside child loop\n");
		access(data->commands[i], X_OK);
		child(data->commands[i], i, data); // v tuto chvili rozhodnout zda-li exe nebo builtin
		i++;
	}
	i = 0;
	if (data->outfile != -1)
	{
		printf("we are inside outfile redirection\n");
		dup2(data->outfile, STDOUT_FILENO);
		close(data->outfile);
	}
	// v tuto chvili rozhodnout zda-li exe nebo builtin
	if (ft_is_builtin(data->commands[data->last_command]))
	{
		builtin_nonfork_redirection(data->commands[data->last_command], data->args[data->last_command], data);
	}
	else
	{
		pid = fork();
		if (pid == -1)
	{
			// Handle fork error
			perror("fork");
			exit(1);
	}
	else if (pid == 0)
		execute(data->commands[data->last_command], data->last_command, data);
	else
		waitpid(pid, &g_exit, 0);
	}
	dup2(saved_stdout,STDOUT_FILENO);
	dup2(saved_stdin,STDIN_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	free_command_table(data);
	printf("exit: %d\n", g_exit);
}
