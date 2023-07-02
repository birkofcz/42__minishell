/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:28:41 by sbenes            #+#    #+#             */
/*   Updated: 2023/07/02 20:14:45 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int g_exit;

static	char **ft_alloc_env(void)
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

void	ft_initialize_data(t_data *data)
{
	int	index;

	index = ft_checkforexisting("SHELL");
	data->commands = NULL;
	data->last_command = 0;
	data->args = NULL;
	data->infile = -1;
	data->delimiter = NULL;
	data->redirs = NULL;
	data->outfile = -1;
	data->minishell_env = ft_alloc_env();
	environ = data->minishell_env;
	ft_rewrite(index, "SHELL=[TS]minishell");

	
	/*printf("TESTPRINT OF MINISHELL_ENV\n");
	int i = 0;
	while (data->minishell_env[i] != NULL)
	{
		printf("%s\n", data->minishell_env[i]);
		i++;
	}*/
	//data->saved_stdin;
	//data->saved_stdout;
	//fill up the structure with usefull environmental variables
	// may need to call this when updating after pwd, cd and stuff?
	
	//// getenv takes the initial environment data and doesnt update it.
	//// To get updated PWD we have to use the getcwd function.
}

int	ft_read(t_data *data)
{
	char	*input;
	char	*prompt;
	int		exit_l; //making the loop of readline to continue

	prompt = ft_strjoin(getenv("USER"), "@\033[96m[TS]minishell\033[0m>> ");
	input = readline(prompt);
	exit_l = 1;
	if (input == NULL)
	{
		write(1, "exit\n", 5);
		exit(0);
	}
	if (input && input[0] != '\0')
	{
		add_history(input);
		ft_initialize_data(data);
		exit_l = ft_prompt_crossroad(input, data);
		free(input);
	}
	free(prompt);
	return (exit_l);
}

int	main(int ac, char **av, char **environ)
{
	t_data	data;

	(void)ac;
	(void)av;
	(void)environ;
	ft_initialize_data(&data);
	signal(SIGINT, ft_sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	while (ft_read(&data))
	{
		(void)environ;
	}

	return (0);
}
