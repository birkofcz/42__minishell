/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:30:39 by sbenes            #+#    #+#             */
/*   Updated: 2023/06/01 14:04:19 by sbenes           ###   ########.fr       */
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
# define MAX_PATH_LENGTH 1024	

/* Structs and typedefs */
typedef struct s_envdata
{
	char	*user;
	char	*pwd;
	char	*home;
}	t_env;

/* Environmental variables storage */
extern char	**environ;

/* Functions by files */

/* prompt_crossroad.c */
void	ft_prompt_crossroad(const char *input, t_env *env);
int		word_counting(char **words);
char	**parse_double_quated_strings(char **words);
char	*prepare_double_quoted_string(const char *input);

/* builtins_pwd_cd.c */
void	ft_pwd(t_env *env, int words_count);
void	ft_cd(t_env *env, char **arg, int words_count);

/* buldin_echo.c */
void	ft_echo(char **words, int fd);
void	ft_echoprint(char **words, int i, int fd);

/* builtin_env.c */
void	ft_env(int fd);

/* builtin_export.c */
int		ft_checkforexisting(char *var);
void	ft_rewrite(int index, char *var);
void	ft_add(char *var);
char	*ft_checkarg(char *arg);
void	ft_export(char **words);

/* builtin_unset.c */
void	ft_unset(char **words);




#endif