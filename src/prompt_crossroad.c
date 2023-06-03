/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_crossroad.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 13:40:19 by sbenes            #+#    #+#             */
/*   Updated: 2023/06/03 19:57:44 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
/* 
FT_PROMPT_CROSSROAD
function to read the input a set a proper function into motion
 */

//something like this - may do a int type to return the errors?

//to do: osetrit pokud je input NULL
int	ft_prompt_crossroad(const char *input, t_env *env)
{
	char	**words;
	int		words_count;

	words = ft_split(prepare_quoted_string(input), 29);
	//tester
	/*printf("\ntest words before trimming\n");
	int i = 0;
    while (words[i] != NULL)
	{
        printf("%s\n", words[i]);
        i++;
    }*/
	//konec testru
	words = replace_env_var_nonquated (words);
	words = parse_double_quated_strings(words);
	//tester
	/*printf("\ntest formated_words\n");
	int i = 0;
    while (words[i] != NULL)
	{
        printf("%s\n", words[i]);
        i++;
    }
	printf("\n");*/
	//konec testru
	words_count = word_counting(words);
	if (ft_strncmp(words[0], "echo", ft_strlen(words[0])) == 0)
    	ft_echo(words, 1);
	else if (ft_strncmp(words[0], "pwd", ft_strlen(words[0])) == 0)
		ft_pwd(env, words_count);
	else if (ft_strncmp(words[0], "cd", ft_strlen(words[0])) == 0)
		ft_cd(env, words, words_count);
	else if (ft_strncmp(words[0], "env", ft_strlen(words[0])) == 0)
		ft_env(1);
	else if (ft_strncmp(words[0], "export", ft_strlen(words[0])) == 0)
		ft_export(words);
	else if (ft_strncmp(words[0], "unset", ft_strlen(words[0])) == 0)
		ft_unset(words);
	else if (ft_strncmp(words[0], "exit", ft_strlen(words[0])) == 0)
		return (free_args(words),0);
	return (free_args(words), 1);
}
