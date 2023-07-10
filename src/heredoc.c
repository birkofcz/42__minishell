/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 12:40:29 by sbenes            #+#    #+#             */
/*   Updated: 2023/07/10 17:44:57 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_heredoc(char *delimiter)
{
	int		pid;
	int		fd[2];
	char	*heredoc_line;

	if (pipe(fd) == -1)
		return ;
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		heredoc_line = "";
		while (ft_strncmp(heredoc_line, delimiter, ft_strlen(delimiter)) != 0)
		{
			heredoc_line = readline("\033[96mheredoc>\033[0m ");
			write(fd[1], heredoc_line, ft_strlen(heredoc_line));
			write(fd[1], "\n", 1);
		}
		exit(0);
	}
	else
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		close(fd[0]);
		wait(NULL);
	}
}
