/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TEST_commands_exe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 14:34:37 by tkajanek          #+#    #+#             */
/*   Updated: 2023/06/18 18:43:15 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	executor_experim(t_data *data) 
{   //save standart in/out
	int tmpin = dup(STDIN_FILENO);
	int tmpout = dup(STDOUT_FILENO);

	//set the initial input 
	int fdin;
	if (data->infile) 
	{
		fdin = data->infile;
		printf("fdin set: %d\n", data->infile);
	}
	else
	{
		// Use default input
		fdin = dup(tmpin);
	}

	pid_t pid;
	int fdout;
	int i = 0;
	while (i <= data->last_command)
	{
		//redirect input
		dup2(fdin, STDIN_FILENO);
		close(fdin);
		//setup output
		printf("last command: %d\n", data->last_command);
		if (i == data->last_command)
		{
			// Last simple command 
			if(data->outfile)
			{
				fdout = (data->outfile[1]);
				printf("fdout set: %d\n", data->infile);
			}
			else
			{
				// Use default output
				fdout = dup(tmpout);
			}
		}
		else
		{
			// Not last 
			//simple command
			//create pipe
			int fdpipe[2];
			pipe(fdpipe);
			fdout = fdpipe[1];
			fdin = fdpipe[0];
			printf("not last command, pipe sets: fdout = %d, fdin = %d\n", fdout, fdin);
		}
		// Redirect output
		dup2(fdout,STDOUT_FILENO);
		printf("BEFORE FORK: fdout = %d, fdin = %d\n", fdout, fdin);
		close(fdout);

		// Create child process	
		pid = fork();
		if (pid == 0)
		{ 
			printf("we are in a child\n");
			//child 
			char *args_execve[] = {data->commands[i], *data->args[i], NULL};
			execve(data->commands[i], args_execve, environ);
			exit(1);
		} 
    	else if (pid < 0)
		{ 
			perror("fork"); 
			return ; 
		} 
	// Parent shell continue 
  	i++;
  	} 

	//restore in/out defaults
	dup2(tmpin,0);
	dup2(tmpout,1);
	close(tmpin);
	close(tmpout);
	// wait for last process 
	while (waitpid(pid, NULL, 0) > 0) {}
}// execute 