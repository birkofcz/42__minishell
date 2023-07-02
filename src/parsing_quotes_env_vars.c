/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_quotes_env_vars.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 18:02:23 by tkajanek          #+#    #+#             */
/*   Updated: 2023/07/02 20:49:41 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
replace all spaces with delimiter of ASCII value 29 (control character: Group Separator).
It will skip all spaces inside a double & single quates. The split is set to fragment the string
according the setted up delimiter of ASCII value 29.
*/
char *prepare_quoted_string(const char *input)
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
		else if(copy[i] == '{')
		{
			i++;
			while(copy[i] !='}')
				i++;
		}
		i++;
	}
	return (copy);
}

char	*dollar_check(char *word)
{
	int		i;
	int		j;
	char *env_v;
	char * temp;
	char *updated_str;

	i = 0;
	j = 0;
	updated_str = NULL;
	while (word[i] != '\0')
	{
		if (word[i] == '$')
		{
			while (ft_isalnum(word[i + 1 + j]) || word[i + 1 + j] == '_') // pridat vyjimku pro $?
				j++;
			if (j != 0)
			{
				printf("test pred $\n");
				temp = ft_substr(word, i + 1, j); //alokovany
				if (!(env_v = getenv(temp)))
					env_v = ""; //nealokovany
				printf("test $: %s\n", env_v);
				free(temp);
				updated_str = ft_substr(word, 0, i);
				temp = ft_strjoin(updated_str, env_v);
				free(updated_str);
				updated_str = ft_strjoin(temp, word + i + j + 1);
				free(temp);
				free(word);
				word = updated_str;
				i = -1;
				j = 0;
			}
		}
		i ++;
	}
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
			words[i] = ft_strtrim(temp, "\"");
			free(temp);
		}
		else if (words[i][0] == '\'')
		{
			temp = words[i];
			words[i] = ft_strtrim(temp, "\'");
			free(temp);
		}
		i++;
	}
	return (words);
}

char **replace_env_var_nonquated(char **words)
{
	int 	i;
	int 	len;

	i = 0;
	while (words[i] != NULL)
	{
		len = ft_strlen(words[i]);

		if ((words[i][0] != '"' && words[i][len - 1] != '"') &&
			(words[i][0] != '\'' && words[i][len - 1] != '\''))
			words[i] = dollar_check(words[i]);
		i++;
	}
	return (words);
}

char *status_substitution(char *word)
{
	int 	i;
	char	*temp;
	char	*status;
	char	*updated_str;

	i = 0;
	while (word[i] != '\0')
	{
		if (word[i] == '$' && word[i + 1] == '?')
		{
				status = ft_itoa(g_exit >> 8); //alokovany
				updated_str = ft_substr(word, 0, i);
				temp = ft_strjoin(updated_str, status);
				free(updated_str);
				free(status);
				updated_str = ft_strjoin(temp, word + i + 2);
				free(temp);
				free(word);
				word = updated_str;
				i = -1;
		}
		i ++;
	}
	printf("test final $?: %s\n", word);
	return(word);
}

char **substitution(char **words)
{
	int 	i;

	i = 0;
	while (words[i] != NULL)
	{
		if (ft_strchr(words[i], '$'))
			words[i] = status_substitution(words[i]);
		i ++;
	}
	return (words);
}

