/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_crossroad.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 13:40:19 by sbenes            #+#    #+#             */
/*   Updated: 2023/06/17 18:04:26 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
/* 
FT_PROMPT_CROSSROAD
function to read the input a set a proper function into motion
 */

//something like this - may do a int type to return the errors?

//to do: osetrit pokud je input NULL
 /*char *analyze(char **words, t_data *data)
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
}*/
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


/* do we need this shit? */
void tokenize_redir(char **words, t_data *data)
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
}

int	is_command(char *word)
{
	if (ft_strncmp(word, "echo", ft_strlen("echo") + 1) == 0)
    	return(1);
	else if (ft_strncmp(word, "pwd", ft_strlen("pwd") + 1) == 0)
		return(1);
	else if (ft_strncmp(word, "cd", ft_strlen("cd") + 1) == 0)
		return(1);
	else if (ft_strncmp(word, "env", ft_strlen("env") + 1) == 0)
		return(1);
	else if (ft_strncmp(word, "export", ft_strlen("export") + 1) == 0)
		return(1);
	else if (ft_strncmp(word, "unset", ft_strlen("unset") + 1) == 0)
		return(1);
	else if (ft_strncmp(word, "clear", ft_strlen("clear") + 1) == 0)
		return(1);
	else if (ft_strncmp(word, "exit", ft_strlen("exit") + 1) == 0)
		return(1);
	else if (ft_strchr(word, '/') != NULL)
		return(1);
	return (0);
}

int	args_counter(char **words, int i)
{
	int	count;
	int command;

	count = 0;
	command = 0;
	while (words[i] != NULL && command != 2 && ((is_redir(words[i]) == 1) || (is_command(words[i]) == 1) || (ft_strncmp(words[i], "|", ft_strlen("|") + 1) == 0)))
	{
		if (is_redir(words[i]) == 1)
			i++;
		if ((is_command(words[i]) == 1))
			command ++;
		i++;
	}
	if (command == 2)
		i --;
	while (words[i] != NULL && (is_redir(words[i]) == 0) && (is_command(words[i]) == 0) && (ft_strncmp(words[i], "|", ft_strlen("|") + 1) != 0))
	{
		count ++;
		i++;
	}
	printf ("args_count = %d\n", count);
	return (count);
}

void	tokenize_arg(char **words, t_data *data, int count) //predelat na druhem miste muze byt infile
{
	int i;
	int j;
	int k;
	int command;
	char	***args;

	i = 0;
	j = 0;
	k = 0;
	printf ("command count : %d\n", count);
	args = (char ***)malloc(sizeof(char **) * (count + 1));//command_count
	while (words[i] != NULL)
	{
		count = args_counter (words, i);
		printf ("argument count : %d\n", count);
		if (count == 0)
		{
			args[j] = (char **)malloc(sizeof(char *) * (2));
		}
		else
			args[j] = (char **)malloc(sizeof(char *) * (count + 1));
		command = 0;
		while (words[i] != NULL && command != 2 &&((is_redir(words[i]) == 1) || (is_command(words[i]) == 1) || (ft_strncmp(words[i], "|", ft_strlen("|") + 1) == 0)))
		{
			if (is_redir(words[i]) == 1)
				i++;
			if ((is_command(words[i]) == 1))
				command ++;
			i++;
		}
		if (command == 2)
			i --;
		while (count != 0 && words[i] != NULL && (is_redir(words[i]) == 0) && (is_command(words[i]) == 0) && (ft_strncmp(words[i], "|", ft_strlen("|") + 1) != 0))
		{
			args[j][k] = ft_strdup(words[i]);
			k++;
			i++;
		}
		args[j][k] = NULL;
		k = 0;
		j++;
		if (words[i] == NULL)
			break ;
	}
	args[j] = NULL;
	data->args = args;
}

void	tokenize_command(char **words, t_data *data)
{
	int i;
	int j;
	int	count;
	char	**commands;

	i = -1;
	count = 0;
	
	while (words[++i] != NULL)
	{
		if ((is_command(words[i]) ))
			count ++;
	}
	i = -1;
	commands = (char **)malloc(sizeof(char *) * (count + 1));
	j = 0;
	while (words[++i] != NULL)
	{
		if (is_command(words[i]))
		{
			commands[j] = ft_strdup(words[i]);
			j++;
		}
	}
	commands[j] = NULL;
	data->commands = commands;
	i = 0;
	tokenize_arg(words, data, count);
}

void	tokenize_infile(char **words, t_data *data)
{
	int i;

	i = - 1;
	data->infile = -1;
	while (words[++i] != NULL)
	{
		if (ft_strncmp(words[i], "<", ft_strlen("<") + 1) == 0)
			data->infile = open(words[i + 1], O_RDONLY, 0777);
	}
}

void	tokenize_outfile(char **words, t_data *data)
{
	int i;
	int j;
	int count;
	int *outfile;

	count = 0;
//infile
//if [0] == <, pak [i] = infile

//outfile
	i = - 1;
	j = 0;
	while (words[++i] != NULL)
	{
		if ((ft_strncmp(words[i], ">", ft_strlen(">") + 1) == 0) || (ft_strncmp(words[i], ">>", ft_strlen(">>") + 1) == 0))
			count++;
	}
	outfile = (int *)malloc(sizeof(int) * (count + 1));//uzavrit 0
	i = - 1;
	while (words[++i] != NULL)
	{
		if (ft_strncmp(words[i], ">>", ft_strlen(">>") + 1) == 0)
		{
			outfile[j] = open(words[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
			j++;
		}
		else if (ft_strncmp(words[i], ">", ft_strlen(">") + 1) == 0)
		{
			outfile[j] = open(words[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
			j++;
		}
	}
	data->outfile = outfile;
	data->outfile_count = count;
}

void	lexer(char **words, t_data *data)
{
	tokenize_redir(words, data);
	tokenize_command(words, data);
	int i = 0;
	while (data->commands[i])
	{
        printf("commands[%d] :%s\n",i, data->commands[i]);
		i++;
    }
	/*i = 0;
	while (data->args[0][i])
	{
        printf("args[0][%d] :%s\n",i, data->args[0][i]);
		i++;
    }
	i = 0;
	while (data->args[1][i])
	{
        printf("args[1][%d] :%s\n",i, data->args[1][i]);
		i++;
    }*/
	tokenize_outfile(words, data);
	tokenize_infile(words, data);
	printf("infile fd = %d\n", data->infile);
	printf("outfile fd = %d\n", data->outfile[0]);
	write(1, "test lexer\n", 11);
	//printf("infile : %d, outfile[0] = %d, outfile[1] = %d, outfile count = %d\n", data->infile, data->outfile[0], data->outfile[1], data->outfile_count);
	//tokenize_heredoc(words, data);
}

int	ft_prompt_crossroad(const char *input, t_data *data)
{
	char	**words;

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
	i = 0;/*
	while (data->args[1][i])
	{
        printf("args[1][%d] :%s\n",i, data->args[1][i]);
		i++;
    }
	i = 0;
    printf("args[2][%d] :%p\n",i, data->args[2]);*/
	/*if (ft_strncmp(words[0], "echo", ft_strlen("echo") + 1) == 0)
    	ft_echo(words, 1);
	else if (ft_strncmp(words[0], "pwd", ft_strlen("pwd") + 1) == 0) // $blabla pwd -> by melo fungovat
		ft_pwd(env, words_count);
	else if (ft_strncmp(words[0], "cd", ft_strlen("cd") + 1) == 0)
		ft_cd(env, words, words_count);
	else if (ft_strncmp(words[0], "env", ft_strlen("env") + 1) == 0)
		ft_env(1);
	else if (ft_strncmp(words[0], "export", ft_strlen("export") + 1) == 0)
		ft_export(words);
	else if (ft_strncmp(words[0], "unset", ft_strlen("unset") + 1) == 0)
		ft_unset(words);
	else if (ft_strncmp(words[0], "clear", ft_strlen(words[0])) == 0)
		printf("\033[2J\033[1;1H");
	else if (ft_strncmp(words[0], "exit", ft_strlen("exit") + 1) == 0)
		return (free_args(words),0);
	else*/
	ft_executor_binary(data);
	return (free_split(words), 1);
}
