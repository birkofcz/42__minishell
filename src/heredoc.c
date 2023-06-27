/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 12:40:29 by sbenes            #+#    #+#             */
/*   Updated: 2023/06/25 16:44:51 by tkajanek         ###   ########.fr       */
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
		while (ft_strncmp(heredoc_line, delimiter, ft_strlen(delimiter)) != 0)
		{
			heredoc_line = readline("heredoc>");
			write(fd[1], heredoc_line, ft_strlen(heredoc_line));
		}
	}
	else
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		wait(NULL);
	}
}
