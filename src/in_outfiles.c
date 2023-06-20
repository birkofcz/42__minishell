/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_outfiles.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:51:58 by tkajanek          #+#    #+#             */
/*   Updated: 2023/06/19 16:31:31 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	tokenize_infile_heredoc(char **words, t_data *data)
{
	int i;

	i = - 1;
	while (words[++i] != NULL)
	{
		if (ft_strncmp(words[i], "<", ft_strlen("<") + 1) == 0)
			data->infile = open(words[i + 1], O_RDONLY | O_CLOEXEC, 0777);
		else if (ft_strncmp(words[i], "<<", ft_strlen("<<") + 1) == 0)
			data->delimiter = ft_strdup(words[i + 1]);
	}
}

void	tokenize_outfile(char **words, t_data *data)
{
	int i;
	int j;
	int count;
	int *outfile;

	count = 0;
	i = - 1;
	j = 0;
	while (words[++i] != NULL)
	{
		if ((ft_strncmp(words[i], ">", ft_strlen(">") + 1) == 0) || (ft_strncmp(words[i], ">>", ft_strlen(">>") + 1) == 0))
			count++;
	}
	outfile = (int *)malloc(sizeof(int) * (count));
	i = - 1;
	while (words[++i] != NULL)
	{
		if (ft_strncmp(words[i], ">>", ft_strlen(">>") + 1) == 0)
		{
			outfile[j] = open(words[i + 1], O_WRONLY | O_CREAT | O_APPEND| O_CLOEXEC, 0777);
			j++;
		}
		else if (ft_strncmp(words[i], ">", ft_strlen(">") + 1) == 0)
		{
			outfile[j] = open(words[i + 1], O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC, 0777);
			j++;
		}
	}
	data->outfile = outfile;
	data->outfile_count = count;
}