/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 08:38:17 by sbenes            #+#    #+#             */
/*   Updated: 2023/07/10 08:39:58 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	set_outfile(t_data *data)
{
	if (data->outfile != -1)
	{
		dup2(data->outfile, STDOUT_FILENO);
		close(data->outfile);
	}
}

void	set_infile(t_data *data)
{
	if (data->infile != -1)
	{
		dup2(data->infile, STDIN_FILENO);
		close(data->infile);
	}
	else if (data->delimiter != NULL)
		ft_heredoc(data->delimiter);
}

void	save_restore_std(t_data *data, int i)
{
	if (i == 0)
	{
		data->saved_stdin = dup(STDIN_FILENO);
		data->saved_stdout = dup(STDOUT_FILENO);
	}
	else if (i == 1)
	{
		dup2(data->saved_stdout, STDOUT_FILENO);
		dup2(data->saved_stdin, STDIN_FILENO);
		close(data->saved_stdin);
		close(data->saved_stdout);
	}
}