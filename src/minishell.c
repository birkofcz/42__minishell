/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:28:41 by sbenes            #+#    #+#             */
/*   Updated: 2023/06/22 15:31:32 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_initialize_data(t_data *data)
{
	data->commands = NULL;
	data->last_command = 0;
	data->args = NULL;
	data->infile = -1; //fd infilu
	data->delimiter = NULL;
	data->redirs = NULL; 
	data->outfile = -1;
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
