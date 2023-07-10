/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 16:08:30 by sbenes            #+#    #+#             */
/*   Updated: 2023/07/10 08:13:21 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* 
FT_CHECKFOREXISTING - loops through minishell env, check if var exists there.
If so, returs index. Else returns erorr.
 */
int	ft_checkforexisting(char *var)
{
	int		i;
	char	**split;

	i = 0;
	while (environ[i] != NULL)
	{
		split = ft_split(environ[i], '=');
		if (ft_strncmp(split[0], var, ft_strlen(var)) == 0)
		{
			free_split(split);
			return (i);
		}
		else
			free_split(split);
		i++;
	}
	return (-1);
}

/* 
FT_CHECKARG - checks the argument format
 */
char	*ft_checkarg(char *arg)
{
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	if (!ft_isalpha(arg[i]))
		return (NULL);
	while (arg[i] != '\0')
	{
		if (arg[i] == '=')
			flag++;
		i++;
	}
	i = -1;
	while (arg[++i] != '=')
		if ((!ft_isalnum(arg[i])) && arg[i] != '_')
			return (NULL);
	if (flag == 0)
		return (NULL);
	else if (flag == 1 && arg[0] != '=' && arg[i - 1] != '=')
		return (arg);
	else
		return (NULL);
}
