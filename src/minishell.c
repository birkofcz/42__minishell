/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:28:41 by sbenes            #+#    #+#             */
/*   Updated: 2023/06/01 17:57:52 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_set_envdata(t_env *env)
{
	env->user = getenv("USER");
	env->pwd = getenv("PWD");
	env->home = getenv("HOME");
	//fill up the structure with usefull environmental variables
	// may need to call this when updating after pwd, cd and stuff?
	
	//// getenv takes the initial environment data and doesnt update it.
	//// To get updated PWD we have to use the getcwd function.
}

int	ft_read(t_env *env)
{
	char	*input;
	char	*prompt;
	int		exit;

	prompt = ft_strjoin(env->user, "@\033[96mminishell\033[0m>> ");
	input = readline(prompt);
	//Here we put some crossroad function to read the lines commad
	//using basic function to test here
	//testing ft_prompt_crossroad() - as a crossroad
	exit = 0;
	if (input)
	{
		add_history(input);
		exit = ft_prompt_crossroad(input, env);
		free(input); //uvolnit pred exitem
	}
	free(prompt);
	return (exit);//uvolnit pred exitem
}


int	main(int ac, char **av, char **envir)
{
	(void)ac;
	(void)av;
	(void)envir;
	t_env	env;

	ft_set_envdata(&env);
	while (ft_read(&env))
		(void)envir;
	return (0);
}
