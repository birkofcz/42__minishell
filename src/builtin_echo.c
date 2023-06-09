/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 15:07:25 by sbenes            #+#    #+#             */
/*   Updated: 2023/07/11 16:19:26 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_echoprint(char **args, int i)
{
	while (args[i] != NULL)
	{
		if (args[i][0] == '{' && args[i][ft_strlen(args[i]) - 1] == '}')
			ft_echo_expander(args[i]);
		else
			write(1, args[i], ft_strlen(args[i]));
		if (args[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
}

void	ft_echo_fork(char **args, t_data *data)
{
	if (!args[1])
		write(1, "\n", 1);
	else if (ft_strncmp(args[1], "-n", ft_strlen(args[0])) == 0)
		ft_echoprint(args, 2);
	else
	{
		ft_echoprint(args, 1);
		write(1, "\n", 1);
	}
	fork_exit(0, data);
}

int	ft_echo_nonfork(char **args)
{
	if (!args[1])
		write(1, "\n", 1);
	else if (ft_strncmp(args[1], "-n", ft_strlen(args[0])) == 0)
		ft_echoprint(args, 2);
	else
	{
		ft_echoprint(args, 1);
		write(1, "\n", 1);
	}
	return (0);
}
