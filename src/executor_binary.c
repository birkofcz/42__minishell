/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_binary.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 15:11:12 by tkajanek          #+#    #+#             */
/*   Updated: 2023/06/28 17:15:00 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	execute(char *command, int position, t_data *data)
{
	if (ft_is_builtin(command))
		builtin_redirection(command,data->args[position]);
	else
		execve(command,data->args[position], environ);
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
		g_exit = waitpid(pid, &g_exit, 0);
	}
}

void	ft_executor_binary(t_data *data)
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
		builtin_nonfork_redirection(data->commands[data->last_command], data->args[data->last_command]);
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
