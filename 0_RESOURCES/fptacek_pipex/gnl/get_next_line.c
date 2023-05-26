/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fptacek <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:30:01 by fptacek           #+#    #+#             */
/*   Updated: 2023/03/22 15:30:06 by fptacek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_one_line(char *static_ptr)
{
	int		i;
	char	*buff;

	i = 0;
	if (!static_ptr)
		return (NULL);
	while (static_ptr[i] != '\0' && static_ptr[i] != '\n')
		i++;
	buff = (char *)malloc(sizeof(char) * i + 2);
	if (buff == NULL)
		return (NULL);
	i = 0;
	while (static_ptr[i] != '\0' && static_ptr[i] != '\n')
	{
		buff[i] = static_ptr[i];
		i++;
	}
	if (static_ptr[i] == '\n')
	{
		buff[i] = '\n';
		i++;
	}
	buff[i] = '\0';
	return (buff);
}

int	ft_check_n(char *static_ptr)
{
	int		i;

	i = 0;
	while (static_ptr[i] != '\0')
	{
		if (static_ptr[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_read(char *static_ptr, int fd)
{
	int		int_read;
	char	*buff;

	buff = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	while (1)
	{
		int_read = read(fd, buff, BUFFER_SIZE);
		if (int_read == 0)
			break ;
		if (int_read == -1)
		{
			free(static_ptr);
			free(buff);
			return (NULL);
		}
		buff[int_read] = '\0';
		static_ptr = ft_strjoin(static_ptr, buff);
		if (ft_check_n(static_ptr) == 1)
			break ;
	}
	free(buff);
	return (static_ptr);
}

char	*get_next_line(int fd)
{
	static char		*static_ptr;
	char			*line;
	char			*p;

	if (fd == -1 || BUFFER_SIZE <= 0)
		return (NULL);
	static_ptr = ft_read(static_ptr, fd);
	p = static_ptr;
	line = ft_one_line(static_ptr);
	if (!line)
		return (NULL);
	static_ptr = ft_new_str(static_ptr, '\n');
	free(p);
	return (line);
}
