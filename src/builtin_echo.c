/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 15:07:25 by sbenes            #+#    #+#             */
/*   Updated: 2023/06/22 17:20:39 by sbenes           ###   ########.fr       */
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

void	ft_write_expander_num(char *word)
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
			write(1, num_str, ft_strlen(num_str));
			free(num_str);  // Remember to free the allocated string!
			if (start_int != end_int)
				write(1, " ", 1);
			start_int++;
		}
	}
	else
	{
		while (start_int >= end_int)
		{
			num_str = ft_itoa(start_int);
			write(1, num_str, ft_strlen(num_str));
			free(num_str);  // Remember to free the allocated string!
			if (start_int != end_int)
				write(1, " ", 1);
			start_int--;
		}
	}
}

void	ft_echo_expander(char *word)
{
	int		dots;
	int		spaces;
	int		i;
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
		//NEPROJDE TIMTO IF - opravit
		
		if ((ft_isdigit(split[0][0]) && ft_isdigit(split[0][1])) && (ft_isdigit(split[1][0]) && ft_isdigit(split[1][1])) && dots == 2)
		{
			ft_write_expander_num(word);
		}
		else
			write(1, word, ft_strlen(word));
	}
	///TADY JE POTREBA UPRAVA NA PARSE ARGUMENTS = V PRIPADE { 1..6}, VRACI DVE SLOVA - { A 1..6}.
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
