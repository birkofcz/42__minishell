/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_crossroad.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 13:40:19 by sbenes            #+#    #+#             */
/*   Updated: 2023/05/31 14:39:02 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
/* 
FT_PROMPT_CROSSROAD
function to read the input a set a proper function into motion
 */

//something like this - may do a int type to return the errors?


/*
replace all spaces with delimiter of ASCII value 29 (control character: Group Separator).
It will skip all spaces inside a double quates. The split is set to fragment the string
according the setted up delimiter of ASCII value 29.

It is important even for echo: e.g. try this command
echo " xxx                      " xx
*/
char *prepare_double_quoted_string(const char *input)
{
	int		i;
	char	*copy;

	copy = (char *)input;
	i = 0;
	while (copy[i] != 0)
	{
		if (copy[i] == ' ')
			copy[i] = 29;
		if (copy[i] == '"')
		{
			i++;
			while(copy[i] !='"')
				i++;
		}
		i++;
	}
	return (copy);
}

/*
Removes the quates, same as in your echo function. Just added proper free managment.
Be aware, this function changes the original char **words,
doesnt create altered copy and doesnt keep original.
*/
char **parse_double_quated_strings(char **words)
{
	int	i;
	char *temp;

	i = 0;
	while (words[i])
	{
		if (words[i][0] == '"' || words[i][ft_strlen(words[i]) - 1] == '"')
		{
			temp = words[i];
			words[i] = ft_strtrim(words[i], "\"");
			free (temp);
		}
		i++;
	}
	return (words);
}

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

//to do: musime vysypat cely split a osetrit pokud je input NULL
void	ft_prompt_crossroad(const char *input, t_env *env)
{
	char	**words;
	char	**formated_words;
	int		words_count;

	words = ft_split(prepare_double_quoted_string(input), 29);
/* 	//tester
	printf("\ntest words before trimming\n");
	int i = 0;
    while (words[i] != NULL)
	{
        printf("%s\n", words[i]);
        i++;
    }
	//konec testru */
	formated_words = parse_double_quated_strings(words);
/* 	//tester
	printf("\ntest formated_words\n");
	i = 0;
    while (formated_words[i] != NULL)
	{
        printf("%s\n", formated_words[i]);
        i++;
    }
	printf("\n");  */
	//konec testru
	//parse_single_quoted_string
	//parse_env_var
	words_count = word_counting(words);
	if (ft_strncmp(words[0], "echo", ft_strlen(words[0])) == 0)
    	ft_echo(formated_words, 1);
	else if (ft_strncmp(words[0], "pwd", ft_strlen(words[0])) == 0)
		ft_pwd(env, words_count);
	else if (ft_strncmp(words[0], "cd", ft_strlen(words[0])) == 0)
		ft_cd(env, words, words_count);
	else if (ft_strncmp(words[0], "env", ft_strlen(words[0])) == 0)
		ft_env(1);
	else if (ft_strncmp(words[0], "export", ft_strlen(words[0])) == 0)
		ft_export(formated_words);
	else if (ft_strncmp(words[0], "exit", ft_strlen(words[0])) == 0)
	{
		free(words);
		exit(0);
	}
}
