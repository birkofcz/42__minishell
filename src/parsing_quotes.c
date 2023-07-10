/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 18:02:23 by tkajanek          #+#    #+#             */
/*   Updated: 2023/07/10 14:29:27 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
replace all spaces with delimiter of ASCII value 29 (control character:
 Group Separator). It will skip all spaces inside a double & single quates. 
 The split is set to fragment the string  according the setted up delimiter 
 of ASCII value 29.
*/

static void	ft_move_brackets(char *copy, int *i, char bracket)
{
	(*i)++;
	while (copy[*i] != bracket)
		(*i)++;
}

char	*prepare_quoted_string(const char *input)
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
			ft_move_brackets(copy, &i, '"');
		else if (copy[i] == '\'')
			ft_move_brackets(copy, &i, '\'');
		else if (copy[i] == '{')
			ft_move_brackets(copy, &i, '}');
		i++;
	}
	return (copy);
}

char	**parse_quated_strings(char **words)
{
	int		i;
	char	*temp;

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
