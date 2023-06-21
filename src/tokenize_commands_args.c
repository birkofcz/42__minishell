/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_commands_args.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:22:21 by tkajanek          #+#    #+#             */
/*   Updated: 2023/06/21 17:01:48 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_command(char *word)
{
	if (ft_strncmp(word, "echo", ft_strlen("echo") + 1) == 0)
    	return(1);
	else if (ft_strncmp(word, "pwd", ft_strlen("pwd") + 1) == 0)
		return(1);
	else if (ft_strncmp(word, "cd", ft_strlen("cd") + 1) == 0)
		return(1);
	else if (ft_strncmp(word, "env", ft_strlen("env") + 1) == 0)
		return(1);
	else if (ft_strncmp(word, "export", ft_strlen("export") + 1) == 0)
		return(1);
	else if (ft_strncmp(word, "unset", ft_strlen("unset") + 1) == 0)
		return(1);
	else if (ft_strncmp(word, "clear", ft_strlen("clear") + 1) == 0)
		return(1);
	else if (ft_strncmp(word, "exit", ft_strlen("exit") + 1) == 0)
		return(1);
	else if (ft_strchr(word, '/') != NULL)
		return(1);
	return (0);
}

bool is_pipe(char *word)
{
	if (ft_strncmp(word, "|", 2) == 0)
		return (true);
	else
		return (false);
}

int	args_counter(char **words, int i)
{
	int	count;

	count = 0;
	if (words[i] != NULL)
		i++;
	while (words[i] != NULL && !is_pipe(words[i]))
	{
		count++;
		i++;
	}
	return (count);
}

void	tokenize_arg(char **words, t_data *data, int count) //predelat na druhem miste muze byt infile
{
	int i;
	int j;
	int k;
	char	***args;

	i = 0;
	j = 0;
	k = 0;
	printf ("command count : %d\n", count);
	args = (char ***)malloc(sizeof(char **) * (count + 1));//command_count
	while (words[i] != NULL)
	{
		count = args_counter (words, i);
		printf ("argument count : %d\n", count);
		if (count == 0)
		{
			args[j] = (char **)malloc(sizeof(char *) * (2));
		}
		else
			args[j] = (char **)malloc(sizeof(char *) * (count + 1));
		if (words[i] != NULL)
		i++;
		while (words[i] != NULL && !is_pipe(words[i]))
		{
			args[j][k] = ft_strdup(words[i]);
			k++;
			i++;
		}
		args[j][k] = NULL;
		k = 0;
		j++;
		if (words[i] == NULL)
			break ;
		i++;
		/**/
	}
	args[j] = NULL;
	data->args = args;
}

void	tokenize_command(char **words, t_data *data)
{
	int i;
	int j;
	int	count;
	char	**commands;

	i = 0;
	count = 0;
	if (words != NULL)
	{
		while (words[i] != NULL)
		{
			write(1, "test1\n", 7);
			count++;
			i++;
			if (words[i] != NULL)
				{
					while (words[i] != NULL && (ft_strncmp(words[i], "|", 2)))
					i++;
					if (words[i] != NULL)
					{
						if (ft_strncmp(words[i], "|", 2) == 0)
							i++;
					}
				}
		}
	}
	printf ("command count = %d", count);
	commands = (char **)malloc(sizeof(char *) * (count + 1));
	i = 0;
	j = 0;
	if (words != NULL)
	{
		while (words[i] != NULL)
		{
			write(1, "test2\n", 7);
			commands[j++] = ft_strdup(words[i++]);
			if (words[i] != NULL)
				{
					while (words[i] != NULL && (ft_strncmp(words[i], "|", 2)))
					i++;
					if (words[i] != NULL)
					{
						if (ft_strncmp(words[i], "|", 2) == 0)
							i++;
					}
				}
		}
		commands[j] = NULL;
	}
	/*
	while (words[++i] != NULL)
	{
		if ((is_command(words[i]) ))
			count ++;
	}
	i = -1;
	commands = (char **)malloc(sizeof(char *) * (count + 1));
	j = 0;
	while (words[++i] != NULL)
	{
		if (is_command(words[i]))
		{
			commands[j] = ft_strdup(words[i]);
			j++;
		}
	}
	commands[j] = NULL;
	data->commands = commands;
	i = 0;*/
	data->commands = commands;
	write(1, "test_konec\n", 12);
	i = 0;
	while (commands[i])
	{
        printf("commands[%d] :%s\n",i, commands[i]);
		i++;
    }
	tokenize_arg(words, data, count);
}