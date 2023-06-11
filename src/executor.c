/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 11:05:42 by sbenes            #+#    #+#             */
/*   Updated: 2023/06/11 13:14:06 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_executor(char **words)
{
	int	result;
	int	pid;

	result = access(words[0], X_OK);
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
			execve(words[0], words, environ);
			//updated exit status
			exit(0);
		}
		else
		{
			wait(NULL);
			//update exit status
		}
	}
	else
	{
		printf("No such file or directory: %s\n", words[0]);
		//update exit status
	}
}
