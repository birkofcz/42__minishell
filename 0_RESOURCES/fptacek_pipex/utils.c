/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fptacek <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 19:48:11 by fptacek           #+#    #+#             */
/*   Updated: 2023/04/26 12:06:28 by fptacek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

char	*find_whole_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

char	*find_path(char *cmd, char *envp[])
{
	char	**paths;
	char	*whole_path;
	char	*add_slash;
	char	*single_path;
	int		i;

	i = 0;
	whole_path = find_whole_path(envp);
	if (!whole_path)
		perror("find whole path");
	paths = ft_split(whole_path, ':');
	while (paths[i])
	{
		add_slash = ft_strjoin(paths[i], "/");
		single_path = ft_strjoin(add_slash, cmd);
		free(add_slash);
		if (access(single_path, F_OK) == 0)
			return (single_path);
		free(single_path);
		i++;
	}
	free_paths(paths);
	return (0);
}

void	execute(char *argv, char *envp[])
{
	char	**command;
	char	*path;
	int		i;

	i = 0;
	command = ft_split(argv, ' ');
	path = find_path(command[0], envp);
	if (!path)
	{
		while (command[i])
		{
			free(command[i]);
			i++;
		}
		free(command);
		perror("path");
		exit(EXIT_FAILURE);
	}
	if (execve(path, command, envp) == -1)
	{
		perror("exe");
		exit(EXIT_FAILURE);
	}
}
