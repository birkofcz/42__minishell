/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:05:04 by sbenes            #+#    #+#             */
/*   Updated: 2023/07/11 16:14:28 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
			status = ft_itoa(g_exit >> 8);
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
	return (word);
}

static char	*ft_uznevimnorminette(void)
{
	char	*temp;
	char	*output;

	temp = getenv("HOME");
	output = ft_strdup(temp);
	free(temp);
	return (output);
}

char	*tilda_replace(char *word)
{
	int		i;
	char	*temp;
	char	*path;

	i = 0;
	while (word[i] != '\0')
	{
		if (word[i] == '~' && word[i + 1] == '/')
		{
			path = ft_strtrim(word, "~");
			temp = ft_strjoin(getenv("HOME"), path);
			free(path);
			free(word);
			word = temp;
		}
		else if (word[i] == '~' && word[i + 1] == '\0')
		{
			free(word);
			word = ft_uznevimnorminette();
		}
		else if (word[i] == '~' && word[i + 1] != '/' && word[i + 1] != '\0')
			break ;
		i++;
	}
	return (word);
}
