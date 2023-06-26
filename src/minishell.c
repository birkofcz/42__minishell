/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:28:41 by sbenes            #+#    #+#             */
/*   Updated: 2023/06/26 15:42:37 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	data->commands = NULL;
	data->last_command = 0;
	data->args = NULL;
	data->infile = -1; //fd infilu
	data->delimiter = NULL;
	data->redirs = NULL;
	data->outfile = -1;
	data->minishell_env = ft_alloc_env();
	environ = data->minishell_env;
	int i = 0;
	
	while (data->minishell_env[i] != NULL)
	{
		printf("%s\n", data->minishell_env[i]);
		i++;
	}
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
	int		exit;

	prompt = ft_strjoin(getenv("USER"), "@\033[96mminishell\033[0m>> ");
	input = readline(prompt);
	//Here we put some crossroad function to read the lines commad
	//using basic function to test here
	//testing ft_prompt_crossroad() - as a crossroad
	exit = 0;
	if (input)
	{
		add_history(input);
		ft_initialize_data(data);
		exit = ft_prompt_crossroad(input, data);
		free(input); 
	}
	free(prompt);
	return (exit);
}

int	main(int ac, char **av, char **environ)
{
	(void)ac;
	(void)av;
	(void)environ;
	t_data 	data;
	
	ft_initialize_data(&data);
	while (ft_read(&data))
		(void)environ;
	return (0);
}
