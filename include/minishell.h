/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:30:39 by sbenes            #+#    #+#             */
/*   Updated: 2023/06/20 14:54:46 by tkajanek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* Preprocessor header files */
# include "../libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

/* Colors for program */
# define BG "\033[92m"
# define BC "\033[96m"
# define RES "\033[0m"

/* Redirs macros */
# define OUTFILE ">"
# define INFILE "<"
# define PIPE "|"
# define HEREDOC "<<"

/* constants*/
# define MAX_PATH_LENGTH 1024	

/* Structs and typedefs */
typedef struct s_data
{
	char **commands; //alocated
	int	last_command;
	char ***args; //alocated
	int 	infile; //fd infilu
	char * delimiter; //alocated
	char **redirs; 
	//char ***redirections;
	int	*outfile;//allocated
	int	outfile_count;
	int saved_stdin;
	int	saved_stdout;
}	t_data;

/* Environmental variables storage */
extern char **environ;

/* Functions by files */

/* prompt_crossroad.c */
int	ft_prompt_crossroad(const char *input, t_data *data);
int	is_redir(char *word);

/* parsing_quotes_env_vars.c */
char *prepare_quoted_string(const char *input);
char **parse_double_quated_strings(char **words);
char **replace_env_var_nonquated (char **words);
char	*dollar_check(char *word);

 /* in_outfiles.c */
void	tokenize_outfile(char **words, t_data *data);
void	tokenize_infile_heredoc(char **words, t_data *data);

/* tokenize_commands_args.c */
int	is_command(char *word);
int	args_counter(char **words, int i);
void	tokenize_arg(char **words, t_data *data, int count);
void	tokenize_command(char **words, t_data *data);

/* builtins_pwd_cd.c */
//void	ft_pwd(t_env *env, int words_count);
//void	ft_cd(t_env *env, char **arg, int words_count);

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

/*executor_binary.c*/
void	ft_executor_binary(t_data *data);
void	executor_experim(t_data *data);
void	ft_executor_binary_exp(t_data *data);

/* executor.c */
void	ft_executor(char **words, t_data *data);

/* heredoc.c */
void	ft_heredoc(char *delimiter);

/* utils.c*/
int	commands_counting(char **words);
void 	free_split(char **args);
void 	free_args(char ***args);
void	free_command_table(t_data *data);

#endif
