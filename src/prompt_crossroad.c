/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_crossroad.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 13:40:19 by sbenes            #+#    #+#             */
/*   Updated: 2023/05/28 18:31:16 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
/* 
FT_PROMPT_CROSSROAD
function to read the input a set a proper function into motion
 */

//something like this - may do a int type to return the errors?

void	ft_prompt_crossroad(const char *input, t_env *env)
{
	char	**words;

	words = ft_split(input, ' '); //musime vysypat cely array a osetrit pokud je input NULL
	if (ft_strncmp(words[0], "echo", ft_strlen(words[0])) == 0)
		printf("echo recieved...\n");
	else if (ft_strncmp(words[0], "pwd", ft_strlen(words[0])) == 0)
		ft_pwd(env); //check the arguments, if there are more than just pwd -> error
	else if (ft_strncmp(words[0], "cd", ft_strlen(words[0])) == 0)
		ft_cd(env, words);
	else if (ft_strncmp(words[0], "exit", ft_strlen(words[0])) == 0)
	{
		free(words);
		exit(0);
	}
}
