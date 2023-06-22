/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_binary.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 15:11:12 by tkajanek          #+#    #+#             */
/*   Updated: 2023/06/22 16:48:36 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	execute(char *command, int position, t_data *data)
{
	char *args_execve[] = {data->commands[position], *data->args[position], NULL};

	if (ft_is_builtin(command) == true)
		builtin_redirection(command, args_execve);
	else
		execve(command, args_execve, environ);
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
		waitpid(pid, NULL, 0);
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
		waitpid(pid, NULL, 0);
	dup2(saved_stdout,STDOUT_FILENO);
	dup2(saved_stdin,STDIN_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	free_command_table(data);
}
//outfiles : prvni udelat normalne,
//druhy a x-ty pouze kopirovat-(zachovat adresu/filename + OREADONLY)
//outfile mame