/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:28:41 by sbenes            #+#    #+#             */
/*   Updated: 2023/05/29 16:24:26 by tkajanek         ###   ########.fr       */
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

void	ft_read(t_env *env)
{
	char	*input;
	char	*prompt;

	prompt = ft_strjoin(env->user, "@\033[96mminishell\033[0m>> ");
	input = readline(prompt);
	//Here we put some crossroad function to read the lines commad
	//using basic function to test here
	//testing ft_prompt_crossroad() - as a crossroad
	if (input)
	{
		ft_prompt_crossroad(input, env);
		add_history(input);
		free(input);
	}
	free(prompt);
}


int	main(int ac, char **av, char **envir)
{
	(void)ac;
	(void)av;
	(void)envir;
	t_env	env;

	ft_set_envdata(&env);
	while (1)
	{
		ft_read(&env);
	}
	return (0);
}
