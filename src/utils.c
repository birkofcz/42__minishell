/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 18:05:14 by tkajanek          #+#    #+#             */
/*   Updated: 2023/06/03 19:58:44 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	word_counting(char **words)
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

void free_args(char **args)
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