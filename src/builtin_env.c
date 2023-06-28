/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:18:18 by sbenes            #+#    #+#             */
/*   Updated: 2023/06/28 16:15:33 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* 
FT_ENV - to printout environmental variables - or write them in the file
(implemented with fd)
 */


/* envoronmental variables are usually stored in char **environ global 
variable in C. That is defined as extern char **environ - global var 
in header file*/

void	ft_env(void)
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
	exit(0);
}

int	ft_env_nonfork(char **args)
{
	int	i;

	(void)args;
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