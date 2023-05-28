/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 16:30:39 by sbenes            #+#    #+#             */
/*   Updated: 2023/05/28 11:33:27 by sbenes           ###   ########.fr       */
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

/* Structs and typedefs */
typedef struct s_envdata
{
	char	*user;
}	t_env;

/* Functions by files */

#endif