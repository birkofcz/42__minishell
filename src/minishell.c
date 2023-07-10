/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:28:41 by sbenes            #+#    #+#             */
/*   Updated: 2023/07/10 14:18:08 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int g_exit;

static char	**ft_alloc_env(void)
{
	int		size;
	int		i;
	char	**minishell_env;

	size = 0;
	i = -1;
	while (environ[size] != NULL)
		size++;
	minishell_env = malloc((size + 1) * sizeof(char *));
	while (++i < size)
		minishell_env[i] = ft_strdup(environ[i]);
	minishell_env[i] = NULL;
	return (minishell_env);
}

static void	ft_clean_init(t_data *data)
{
	data->commands = NULL;
	data->last_command = -1;
	data->args = NULL;
	data->infile = -1;
	data->delimiter = NULL;
	data->redirs = NULL;
	data->outfile = -1;
	data->saved_stdin = -1;
	data->saved_stdout = -1;
}

void	ft_initialize_data(t_data *data)
{
	int	index;

	index = ft_checkforexisting("SHELL");
	data->commands = NULL;
	data->last_command = -1;
	data->args = NULL;
	data->infile = -1;
	data->delimiter = NULL;
	data->redirs = NULL;
	data->outfile = -1;
	data->saved_stdin = -1;
	data->saved_stdout = -1;
	data->minishell_env = ft_alloc_env();
	environ = data->minishell_env;
	ft_rewrite(index, "SHELL=[TS]minishell");
}

void	ft_read(t_data *data)
{
	char	*input;
	char	*prompt;

	prompt = ft_strjoin(getenv("USER"), "@\033[96m[TS]minishell\033[0m>> ");
	input = readline(prompt);
	if (input == NULL)
	{
		write(1, "exit\n", 5);
		free(prompt);
		exit(0);
	}
	else if (input[0] != '\0')
	{
		add_history(input);
		ft_clean_init(data);
		ft_parser(input, data);
		data->last_command = commands_counting(data->commands) - 1;
		if (data->last_command >= 0)
			ft_executor(data);
	//mozna treba free(data->commands), args?
	}
	free(input);
	free(prompt);
}

int	main(void)
{
	t_data	data;

	ft_initialize_data(&data);
	signal(SIGINT, ft_sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
		ft_read(&data);
	return (0);
}
