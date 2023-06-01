/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_crossroad.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 13:40:19 by sbenes            #+#    #+#             */
/*   Updated: 2023/06/01 14:03:18 by sbenes           ###   ########.fr       */
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
		else if(copy[i] == '\'')
		{
			i++;
			while(copy[i] !='\'')
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



char	*dollar_check(char *word)
{
	int		i;
	int		j;
	char *env_v;
	char *temp;
	char *updated_str;

	i = 0;
	j = 0;
	updated_str = NULL;
	while (word[i] != '\0')
	{
		if (word[i] == '$')
		{
			while (ft_isalnum(word[i + 1 + j]))
				j++;
			printf ("\n$while loop: i = %d, j = %d", i, j);
			if (j != 0)
			{
				temp = ft_substr(word, i + 1, j); //alokovany
				//printf ("\ntemp po substr: %s", temp);
				if (!(env_v = getenv(temp)))
					env_v = ""; //nealokovany
				//printf ("\nenv_v: %s", env_v);
				free(temp);
				updated_str = ft_substr(word, 0, i);
				//printf ("\ntemp po substr2: %s", temp);
				temp = ft_strjoin(updated_str, env_v);
				//printf ("\nstrjoin: %s", updated_str);
				free(updated_str);
				updated_str = ft_strjoin(temp, word + i + j + 1);
				//printf ("\nstrjoin2: %s", updated_str);
				free(temp);
				free(word);
				word = updated_str;
				if (!word)
					return(ft_strdup(""));
				i = 0;
				j = 0;
			}
		}
		i ++;
	}
	printf("\nkonec $, word = %s", word);
	return(word);
}

char **parse_double_quated_strings(char **words)
{
	int	i;
	char *temp;

	i = 0;
	while (words[i])
	{
		if (words[i][0] == '"')
		{
			temp = dollar_check(words[i]);
			//printf ("\ntest po dollar checku: %s", temp);
			words[i] = ft_strtrim(temp, "\"");
			free (temp);
		}
		else if (words[i][0] == '\'')
		{
			temp = words[i];
			words[i] = ft_strtrim(temp, "\'");
			free (temp);
		}
		i++;
	}
	return (words);
}

char **replace_env_var_nonquated (char **words)
{
	int 	i;
	int 	len;

	i = 0;
	while (words[i] != NULL)
	{
		len = strlen(words[i]);

		if ((words[i][0] != '"' && words[i][len - 1] != '"') &&
			(words[i][0] != '\'' && words[i][len - 1] != '\''))
		{
			
			words[i] = dollar_check(words[i]);
			printf ("\n words po dollar check: %s i= %d", words[i], i);
			//mozna chyba pokud dollar check nic neudela???
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

void free_args(char **args)
{
    int i;

	i = 0;
    while (args[i] != NULL)
    {
        free(args[i]);
        i++;
    }
    free(args);
}

//to do: musime vysypat cely split a osetrit pokud je input NULL
int	ft_prompt_crossroad(const char *input, t_env *env)
{
	char	**words;
	int		words_count;

	//input = parse_env_var(input);
	words = ft_split(prepare_double_quoted_string(input), 29);
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
	printf("\ntest formated_words\n");
	int i = 0;
    while (words[i] != NULL)
	{
        printf("%s\n", words[i]);
        i++;
    }
	printf("\n");  */
	//konec testru
	//parse_single_quoted_string
	
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
	else if (ft_strncmp(words[0], "unset", ft_strlen(words[0])) == 0)
		ft_unset(formated_words);
	else if (ft_strncmp(words[0], "exit", ft_strlen(words[0])) == 0)
	{
		free_args(words);
		return (0);
	}
	printf("teeeeeeeeeeeeeeest\n");
	free_args(words);
	return (1);
}
