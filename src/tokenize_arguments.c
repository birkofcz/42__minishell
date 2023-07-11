/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_arguments.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:17:35 by tkajanek          #+#    #+#             */
/*   Updated: 2023/07/10 15:47:49 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**copy_args(char **arr_src, char *command)
{
	char	**arr_dst;
	int		i;
	int		counter;

	counter = 0;
	i = 0;
	while (arr_src[counter])
		counter++;
	counter += 2;
	arr_dst = (char **)malloc(sizeof(char *) * (counter));
	arr_dst [i] = ft_strdup(command);
	if (!arr_dst)
		return (NULL);
	while (i < counter - 1)
	{
		arr_dst[i + 1] = arr_src[i];
		i++;
	}
	arr_dst[i] = NULL;
	free(arr_src);
	return (arr_dst);
}

char	***argument_parser(char **commands, char ***args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		args[i] = copy_args(args[i], commands[i]);
		i++;
	}
	return (args);
}

static int	args_counter(char **words, int i)
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

static void	argument_fill(char	***args, char **words, int *i, int j)
{
	int	k;

	k = 0;
	while (words[*i] != NULL && !is_pipe(words[*i]))
	{
		args[j][k] = ft_strdup(words[*i]);
		k++;
		(*i)++;
	}
	args[j][k] = NULL;
}

void	tokenize_arg(char **words, t_data *data, int count)
{
	int		i;
	int		j;
	char	***args;

	i = 0;
	j = 0;
	args = (char ***)malloc(sizeof(char **) * (count + 1));
	while (words[i] != NULL)
	{
		count = args_counter (words, i);
		if (count == 0)
			args[j] = (char **)malloc(sizeof(char *) * (2));
		else
			args[j] = (char **)malloc(sizeof(char *) * (count + 1));
		if (words[i] != NULL)
			i++;
		argument_fill(args, words, &i, j);
		j++;
		if (words[i] == NULL)
			break ;
		i++;
	}
	args[j] = NULL;
	data->args = args;
}
