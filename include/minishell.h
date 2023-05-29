/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:30:39 by sbenes            #+#    #+#             */
/*   Updated: 2023/05/29 16:22:38 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* Preprocessor header files */
# include "../libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

/* Colors for program */
# define BG "\033[92m"
# define BC "\033[96m"
# define RES "\033[0m"

/* constants*/
#define MAX_PATH_LENGTH 1024	

/* Structs and typedefs */
typedef struct s_envdata
{
	char	*user;
	char	*pwd;
	char	*home;
}	t_env;

/* Functions by files */

/* prompt_crossroad.c */
void	ft_prompt_crossroad(const char *input, t_env *env);

/* argument parsing*/
int	word_counting(char **words);

/* commands */
void	ft_pwd(t_env *env, int words_count);
void	ft_cd(t_env *env, char **arg, int words_count);

/* buldin_echo.c */
void	ft_echo(char **words);
void	ft_echoprint(char **words, int i);


#endif