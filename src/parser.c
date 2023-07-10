/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 13:40:19 by sbenes            #+#    #+#             */
/*   Updated: 2023/07/10 13:34:07 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

 bool	is_redir(char *word)
 {
		if ((ft_strncmp(word, "<", ft_strlen("<") + 1) == 0))
			return(true);
		else if ((ft_strncmp(word, ">", ft_strlen(">") + 1) == 0))
			return(true);
		else if ((ft_strncmp(word, "<<", ft_strlen("<<") + 1) == 0))
			return(true);
		else if ((ft_strncmp(word, ">>", ft_strlen(">>") + 1) == 0))
			return(true);
		return(false);
 }

int counter_without_redirs(char **words)
{
	int	i;
	int count;

	i = -1;
	count = 0;
	while (words[++i] != NULL)
	{
		if (is_redir(words[i]) == false)
			count++;
		if (is_redir(words[i]) == true)
			i++;
	}
	return (count);
}

char	**destroy_redirections(char **words)
{
	int	i;
	int	j;
	int	count;
	char	**words_copy;

	count = counter_without_redirs(words);
	words_copy = (char **)malloc(sizeof(char *) * count + 1);
	i = - 1;
	j = 0;
	while (words[++i] != NULL)
	{
		if (is_redir(words[i]) == 0)
		{
			words_copy[j] = ft_strdup(words[i]);
			j++;
		}
		if (is_redir(words[i]) == 1)
			i++;
	}
	words_copy[j] = NULL;
	free_split(words);
	return(words_copy);
}

void	lexer(char **words, t_data *data)
{
	tokenize_outfile(words, data);
	tokenize_infile_heredoc(words, data);
	words = destroy_redirections(words);
	tokenize_command(words, data);
	ft_command_check(data);
	data->args = argument_parser(data->commands, data->args);
	// int i = 0;
/*     while (data->args[i])
	{
		int j = 0;
		while (data->args[i][j])
		{
			printf("args[%d][%d]: %s\n", i, j, data->args[i][j]);
			j++;
        }
        i++;
    } */
	free_split(words);
}

void	ft_parser(const char *input, t_data *data)
{
	char	**words;

	words = ft_split(prepare_quoted_string(input), 29);
	words = replace_env_var_nonquated (words);
	words = parse_quated_strings(words);
	words = status_var_check(words); 
	lexer(words, data);
}
 