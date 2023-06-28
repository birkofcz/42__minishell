/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_crossroad.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 13:40:19 by sbenes            #+#    #+#             */
/*   Updated: 2023/06/27 16:06:35 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
/* 
FT_PROMPT_CROSSROAD
function to read the input a set a proper function into motion
 */

//something like this - may do a int type to return the errors?

//to do: osetrit pokud je input NULL

 int	is_redir(char *word)
 {
		if ((ft_strncmp(word, "<", ft_strlen("<") + 1) == 0))
			return(1);
		else if ((ft_strncmp(word, ">", ft_strlen(">") + 1) == 0))
			return(1);
		else if ((ft_strncmp(word, "<<", ft_strlen("<<") + 1) == 0))
			return(1);
		else if ((ft_strncmp(word, ">>", ft_strlen(">>") + 1) == 0))
			return(1);
/*		else if ((ft_strncmp(word, "|", ft_strlen("|") + 1) == 0))
			return(1);*/
		return(0);
 }

/*void tokenize_redir(char **words, t_data *data)
{
	int i;
	int j;
	int	count;
	char	**redirs;

	i = -1;
	count = 0;
	while (words[++i] != NULL)
	{
		if (is_redir(words[i]))
			count++;
	}
	i = -1;
	redirs = (char **)malloc(sizeof(char *) * (count + 1));
	j = 0;
    while (words[++i] != NULL)
    {
        if (is_redir(words[i]))
		{
			redirs[j] = ft_strdup(words[i]);
			j++;
		}
    }
	redirs[j] = NULL;
	data->redirs = redirs;
	i = 0;
}*/

char	**destroy_redirections(char **words)
{
	int	i;
	int	j;
	int	count;
	char	**words_copy;

	i = -1;
	count = 0;
	while (words[++i] != NULL)
	{
		if (is_redir(words[i]) == 0)
			count++;
		if (is_redir(words[i]) == 1)
			i++;
	}
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
	int i = 0;
	tokenize_outfile(words, data);
	tokenize_infile_heredoc(words, data);
    /*while (words[i] != NULL)
	{
        printf("words pred cistkou: %s\n", words[i]);
        i++;
    }*/
	words = destroy_redirections(words);
	/*i = 0;
    while (words[i] != NULL)
	{
        printf("words po cistce:%s\n", words[i]);
        i++;
    }*/
	tokenize_command(words, data);
	ft_command_check(data);
	i = 0;
	while (data->commands[i])
	{
        printf("after check commands[%d] :%s\n",i, data->commands[i]);
		i++;
    }
	data->args = argument_parser(data->commands, data->args);
	printf("infile fd = %d\n", data->infile);
	printf("outfile fd = %d\n", data->outfile);
	free_split(words);
}


int	ft_prompt_crossroad(const char *input, t_data *data)
{
	char	**words;

	if(!input)
		return (1);
	words = ft_split(prepare_quoted_string(input), 29);
	words = replace_env_var_nonquated (words);
	words = parse_double_quated_strings(words);
	words = substitution(words); 
	//tester
	/*printf("\ntest formated_words\n");
	i = 0;
    while (words[i] != NULL)
	{
        printf("%s\n", words[i]);
        i++;
    }
	printf("\n");*/
	//konec testru
	lexer(words, data);
	
	data->last_command = commands_counting(data->commands) - 1;
	int i = 0;
    while (data->args[i])
	{
        int j = 0;
        while (data->args[i][j])
		{
            printf("args[%d][%d]: %s\n", i, j, data->args[i][j]);
            j++;
        }
        i++;
    }
	ft_executor_binary(data);
	return (1);
}
 