/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbenes <sbenes@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 14:57:44 by sbenes            #+#    #+#             */
/*   Updated: 2023/06/29 17:02:39 by sbenes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* 
FT_SIGINT_HANDLER - handles the ctrl + c pressed.
Resets the line and display a new prompt.
 */
void	ft_sigint_handler(int signal)
{
	if (signal == SIGINT)
	{
		rl_replace_line("", 0); // Clear the current line
		rl_on_new_line(); // Inform readline to read a new line
		write(1, "\n", 1);
		rl_redisplay(); // Redisplay the prompt
	}
}