/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 18:05:14 by tkajanek          #+#    #+#             */
/*   Updated: 2023/06/24 16:22:28 by sbenes           ###   ########.fr       */
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
void	free_command_table(t_data *data)
{

	//write(1, "test before args free\n", 23);
	//free_args(data->args);
	//write(1, "test before commands free\n", 27);
	free_split(data->commands);
} 
void	free_args(char ***args)
{
	int i;
	int j;
	
	i = 0;
	if (args != NULL)
	{
		write(1, "test 1\n", 8);
		while (args[i] != NULL)
		{
			write(1, "test 2\n", 8);
			j = 0;
			while (args[i][j] != NULL)
			{
				write(1, "test 3\n", 8);
				free(args[i][j]);
				j++;
			}
			free(args[i]);
			write(1, "test 4\n", 8);
			i++;
		}
		free(args);
	}
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