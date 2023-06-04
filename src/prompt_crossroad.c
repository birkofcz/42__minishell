/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_crossroad.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 13:40:19 by sbenes            #+#    #+#             */
/*   Updated: 2023/06/04 16:09:56 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
/* 
FT_PROMPT_CROSSROAD
function to read the input a set a proper function into motion
 */

//something like this - may do a int type to return the errors?

//to do: osetrit pokud je input NULL
 char *analyze(char **words, t_data *data)
{
	int i;

	i = 0;
    while (words[i] != NULL)
    {
        if ((ft_strncmp(words[i], "<", ft_strlen("<") + 1) == 0))
			ft_strlcpy(data->redir,words[i], 2);
		else if ((ft_strncmp(words[i], ">", ft_strlen(">") + 1) == 0))
			ft_strlcpy(data->redir,words[i], 2);
		else if ((ft_strncmp(words[i], "<<", ft_strlen("<<") + 1) == 0))
			ft_strlcpy(data->redir,words[i], 3);
		else if ((ft_strncmp(words[i], ">>", ft_strlen(">>") + 1) == 0))
			ft_strlcpy(data->redir,words[i], 3);
		else if ((ft_strncmp(words[i], "|", ft_strlen("|") + 1) == 0))
			ft_strlcpy(data->redir,words[i], 2);
        i++;
    }
	return (data->redir);
}

int	ft_prompt_crossroad(const char *input, t_data *data)
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
	if (analyze(words, data) != 0)
		ft_redir_crossroad(words, data);
	else if (ft_strncmp(words[0], "echo", ft_strlen("echo") + 1) == 0)
    	ft_echo(words, 1);
	//else if (ft_strncmp(words[0], "pwd", ft_strlen("pwd") + 1) == 0) // $blabla pwd -> by melo fungovat
	//	ft_pwd(env, words_count);
	//else if (ft_strncmp(words[0], "cd", ft_strlen("cd") + 1) == 0)
	//	ft_cd(env, words, words_count);
	else if (ft_strncmp(words[0], "env", ft_strlen("env") + 1) == 0)
		ft_env(1);
	else if (ft_strncmp(words[0], "export", ft_strlen("export") + 1) == 0)
		ft_export(words);
	else if (ft_strncmp(words[0], "unset", ft_strlen("unset") + 1) == 0)
		ft_unset(words);
	if (ft_strncmp(words[0], "exit", ft_strlen("exit") + 1) == 0)
		return (free_args(words),0);
	return (free_args(words), 1);
}
