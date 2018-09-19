/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/25 13:48:15 by vde-la-s          #+#    #+#             */
/*   Updated: 2018/08/02 18:05:11 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

static int	return_line(char *eol, char *s)
{
	if (!(*s = 0) && !eol)
		return (0);
	*eol++ = '\0';
	ft_strcpy(s, eol);
	return (1);
}

static int	fill_line(char **line, char *buf)
{
	*line = ft_strjoin_free(*line, buf);
	return (*line ? 1 : -1);
}

int			get_next_line(int const fd, char **line)
{
	static char s[256][BUFF_SIZE];
	char		buf[BUFF_SIZE + 1];
	char		*n;
	int			r;

	if (!line || fd < 0 || fd > 255 || BUFF_SIZE < 1)
		return (-1);
	if (!(*line = *s[fd] ? ft_strdup(s[fd]) : ft_strnew(1)))
		return (-1);
	while (!ft_strchr(*line, '\n') && (r = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[r] = '\0';
		if (!fill_line(line, buf))
			return (-1);
	}
	n = ft_strchr(*line, '\n');
	if (return_line(n, s[fd]) || ft_strlen(*line) || r > 0)
		return (1);
	return (!r ? 0 : -1);
}
