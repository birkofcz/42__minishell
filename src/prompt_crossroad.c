/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_crossroad.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 13:40:19 by sbenes            #+#    #+#             */
/*   Updated: 2023/05/29 16:24:18 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
/* 
FT_PROMPT_CROSSROAD
function to read the input a set a proper function into motion
 */

//something like this - may do a int type to return the errors?

/* in progress
parse_double_quoted_strings (char	**words)
{
	char	**words_formatted	
}
*/

int	word_counting(char **words)
{
    int count;
    int i;
	
	count = 0;
	i = 0;
    while (words[i] != NULL)
	{
        count++;
        i++;
    }
    return (count);
}

void	ft_prompt_crossroad(const char *input, t_env *env)
{
	char	**words;
	int		words_count;

	words = ft_split(input, ' '); //musime vysypat cely array a osetrit pokud je input NULL
	//parse_double_quoted_strings
	//parse_single_quoted_strings
	//parse_env_var
	words_count = word_counting(words);
	if (ft_strncmp(words[0], "echo", ft_strlen(words[0])) == 0)
    ft_echo(words);
	else if (ft_strncmp(words[0], "pwd", ft_strlen(words[0])) == 0)
		ft_pwd(env, words_count);
	else if (ft_strncmp(words[0], "cd", ft_strlen(words[0])) == 0)
		ft_cd(env, words, words_count);
	else if (ft_strncmp(words[0], "exit", ft_strlen(words[0])) == 0)
	{
		free(words);
		exit(0);
	}
}
