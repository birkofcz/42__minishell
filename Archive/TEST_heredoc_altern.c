
#include "../include/minishell.h"

void	ft_heredoc(char *delimiter)
{
	int		fd[2];
	char	*heredoc_line;

	if (pipe(fd) == -1)
		return ;
	heredoc_line = "";
	while (ft_strncmp(heredoc_line, delimiter, ft_strlen(delimiter)) != 0)
	{
			heredoc_line = readline("\033[96mheredoc>\033[0m ");
			write(fd[1], heredoc_line, ft_strlen(heredoc_line));
			write(fd[1], "\n", 1);
	}
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]); //jakto ze funguje ??
}
