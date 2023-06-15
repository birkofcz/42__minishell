/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 11:05:42 by sbenes            #+#    #+#             */
/*   Updated: 2023/06/14 14:52:09 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_executor(char **words, t_data *data)
{
	int	result;
	int	pid;
	int saved_stdin;

	result = access(words[0], X_OK);
	write (1, "test inside executor\n", 22);
	if (result == 0)
	{
		if (data->infile)
		{
			saved_stdin = dup(STDIN_FILENO);
			dup2(data->infile, STDIN_FILENO);
			//uzavre STDIN=0, a priradi cislu 0 referenci na infile
			close(data->infile);
		}
		write (1, "test after stdin redir\n", 24);
		pid = fork();
		if (pid < 0)
		{
			printf("Fork failed.\n");
			return ;
		}
		if (pid == 0)
		{
			write (1, "we are in child before execve\n", 30);
			char *args_execve[] = {data->commands[0], *data->args[0], NULL};
			int i = 0;
			while (args_execve[i] != NULL)
			{
				printf("args_execve[%d] = %s\n", i, args_execve[i]);
				i++;
			}
			execve(words[0], args_execve, environ);
			printf("we are in child\n");
			//updated exit status
			exit(0);
		}
		else
		{
			wait(NULL);
			//update exit status
		}
		 if (data->infile)
        {
            dup2(saved_stdin, STDIN_FILENO); // restore the original stdin file descriptor
            close(saved_stdin); // close the duplicated file descriptor
        }
	}
	else
	{
		printf("No such file or directory: %s\n", words[0]);
		//update exit status
	}
}