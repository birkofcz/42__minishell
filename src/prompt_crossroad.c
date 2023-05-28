/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_crossroad.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 13:40:19 by sbenes            #+#    #+#             */
/*   Updated: 2023/05/28 14:16:08 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
/* 
FT_PROMPT_CROSSROAD
function to read the input a set a proper function into motion
 */

//something like this - may do a int type to return the errors?

void	ft_prompt_crossroad(const char *input)
{
	//char **words;

	//words = ft_split(input, " ");
	if (ft_strnstr(input, "echo", ft_strlen(input)) != NULL)
		printf("echo recieved...\n");
	else if (ft_strnstr(input, "exit", ft_strlen(input)) != NULL)
	{
		exit(0);
	}
		return ;
	//free(words);
}
