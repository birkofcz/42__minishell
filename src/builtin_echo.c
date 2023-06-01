/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 15:07:25 by sbenes            #+#    #+#             */
/*   Updated: 2023/05/30 16:55:33 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* void	ft_echoenv(char *arg)
{
	printf("%s", getenv(&arg[1]));
} */

void	ft_echoprint(char **words, int i, int fd)
{
	while (words[i] != NULL)
	{
		//POZOR, strtrim alokuje novy string, stare words[i] je treba uvolnit free
		//Taking care of various cases with $ sign + error management
		if (words[i][0] == '$')
		{
			if (words[i][1] != '\0' && (getenv(&words[i][i]) != NULL))
				write(fd, getenv(&words[i][1]), ft_strlen(getenv(&words[i][1])));
			else if (words[i][1] != '\0' && !(getenv(&words[i][1])))
				break ;
			else
				write(fd, "$", 1);
		}
		//else printing word
		else
			write(fd, words[i], ft_strlen(words[i]));
		if (words[i + 1] != NULL)
			write(fd, " ", 1);
		i++;
	}
}

void	ft_echo(char **words, int fd)
{
	if (!words[1])
		write(fd, "\n", 1);
	else if (ft_strncmp(words[1], "-n", ft_strlen(words[1])) == 0)
		ft_echoprint(words, 2, fd);
	else
	{
		ft_echoprint(words, 1, fd);
		write(fd, "\n", 1);
	}
}
