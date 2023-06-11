/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 14:59:54 by tkajanek          #+#    #+#             */
/*   Updated: 2023/06/08 17:27:49 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void ft_outredir(char **words, int flag)
{
	int i;
	int pos;
	int fd;

	i = 0;
	while (words[i][0] != '>')
		i++;
	pos = i;
	if (flag == 1)
		fd = open(words[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else
		fd = open(words[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
	while (words[i] != NULL)
    {
        free(words[i]);
        i++;
    }
	words[pos] = NULL;
	if (ft_strncmp(words[0], "echo", ft_strlen("echo") + 1) == 0)
		ft_echo(words, fd);
	//else if (ft_strncmp(words[0], "pwd", ft_strlen("pwd") + 1) == 0)
	//	ft_pwd(words, fd);
	else if (ft_strncmp(words[0], "env", ft_strlen("env") + 1) == 0)
		ft_env(fd);
	//error managment
}

void ft_inredir(char **words, int flag)
{
	int		i;
	int		pos;
	int 	fd;
	char 	*line;
	char	*file;

	i = 0;
	while (words[i][0] != '<')
		i++;
	pos = i;
	fd = open(words[i + 1], O_RDONLY);
	file = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		file = ft_strjoin(line, file)
		free(line);
	}
}

void ft_redir_crossroad(char **words, t_data *data)
{
	if ((ft_strncmp(data->redir, ">", ft_strlen(">") + 1) == 0))
		ft_outredir(words, 1);
	else if ((ft_strncmp(data->redir, ">>", ft_strlen(">>") + 1) == 0))
		ft_outredir(words, 2);
	else if ((ft_strncmp(data->redir, "<", ft_strlen("<") + 1) == 0))
		ft_inredir(words, 2);
}