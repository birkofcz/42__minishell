/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:57:21 by tkajanek          #+#    #+#             */
/*   Updated: 2023/07/10 14:19:09 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*env_replacement(char *word, int i, int j)
{
	char	*env_v;
	char	*temp;
	char	*updated_str;

	updated_str = NULL;
	printf("test pred $\n");
	temp = ft_substr(word, i + 1, j); //alokovany
	env_v = getenv(temp);
	if (env_v == NULL)
		env_v = ""; //nealokovany
	printf("test $: %s\n", env_v);
	free(temp);
	updated_str = ft_substr(word, 0, i);
	temp = ft_strjoin(updated_str, env_v);
	free(updated_str);
	updated_str = ft_strjoin(temp, word + i + j + 1);
	free(temp);
	free(word);
	return (updated_str);
}

char	*dollar_check(char *word)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (word[i] != '\0')
	{
		if (word[i] == '$')
		{
			while (ft_isalnum(word[i + 1 + j]) || word[i + 1 + j] == '_')
				j++;
			if (j != 0)
			{
				word = env_replacement(word, i, j);
				i = -1;
				j = 0;
			}
		}
		i ++;
	}
	return (word);
}

char	**replace_env_var_nonquated(char **words)
{
	int	i;
	int	len;

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

char	*status_replace(char *word)
{
	int		i;
	char	*temp;
	char	*status;
	char	*updated_str;

	i = 0;
	while (word[i] != '\0')
	{
		if (word[i] == '$' && word[i + 1] == '?')
		{
			status = ft_itoa(g_exit >> 8);//alokovany
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
	return (word);
}

char	**status_var_check(char **words)
{
	int	i;

	i = 0;
	while (words[i] != NULL)
	{
		if (ft_strchr(words[i], '$'))
			words[i] = status_replace(words[i]);
		i ++;
	}
	return (words);
}
