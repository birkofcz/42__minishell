/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 18:05:14 by tkajanek          #+#    #+#             */
/*   Updated: 2023/06/17 18:21:46 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	commands_counting(char **words)
{
    int count;
    int i;
	
	count = 0;
	i = 0;
    while (words[i] != NULL)
	{
        count++;
        i++;
    }
    return (count);
}

void	free_args(char ***args)
{
	int i;
	int j;
	
	i = 0;
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

void	free_split(char **args)
{
    int i;

	i = 0;
    while (args[i] != NULL)
    {
        free(args[i]);
        i++;
    }
    free(args);
}