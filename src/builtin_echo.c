/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 15:07:25 by sbenes            #+#    #+#             */
/*   Updated: 2023/05/28 17:19:14 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_echoenv(char *arg)
{
	printf("%s", getenv(&arg[1]));
}

void	ft_echoprint(char **words, int i)
{
	while (words[i] != NULL)
	{
		printf("%s", words[i]);
		if (words[i + 1] != NULL)
			printf(" ");
		i++;
	}
}

void	ft_echo(char **words)
{
	//TO SOLVE LATER - case with "echo $USER", it has to print value of env variable.
	int i;

	i = 0;
	if (!words[1])
	{
		printf("\n");
		return ;
	}
	else if (words[i++][0] == '$')
		ft_echoenv(words[i]);
	else if (ft_strncmp(words[1], "-n", ft_strlen(words[1])) == 0)
		ft_echoprint(words, 2);
	else
	{
		ft_echoprint(words, 1);
		printf("\n");
	}
}
