/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:24:30 by sbenes            #+#    #+#             */
/*   Updated: 2023/07/11 16:02:22 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"	

void	ft_pwd_fork(char **args, t_data *data)
{
	char	cwd[MAX_PATH_LENGTH];

	(void) args;
	if (getcwd(cwd, MAX_PATH_LENGTH) != NULL)
		printf("%s\n", cwd);
	fork_exit(0, data);
}

int	ft_pwd_nonfork(char **args)
{
	char	cwd[MAX_PATH_LENGTH];

	(void) args;
	if (getcwd(cwd, MAX_PATH_LENGTH) != NULL)
		printf("%s\n", cwd);
	return (0);
}
