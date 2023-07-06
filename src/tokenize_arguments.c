/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_arguments.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:17:35 by tkajanek          #+#    #+#             */
/*   Updated: 2023/07/06 14:39:28 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

static void argument_fill(char	***args, char ** words, int *i, int j)
{
	int k;

	k = 0;
	while (words[*i] != NULL && !is_pipe(words[*i]))
	{
		args[j][k] = ft_strdup(words[*i]);
		k++;
		(*i)++;
	}
	args[j][k] = NULL;
}
//blbne to pokud napr < infile | pwd
void	tokenize_arg(char **words, t_data *data, int count)
{
	int i;
	int j;
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