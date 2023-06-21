/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 15:07:25 by sbenes            #+#    #+#             */
/*   Updated: 2023/06/21 17:15:49 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_write_expander_char(char *word, int fd)
{
	char	start_char;
	char	end_char;

	start_char = word[1];
	end_char = word[ft_strlen(word) - 2];
	if (start_char < end_char)
	{
		while (start_char <= end_char)
		{
			write(fd, &start_char, 1);
			if (start_char != end_char)
				write(fd, " ", 1);
			start_char++;
		}
	}
	else
	{
		while (start_char >= end_char)
		{
			write(fd, &start_char, 1);
			if (start_char != end_char)
				write(fd, " ", 1);
			start_char--;
		}
	}
}

void	ft_write_expander_num(char *word, int fd)
{
	int		start_int;
	int		end_int;
	char	*num_str;
	char	**split;
	char	*temp;

	temp = ft_strtrim(word, "{}");
	split = ft_split(temp, '.');
	start_int = ft_atoi(split[0]);
	end_int = ft_atoi(split[1]);
	if (start_int < end_int)
	{
		while (start_int <= end_int)
		{
			num_str = ft_itoa(start_int);
			write(fd, num_str, ft_strlen(num_str));
			free(num_str);  // Remember to free the allocated string!
			if (start_int != end_int)
				write(fd, " ", 1);
			start_int++;
		}
	}
	else
	{
		while (start_int >= end_int)
		{
			num_str = ft_itoa(start_int);
			write(fd, num_str, ft_strlen(num_str));
			free(num_str);  // Remember to free the allocated string!
			if (start_int != end_int)
				write(fd, " ", 1);
			start_int--;
		}
	}
}

void	ft_echo_expander(char *word, int fd)
{
	int	dots;
	int	spaces;
	int	i;
	char	**split;
	char	*temp;

	dots = 0;
	spaces = 0;
	i = -1;
	while (word[++i] != '\0')
	{
		if (word[i] == '.')
			dots++;
		else if (word[i] == ' ')
			spaces++;
	}
	temp = ft_strtrim(word, "{}");
	split = ft_split(temp, '.');
	//FREEEEEEEEEEEEEEEE NA SPLIT A TEMP!
	if ((ft_strlen(split[0]) > 1) || ft_strlen(split[1]) > 1)
	{
		if ((ft_isdigit(split[0][0]) && ft_isdigit(split[0][1])) && (ft_isdigit(split[1][0]) && ft_isdigit(split[1][1])) && dots == 2)
			ft_write_expander_num(word, fd);
		else
			write(fd, word, ft_strlen(word));
	}
	///TADY JE POTREBA UPRAVA NA PARSE ARGUMENTS = V PRIPADE { 1..6}, VRACI DVE SLOVA - { A 1..6}.
	else if (spaces != 0)
		write(fd, "parse error\n", 13);
	else if (dots == 2)
		ft_write_expander_char(word, fd);
	else
		write(fd, word, ft_strlen(word));
}

void	ft_echoprint(char **args, int i, int fd)
{
	while (args[i] != NULL)
	{
		//POZOR, strtrim alokuje novy string, stare args[i] je treba uvolnit free
		//Taking care of various cases with $ sign + error management
		if (args[i][0] == '{' && args[i][ft_strlen(args[i]) -1 ] == '}')
			ft_echo_expander(args[i], fd);
		else if (args[i][0] == '$')
		{
			if (args[i][1] != '\0' && (getenv(&args[i][i]) != NULL))
				write(fd, getenv(&args[i][1]), ft_strlen(getenv(&args[i][1])));
			// LAST EXIT STATUS FOR ECHO $?
			/*else if (args[i][1] == '?' && args[i][2] == '\0')
				write(fd, ft_itoa(g_exit_status), ft_strlen(ft_itoa(g_exit_status)));*/
			else if (args[i][1] != '\0' && !(getenv(&args[i][1])))
				break ;
			else
				write(fd, "$", 1);
		}
		//else printing word
		else
			write(fd, args[i], ft_strlen(args[i]));
		if (args[i + 1] != NULL)
			write(fd, " ", 1);
		i++;
	}
}

void	ft_echo(char **args, int fd)
{
	if (!args[0])
		write(fd, "\n", 1);
	else if (ft_strncmp(args[0], "-n", ft_strlen(args[0])) == 0)
		ft_echoprint(args, 1, fd);
	else
	{
		ft_echoprint(args, 0, fd);
		write(fd, "\n", 1);
	}
}

/* EXECVE version */
/* void	ft_echo(char **args, int fd)
{
	(void)fd;
	int pid = fork();
	if (pid < 0)
	{
		printf("Fork failed.\n");
		return ;
	}
	if (pid == 0)
	{
		execve("/usr/bin/echo", args, NULL);
		printf("Failed to execute execve.\n");
		exit(1);
	}
	else
		wait(NULL);
} */