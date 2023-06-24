/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 15:07:25 by sbenes            #+#    #+#             */
/*   Updated: 2023/06/24 17:44:42 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_write_expander_char(char *word)
{
	char	start_char;
	char	end_char;

	start_char = word[1];
	end_char = word[ft_strlen(word) - 2];
	if (start_char < end_char)
	{
		while (start_char <= end_char)
		{
			write(1, &start_char, 1);
			if (start_char != end_char)
				write(1, " ", 1);
			start_char++;
		}
	}
	else
	{
		while (start_char >= end_char)
		{
			write(1, &start_char, 1);
			if (start_char != end_char)
				write(1, " ", 1);
			start_char--;
		}
	}
}

void	ft_write_expander_num(char **splitted_args)
{
	int		start_int;
	int		end_int;

	start_int = ft_atoi(splitted_args[0]);
	end_int = ft_atoi(splitted_args[1]);
	free_split(splitted_args);
	if (start_int < end_int)
	{
		while (start_int <= end_int)
		{
			ft_putnbr_fd(start_int, 1);
			if (start_int != end_int)
				write(1, " ", 1);
			start_int++;
		}
	}
	else
	{
		while (start_int >= end_int)
		{
			ft_putnbr_fd(start_int, 1);
			if (start_int != end_int)
				write(1, " ", 1);
			start_int--;
		}
	}
}

int	ft_count_spaces(char *arg)
{
	int	i;
	int	spaces;

	spaces = 0;
	i = -1;
	while (arg[++i] != '\0')
	{
		if (arg[i] == ' ')
			spaces++;
	}
	return (spaces);
}

int	ft_count_dots(char *arg)
{
	int	i;
	int	dots;

	dots = 0;
	i = -1;
	while (arg[++i] != '\0')
	{
		if (arg[i] == '.')
			dots++;	
	}
	return (dots);
}

void	ft_echo_expander(char *word)
{
	int		dots;
	int		spaces;
	char	**split;
	char	*temp;

	dots = ft_count_dots(word);
	spaces = ft_count_spaces(word);
	temp = ft_strtrim(word, "{}");
	split = ft_split(temp, '.');
	//FREEEEEEEEEEEEEEEE NA SPLIT A TEMP!
	if ((ft_strlen(split[0]) > 1) || ft_strlen(split[1]) > 1)
	{
		if ((ft_isdigit_array(split) == 0) && dots == 2)
			ft_write_expander_num(split);
		else
			write(1, word, ft_strlen(word));
	}
	else if (spaces != 0)
		write(1, "parse error\n", 13);
	else if (dots == 2)
		ft_write_expander_char(word);
	else
		write(1, word, ft_strlen(word));
}

void	ft_echoprint(char **args, int i)
{
	while (args[i] != NULL)
	{
		//POZOR, strtrim alokuje novy string, stare args[i] je treba uvolnit free
		//Taking care of various cases with $ sign + error management
		if (args[i][0] == '{' && args[i][ft_strlen(args[i]) -1 ] == '}')
			ft_echo_expander(args[i]);
		else if (args[i][0] == '$')
		{
			if (args[i][1] != '\0' && (getenv(&args[i][i]) != NULL))
				write(1, getenv(&args[i][1]), ft_strlen(getenv(&args[i][1])));
			// LAST EXIT STATUS FOR ECHO $?
			/*else if (args[i][1] == '?' && args[i][2] == '\0')
				write(fd, ft_itoa(g_exit_status), ft_strlen(ft_itoa(g_exit_status)));*/
			else if (args[i][1] != '\0' && !(getenv(&args[i][1])))
				break ;
			else
				write(1, "$", 1);
		}
		//else printing word
		else
			write(1, args[i], ft_strlen(args[i]));
		if (args[i + 1] != NULL)
			write(1, " ", 1);
		i++;
	}
}

void	ft_echo(char **args)
{
	if (!args[1])
		write(1, "\n", 1);
	else if (ft_strncmp(args[1], "-n", ft_strlen(args[0])) == 0)
		ft_echoprint(args, 2);
	else
	{
		ft_echoprint(args, 1);
		write(1, "\n", 1);
	}
}
