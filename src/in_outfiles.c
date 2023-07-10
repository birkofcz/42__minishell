/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_outfiles.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:51:58 by tkajanek          #+#    #+#             */
/*   Updated: 2023/07/10 08:47:15 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	redir_count(char **words, char *redir_frst, char *redir_scnd)
{
	int	count;
	int	i;

	count = 0;
	i = -1;
	while (words[++i] != NULL)
	{
		if ((ft_strncmp(words[i], redir_frst, ft_strlen(redir_frst) + 1) == 0)
			|| (ft_strncmp(words[i], redir_scnd, ft_strlen(redir_scnd) + 1)
				== 0))
			count++;
	}
	return (count);
}

void	tokenize_infile_heredoc(char **words, t_data *data)
{
	int	i;
	int	count;
	int	done;

	count = redir_count(words, "<", "<<");
	done = 0;
	i = -1;
	while (words[++i] != NULL)
	{
		if (ft_strncmp(words[i], "<", ft_strlen("<") + 1) == 0)
		{
			done ++;
			if (done == count)
				data->infile = open(words[i + 1], O_RDONLY | O_CLOEXEC, 0777);
		}
		else if (ft_strncmp(words[i], "<<", ft_strlen("<<") + 1) == 0)
		{
			done ++;
			if (done == count)
				data->delimiter = ft_strdup(words[i + 1]);
		}
	}
}

void	tokenize_outfile(char **words, t_data *data)
{
	int	i;
	int	count;
	int	done;

	count = redir_count(words, ">", ">>");
	done = 0;
	i = -1;
	while (words[++i] != NULL)
	{
		if (ft_strncmp(words[i], ">>", ft_strlen(">>") + 1) == 0)
		{
			data->outfile = open(words[i + 1], O_WRONLY | O_CREAT | O_APPEND
					| O_CLOEXEC, 0777);
			done++;
			if (done < count)
				close (data->outfile);
		}
		else if (ft_strncmp(words[i], ">", ft_strlen(">") + 1) == 0)
		{
			data->outfile = open(words[i + 1], O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC, 0777);
			done++;
			if (done < count)
				close (data->outfile);
		}
	}
}
