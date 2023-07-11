/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:18:18 by sbenes            #+#    #+#             */
/*   Updated: 2023/07/11 14:59:32 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* 
FT_ENV - to printout environmental variables
 */
/* envoronmental variables are usually stored in char **environ global 
variable in C. That is defined as extern char **environ - global var 
in header file*/

void	ft_env_fork(t_data *data)
{
	int	i;

	i = 0;
	while (environ[i])
	{
		if (environ[i][0] != '?' && environ[i][0] != '-')
		{
			write(1, environ[i], ft_strlen(environ[i]));
			write(1, "\n", 1);
		}
		i++;
	}
	fork_exit(0, data);
}

int	ft_env_nonfork(void)
{
	int	i;

	i = 0;
	while (environ[i])
	{
		if (environ[i][0] != '?' && environ[i][0] != '-')
		{
			write(1, environ[i], ft_strlen(environ[i]));
			write(1, "\n", 1);
		}
		i++;
	}
	return (0);
}
