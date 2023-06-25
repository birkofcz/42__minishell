/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 15:07:25 by sbenes            #+#    #+#             */
/*   Updated: 2023/06/25 14:56:42 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_echoprint(char **args, int i)
{
	while (args[i] != NULL)
	{
		//POZOR, strtrim alokuje novy string, stare args[i] je treba uvolnit free
		//Taking care of various cases with $ sign + error management
		if (args[i][0] == '{' && args[i][ft_strlen(args[i]) -1 ] == '}')
			ft_echo_expander(args[i]);
		else if (args[i][0] == '$')
		{
			if (args[i][1] != '\0' && (getenv(&args[i][i]) != NULL))
				write(1, getenv(&args[i][1]), ft_strlen(getenv(&args[i][1])));
			// LAST EXIT STATUS FOR ECHO $?
			/*else if (args[i][1] == '?' && args[i][2] == '\0')
				write(fd, ft_itoa(g_exit_status), ft_strlen(ft_itoa(g_exit_status)));*/
			else if (args[i][1] != '\0' && !(getenv(&args[i][1])))
				break ;
			else
				write(1, "$", 1);
		}
		//else printing word
		else
			write(1, args[i], ft_strlen(args[i]));
		if (args[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
}

void	ft_echo(char **args)
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
	exit(0);
}


void	ft_echo_nonfork(char **args)
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
}