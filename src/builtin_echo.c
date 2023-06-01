/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 15:07:25 by sbenes            #+#    #+#             */
/*   Updated: 2023/05/30 13:34:23 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* void	ft_echoenv(char *arg)
{
	printf("%s", getenv(&arg[1]));
} */

void	ft_echoprint(char **words, int i)
{
	while (words[i] != NULL)
	{
		//POZOR, strtrim alokuje novy string, stare words[i] je treba uvolnit free
		//Taking care of various cases with $ sign + error management
		if (words[i][0] == '$')
		{
			if (words[i][1] != '\0' && (getenv(&words[i][i]) != NULL))
				printf("%s", getenv(&words[i][1]));
			else if (words[i][1] != '\0' && !(getenv(&words[i][1])))
				break ;
			else
				printf("$");
		}
		//else printing word
		else
			printf("%s", words[i]);
		if (words[i + 1] != NULL)
			printf(" ");
		i++;
	}
}

void	ft_echo(char **words)
{
	if (!words[1])
		printf("\n");
	else if (ft_strncmp(words[1], "-n", ft_strlen(words[1])) == 0)
		ft_echoprint(words, 2);
	else
	{
		ft_echoprint(words, 1);
		printf("\n");
	}


}
