/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fptacek <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:30:29 by fptacek           #+#    #+#             */
/*   Updated: 2023/03/22 15:30:34 by fptacek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1

# endif

char	*get_next_line(int fd);
char	*ft_read(char *static_ptr, int fd);
int		ft_check_n(char *static_ptr);
char	*ft_one_line(char *static_ptr);
char	*ft_new_str(char *static_ptr, char n);
int		ft_strlen(char *str);
char	*ft_strjoin(char	*s1, char *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);

#endif
