/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:22:21 by tkajanek          #+#    #+#             */
/*   Updated: 2023/07/10 13:41:20 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_command(char *word)
{
	if (ft_strncmp(word, "echo", ft_strlen("echo") + 1) == 0)
		return (1);
	else if (ft_strncmp(word, "pwd", ft_strlen("pwd") + 1) == 0)
		return (1);
	else if (ft_strncmp(word, "cd", ft_strlen("cd") + 1) == 0)
		return (1);
	else if (ft_strncmp(word, "env", ft_strlen("env") + 1) == 0)
		return (1);
	else if (ft_strncmp(word, "export", ft_strlen("export") + 1) == 0)
		return (1);
	else if (ft_strncmp(word, "unset", ft_strlen("unset") + 1) == 0)
		return (1);
	else if (ft_strncmp(word, "clear", ft_strlen("clear") + 1) == 0)
		return (1);
	else if (ft_strncmp(word, "exit", ft_strlen("exit") + 1) == 0)
		return (1);
	else if (ft_strchr(word, '/') != NULL)
		return (1);
	return (0);
}

bool	is_pipe(char *word)
{
	if (ft_strncmp(word, "|", 2) == 0)
		return (true);
	else
		return (false);
}

static int	cmnd_counter(char **words)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (words != NULL)
	{
		while (words[i] != NULL)
		{
			count++;
			i++;
			if (words[i] != NULL)
			{
				while (words[i] != NULL && !is_pipe(words[i]))
					i++;
				if (words[i] != NULL)
				{
					if (ft_strncmp(words[i], "|", 2) == 0)
						i++;
				}
			}
		}
	}
	return (count);
}

static int	jump_to_next_command(char **words, int i)
{
	while (words[i] != NULL && !is_pipe(words[i]))
		i++;
	if (words[i] != NULL)
	{
		if (is_pipe(words[i]))
			i++;
	}
	return (i);
}

void	tokenize_command(char **words, t_data *data)
{
	int		i;
	int		j;
	int		count;
	char	**commands;

	count = cmnd_counter(words);
	commands = (char **)malloc(sizeof(char *) * (count + 1));
	i = 0;
	j = 0;
	if (words != NULL)
	{
		while (words[i] != NULL)
		{
			commands[j++] = ft_strdup(words[i++]);
			if (words[i] != NULL)
				i = jump_to_next_command(words, i);
		}
		commands[j] = NULL;
	}
	data->commands = commands;
	tokenize_arg(words, data, count);
}
