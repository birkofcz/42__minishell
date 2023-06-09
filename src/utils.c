/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 18:05:14 by tkajanek          #+#    #+#             */
/*   Updated: 2023/07/11 16:16:40 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_isdigit_array(char **arg)
{
	int	i;
	int	j;

	i = 0;
	while (arg[i])
	{
		j = 0;
		while (arg[i][j])
		{
			if (arg[i][j] < '0' || arg[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	commands_counting(char **words)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (words[i] != NULL)
	{
		count++;
		i++;
	}
	return (count);
}

void	free_command_table(t_data *data)
{
	free_args(data->args);
	free_split(data->commands);
	if (data->delimiter != NULL)
		free(data->delimiter);
}

void	free_args(char ***args)
{
	int	i;
	int	j;

	i = 0;
	if (args != NULL)
	{
		while (args[i] != NULL)
		{
			j = 0;
			while (args[i][j] != NULL)
			{
				free(args[i][j]);
				j++;
			}
			free(args[i]);
			i++;
		}
		free(args);
	}
}

void	free_split(char **args)
{
	int	i;

	i = 0;
	if (args != NULL)
	{
		while (args[i] != NULL)
		{
			free(args[i]);
			i++;
		}
	}
	free(args);
}
