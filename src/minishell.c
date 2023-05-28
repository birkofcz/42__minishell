/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:28:41 by sbenes            #+#    #+#             */
/*   Updated: 2023/05/28 11:48:46 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_set_envdata(t_env *env)
{
	env->user = getenv("USER");
	//fill up the structure with usefull environmental variables
	// may need to call this when updating after pwd, cd and stuff?
}

void	ft_prompt(t_env *env)
{
	printf("%s%s%s@%sminishell%s>> ", BG, env->user, RES, BC, RES);
}


int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
	char	*input;
	t_env	env;

	ft_set_envdata(&env);
	while (1)
	{
		ft_prompt(&env);
		input = readline("");
		// some function crossroad to handle the input
		// using temporary code
		if (ft_strncmp(input, "exit", ft_strlen(input)) == 0)
		{
			free(input);
			return (0);
		}
		else
		{
			add_history(input);
			free(input);
		}
	}
}
