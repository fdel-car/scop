/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 12:27:54 by fdel-car          #+#    #+#             */
/*   Updated: 2015/12/08 20:10:41 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	ft_line(const char *s, char c)
{
	int i;
	int l;

	i = 0;
	l = 0;
	while (s[i] == c)
		i++;
	while (s[i] != c && s[i] != '\0')
	{
		i++;
		if (s[i] == c)
			l++;
		while (s[i] == c)
			i++;
	}
	if (s[i - 1] != c)
		l++;
	if (s[0] == '\0')
		l--;
	return (l);
}

static int	ft_column(const char *s, char c)
{
	int	max;
	int k;
	int i;

	max = 0;
	k = 0;
	i = 0;
	while (s[i] == c)
		i++;
	while (s[i] != c && s[i] != '\0')
	{
		i++;
		k++;
		if (k > max)
			max = k;
		while (s[i] == c)
		{
			k = 0;
			i++;
		}
	}
	return (max + 1);
}

static char	*ft_insert(const char *s, char c, char *str, int rep)
{
	int i;
	int j;
	int r;

	r = 0;
	i = 0;
	j = -1;
	while (s[i] == c)
		i++;
	while (s[i] && s[i] != c)
	{
		i--;
		while (s[++i] != c && s[i] && r == rep)
			str[++j] = s[i];
		if (r != rep)
			i++;
		while (s[i] == c)
		{
			i++;
			if (s[i] != c)
				r++;
		}
	}
	str[++j] = '\0';
	return (str);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**str;
	int		i;
	int		l;
	int		k;

	i = -1;
	if (!s)
		return (NULL);
	l = ft_line(s, c);
	k = ft_column(s, c);
	str = (char **)malloc(sizeof(char *) * (l + 1));
	if (!str)
		return (NULL);
	while (++i < l)
	{
		str[i] = (char *)malloc(sizeof(char) * k);
		if (!str[i])
			return (NULL);
		if (s[0] == '\0')
			str[i] = NULL;
		else
			str[i] = ft_insert(s, c, str[i], i);
	}
	str[i] = NULL;
	return (str);
}
