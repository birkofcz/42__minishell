/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_commands_args.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 15:22:21 by tkajanek          #+#    #+#             */
/*   Updated: 2023/06/20 16:40:03 by tkajanek         ###   ########.fr       */
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

int	args_counter(char **words, int i)
{
	int	count;
	int command;

	count = 0;
	command = 0;
	//if pipe i++; i++; arg_count
	while (words[i] != NULL && command != 2 && ((is_redir(words[i]) == 1) || (is_command(words[i]) == 1) || (ft_strncmp(words[i], "|", ft_strlen("|") + 1) == 0)))
	{
		if (is_redir(words[i]) == 1)
			i++;
		if ((is_command(words[i]) == 1))
			command ++;
		i++;
	}
	if (command == 2)
		i --;
	while (words[i] != NULL && (is_redir(words[i]) == 0) && (is_command(words[i]) == 0) && (ft_strncmp(words[i], "|", ft_strlen("|") + 1) != 0))
	{
		count ++;
		i++;
	}
	printf ("args_count = %d\n", count);
	return (count);
}

void	tokenize_arg(char **words, t_data *data, int count) //predelat na druhem miste muze byt infile
{
	int i;
	int j;
	int k;
	int command;
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
		command = 0;
		while (words[i] != NULL && command != 2 &&((is_redir(words[i]) == 1) || (is_command(words[i]) == 1) || (ft_strncmp(words[i], "|", ft_strlen("|") + 1) == 0)))
		{
			if (is_redir(words[i]) == 1)
				i++;
			if ((is_command(words[i]) == 1))
				command ++;
			i++;
		}
		if (command == 2)
			i --;
		while (count != 0 && words[i] != NULL && (is_redir(words[i]) == 0) && (is_command(words[i]) == 0) && (ft_strncmp(words[i], "|", ft_strlen("|") + 1) != 0))
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

	i = -1;
	count = 0;
	
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
	i = 0;
	tokenize_arg(words, data, count);
}