/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/25 13:48:15 by vde-la-s          #+#    #+#             */
/*   Updated: 2018/09/19 14:55:30 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

static char	*ft_strnew(size_t size)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * (size + 1));
	memset(str, '\0', size + 1);
	return (str);
}

static int	return_line(char *eol, char *s)
{
	if (!(*s = 0) && !eol)
		return (0);
	*eol++ = '\0';
	strcpy(s, eol);
	return (1);
}

static int	fill_line(char **line, char *buf)
{
	char	*tmp;

	tmp = *line;
	*line = ft_strjoin(*line, buf);
	free(tmp);
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
	if (!(*line = *s[fd] ? strdup(s[fd]) : ft_strnew(1)))
		return (-1);
	while (!strchr(*line, '\n') && (r = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[r] = '\0';
		if (!fill_line(line, buf))
			return (-1);
	}
	n = strchr(*line, '\n');
	if (return_line(n, s[fd]) || strlen(*line) || r > 0)
		return (1);
	return (!r ? 0 : -1);
}
