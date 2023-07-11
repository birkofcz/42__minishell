/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 16:54:07 by sbenes            #+#    #+#             */
/*   Updated: 2023/07/11 14:59:33 by tkajanek         ###   ########.fr       */
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
		free_split(data->minishell_env);
		exit(exit_status);
	}
	else if (ft_isnum(data->args[0][1]) == false)
	{
		write(2, "exit\n", 5);
		write(2, "[TS]minishell: exit: ", 22);
		write(2, data->args[0][1], ft_strlen(data->args[0][1]));
		write(2, ": numeric argument required\n", 29);
		free_command_table(data);
		free_split(data->minishell_env);
		exit(2);
	}
}

static void	ft_write_bc_stupid_norminette(t_data *data)
{
	write(2, "exit\n", 5);
	write(2, "[TS]minishell: exit: ", 22);
	write(2, data->args[0][1], ft_strlen(data->args[0][1]));
	write(2, ": numeric argument required\n", 29);
}

void	ft_exit(t_data *data)
{
	if (data->args[0][1] && !(data->args[0][2]))
		ft_exit_one(data);
	else if (data->args[0][1] && data->args[0][2])
	{
		if (ft_isnum(data->args[0][1]) == false)
		{
			ft_write_bc_stupid_norminette(data);
			free_command_table(data);
			free_split(data->minishell_env);
			exit(2);
		}
		else
		{
			write(2, "exit\n[TS]minishell: exit: too many arguments\n", 46);
			g_exit = 1 << 8;
		}
	}
	else
	{
		free_command_table(data);
		free_split(data->minishell_env);
		write(1, "exit", 4);
		exit(0);
	}
}
