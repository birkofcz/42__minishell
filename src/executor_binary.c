/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_binary.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:28:32 by tkajanek          #+#    #+#             */
/*   Updated: 2023/06/15 15:53:33 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	execute(char *command, int position, t_data *data)
{
	char *args_execve[] = {data->commands[position], *data->args[position], NULL};
	execve(command,args_execve, environ);
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
	//pid_t	pid;

	i = 0;
	if (data->infile != - 1)
	{
		printf("we are inside infile redirection\n");
		dup2(data->infile, STDIN_FILENO);
		close(data->infile);
	}
	while (i < data->last_command)
	{
		printf("we are inside child loop\n");
		child(data->commands[i], i, data); // v tuto chvili rozhodnout zda-li exe nebo builtin
		i++;
	}
	if (data->outfile[0] != -1)
	{
		printf("we are inside outfile redirection\n");
		dup2(data->outfile[0], STDOUT_FILENO);
		close(data->outfile[0]);
	}
	// v tuto chvili rozhodnout zda-li exe nebo builtin
	/*pid = fork();
	if (pid == -1)
	{
		// Handle fork error
		perror("fork");
		exit(1);
	}
	else if (pid == 0) Je treba pak vratit STDIN a STDOUT aby fungoval dal program */
	execute(data->commands[data->last_command], data->last_command, data);
	//free_args(data->args);
}
