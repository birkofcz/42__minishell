/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TEST_executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:28:32 by tkajanek          #+#    #+#             */
/*   Updated: 2023/06/17 18:03:32 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_executor_binary(char **commands, int position, t_data *data)
{
	int	result;
	int	pid;

	result = access(commands[position], X_OK);
	write (1, "test inside executor\n", 22);
	if (result == 0)
	{
		pid = fork();
		if (pid < 0)
		{
			printf("Fork failed.\n");
			return ;
		}
		if (pid == 0)
		{
			write (1, "we are in child before execve\n", 30);
			char *args_execve[] = {data->commands[position], *data->args[position], NULL};
			/*int i = 0;
			while (args_execve[i] != NULL)
			{
				printf("args_execve[%d] = %s\n", i, args_execve[i]);
				i++;
			}*/
			execve(commands[position], args_execve, environ);
			printf("we are in child\n");
			//updated exit status
			exit(0);
		}
		else
		{
			wait(NULL);
			//update exit status
		}
		/* if (data->infile)
        {
            dup2(saved_stdin, STDIN_FILENO); // restore the original stdin file descriptor
            close(saved_stdin); // close the duplicated file descriptor
        }*/
	}
	else
	{
		printf("No such file or directory: %s\n", commands[position]);
		//update exit status
	}
}

/*pipex_builtins(infile, outfile, pipe)
(
	if (infile && first_command)
		redirect;
	if (outfile & last_command)
		redirect;
	if (<last command)
		pipe_redirection; // while loop
)*/

void redirect_infile(t_data *data)
{
	data->saved_stdin = dup(STDIN_FILENO);
	if (data->infile)
	{
		dup2(data->infile, STDIN_FILENO);
		//uzavre STDIN=0, a priradi cislu 0 referenci na infile
		close(data->infile);
		printf("infile after redirection and close : %d\n", data->infile);
		data->inflag = 1;
	}
	write (1, "test after redirection infile\n", 31);
}

void redirect_outfile(t_data *data)
{
	data->saved_stdout = dup(STDOUT_FILENO);
	printf("outfile in redirection : %d\n", data->outfile[0]);
	if (data->outfile[0])
	{
		dup2(data->outfile[0], STDOUT_FILENO);
		close(data->outfile[0]);
		data->outflag = 1;

	}
	write (1, "test after redirection outfile\n", 32);
}

void	pipe_redirection(t_data *data)
{
	int pipe_fd[2];

	if(data->inflag == 0 || data->outflag == 0)
	{
		pipe(pipe_fd);
		printf("uvnitr pipe redirection: inflag = %d, outflag = %d\n", data->inflag, data->outflag);
		if (data->outflag == 0)
		{
			dup2(pipe_fd[0], STDIN_FILENO);
			close(pipe_fd[0]);
			write (1, "pipe stdin redirected\n", 23);
		}
		//else
		//	close(pipe_fd[0]); // ?
		if (data->inflag == 0)
		{
			dup2(pipe_fd[1], STDOUT_FILENO);
			close(pipe_fd[1]);
			write (1, "pipe stdout redirected\n", 24);
		}
		//else
		//	close(pipe_fd[1]); // ?
	}
	else
	{
		close(pipe_fd[0]); // Close unused read end
		close(pipe_fd[1]); // Close unused write end
	}
	
	write (1, "test after redirection pipe\n", 29);
}

void pipex_exe(int position, t_data *data)
{
	data->inflag = 0;
	data->outflag = 0;
	if (position == 0 && data->infile != -1)
		redirect_infile(data);
	if (position == data->last_command && data->outfile[1] != -1)
		redirect_outfile(data); // loop for every outfiles 
	printf ("inflag = %d, outflag = %d\n", data->inflag, data->outflag);
	if (position < data->last_command)
		{
			write(1, "test uvnitr if pipe\n", 21);
			pipe_redirection(data);
		}
}


void execute(char **commands, int position, t_data *data)
{
	if (ft_strchr(commands[position], '/') != NULL)
	{
		pipex_exe(position, data);
		ft_executor_binary(commands, position, data);
	//restore io?
	}
	/*else
		{
		pipex_builtins
		builtins();
		//restore io?
		}*/
}

void exe(t_data *data)
{
	int i;

	i = 0;
	while (data->commands[i] != NULL)
	{
		execute(data->commands, i, data);
		i++;
	}
}
