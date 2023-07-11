/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkajanek <tkajanek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:30:39 by sbenes            #+#    #+#             */
/*   Updated: 2023/07/11 15:02:37 by tkajanek         ###   ########.fr       */
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
# include <stdbool.h>
# include <errno.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

/* Colors for program */
# define BG "\033[92m"
# define BC "\033[96m"
# define RES "\033[0m"

/* constants*/
# define MAX_PATH_LENGTH 1024	

/* Structs and typedefs */
typedef struct s_data
{
	char	**commands; //alocated
	int		last_command;
	char	***args; //alocated
	int 	infile; //fd infilu
	char	* delimiter; //alocated
	char	**redirs; //alocated, ale nejspis uplne smazat: neni treba
	int		outfile;
	int		saved_stdin;
	int		saved_stdout;
	char	**minishell_env;
}	t_data;

/* Environmental variables storage */
extern char	**environ;
extern int	g_exit;

/* FUNCTIONS BY FILES */

/* parser.c */
void	ft_parser(const char *input, t_data *data);
bool	is_redir(char *word);
char	**destroy_redirections(char **words);
int		counter_without_redirs(char **words);

/* parsing_quotes_env_vars.c */
char	*prepare_quoted_string(const char *input);
char	**parse_quated_strings(char **words);

/* env_vars.c */
char	**replace_env_var_nonquated(char **words);
char	*env_replacement(char *word, int i, int j);
char	*dollar_check(char *word);
char	**status_var_check(char **words);
char	*status_replace(char *word);

/* in_outfiles.c */
int		redir_count(char **words, char *redir_frst, char *redir_scnd);
void	tokenize_infile_heredoc(char **words, t_data *data);
void	tokenize_outfile(char **words, t_data *data);

/* tokenize_commands_args.c */
int		is_command(char *word);
bool	is_pipe(char *word);
void	tokenize_command(char **words, t_data *data);

/* tokenize_arguments.c */
void	tokenize_arg(char **words, t_data *data, int count);
char	***argument_parser(char **commands, char ***args);
char	**copy_args(char **arr_src, char *command);

/* builtins_pwd_cd.c */
void	ft_pwd_fork(char **args, t_data *data);
int		ft_pwd_nonfork(char **args);
char	*join_env(char *var, char *value);
void	ft_cd_fork(char **args, t_data * data);
int		ft_cd_nonfork(char **args, t_data * data);

/* buldin_echo.c */
void	ft_echo_fork(char **args, t_data *data);
int		ft_echo_nonfork(char **args);
void	ft_echoprint(char **words, int i);

/* builtin_echo_utils.c */
void	ft_write_expander_char(char *word);
void	ft_write_expander_num(int start_int, int end_int);
void	ft_echo_expander(char *word);

/* builtin_env.c */
void	ft_env_fork(t_data *data);
int		ft_env_nonfork(void);

/* builtin_export.c */
void	ft_rewrite(int index, char *var, t_data *data);
void	ft_add(char *var, t_data *data);
void	ft_export_fork(char **words, t_data *data);
int		ft_export_nonfork(char **args, t_data *data);

/* builtin_export_utils.c */
int		ft_checkforexisting(char *var);
char	*ft_checkarg(char *arg);

/* builtin_unset.c */
void	ft_unset_fork(char **words, t_data *data);
int		ft_unset_nonfork(char **words, t_data *data);

/* builtin_exit.c */
void	ft_exit(t_data *data);

/* executor.c */
void	ft_executor(t_data *data);
void	executor_experim(t_data *data);
void	ft_executor_binary_exp(t_data *data);
void	save_restore_std(t_data *data, int i);
void	set_infile(t_data *data);
void	set_outfile(t_data *data);

/* builtins_redirection.c  */
void	builtin_redirection_fork(char *command, char **args, t_data	*data);
void	builtin_nonfork_redirection(char *command, char **args, t_data	*data);

/* heredoc.c */
void	ft_heredoc(char *delimiter);

/* command_check.c */
bool	ft_is_builtin(char *command);
bool	ft_is_pathx(char *command);
bool	ft_isnopathx(char *command);
char	*ft_return_path(char *command);
void	ft_command_check(t_data *data);

/* command_check_utils.c */
int		ft_isnopathx_util(void);

/* utils.c*/
int		commands_counting(char **words);
void	free_split(char **args);
void	free_args(char ***args);
void	free_command_table(t_data *data);
int		ft_isdigit_array(char **arg);
void	fork_exit(int status, t_data *data);

/* signals.c */
void	ft_sigint_handler(int signal);
void	ft_sigabrt_handler(int signal);
void	ft_sigquit_handler(int signal);

#endif
