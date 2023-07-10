/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:54:07 by sbenes            #+#    #+#             */
/*   Updated: 2023/07/10 17:15:06 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static bool	ft_isnum(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

static void	ft_exit_one(t_data *data)
{
	int	exit_status;

	if ((ft_isnum(data->args[0][1]) == true))
	{
		exit_status = ft_atoi(data->args[0][1]);
		free_command_table(data);
		exit(exit_status);
	}
	else if (ft_isnum(data->args[0][1]) == false)
	{
		write(1, "exit\n", 5);
		write(2, "[TS]minishell: exit: ", 22);
		write(2, data->args[0][1], ft_strlen(data->args[0][1]));
		write(2, ": numeric argument required\n", 29);
		free_command_table(data);
		exit(2);
	}
}

void	ft_exit(t_data *data)
{
	if (data->args[0][1] && !(data->args[0][2]))
		ft_exit_one(data);
	else if (data->args[0][1] && data->args[0][2])
	{
		if (ft_isnum(data->args[0][1]) == false)
		{
			write(2, "exit\n[TS]minishell: exit: ", 27);
			write(2, data->args[0][1], ft_strlen(data->args[0][1]));
			write(2, ": numeric argument required\n", 29);
			free_command_table(data);
			exit(2);
		}
		else
		{
			write(1, "exit\n", 5);
			write(2, "[TS]minishell: exit: too many arguments\n", 41);
			g_exit = 1 << 8;
		}
	}
	else
	{
		free_command_table(data);
		write(1, "exit", 4);
		exit(0);
	}
}
