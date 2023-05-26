/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fptacek <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 19:47:48 by fptacek           #+#    #+#             */
/*   Updated: 2023/04/26 11:59:55 by fptacek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_pipe(int *pfd)
{
	close(pfd[0]);
	close(pfd[1]);
}

void	child_1(int *pfd, char *argv[], char *envp[])
{
	int	fd;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		perror("open 1");
	if (close(pfd[0]) == -1)
		perror("close 1");
	if (dup2(pfd[1], STDOUT_FILENO) == -1)
		perror("dup2 1");
	if (dup2(fd, STDIN_FILENO) == -1)
		perror("dup2 2");
	execute(argv[2], envp);
	close(fd);
}

void	child_2(int *pfd, char *argv[], char *envp[])
{
	int	fd;

	fd = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
		perror("open 2");
	if (close(pfd[1]) == -1)
		perror("close 2");
	if (dup2(pfd[0], STDIN_FILENO) == -1)
		perror("dup2 3");
	if (dup2(fd, STDOUT_FILENO) == -1)
		perror("dup2 4");
	execute(argv[3], envp);
	close(fd);
}

int	main(int argc, char *argv[], char *envp[])
{
	int		pfd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (argc != 5)
		perror("Wrong input!");
	if (pipe(pfd) == -1)
		perror("pipe");
	pid1 = fork();
	if (pid1 == -1)
		perror("fork 1");
	if (pid1 == 0)
		child_1(pfd, argv, envp);
	waitpid(pid1, NULL, 0);
	pid2 = fork();
	if (pid2 == -1)
		perror("fork 2");
	if (pid2 == 0)
		child_2(pfd, argv, envp);
	close_pipe(pfd);
	waitpid(pid2, NULL, 0);
	return (0);
}
