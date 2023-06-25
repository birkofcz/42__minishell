/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_lexer_parser.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 14:23:09 by tkajanek          #+#    #+#             */
/*   Updated: 2023/06/25 15:19:46 by tkajanek         ###   ########.fr       */
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

char ***argument_parser(char **commands, char ***args)
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