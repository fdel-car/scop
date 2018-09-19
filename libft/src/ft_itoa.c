/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 19:52:10 by fdel-car          #+#    #+#             */
/*   Updated: 2015/12/16 21:41:35 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_length(int n)
{
	int length;

	if (n == 0)
		return (1);
	length = 0;
	while (n)
	{
		n = n / 10;
		length++;
	}
	return (length);
}

static int	ft_sign(int n)
{
	if (n < 0)
		return (1);
	return (0);
}

char		*ft_itoa(int n)
{
	int		l;
	int		sign;
	char	*str;

	l = ft_length(n);
	sign = ft_sign(n);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (sign == 1)
		n = -n;
	str = (char *)malloc(sizeof(char) * (l + sign + 1));
	if (!str)
		return (NULL);
	str = str + l + sign;
	*str = '\0';
	if (!n)
		*--str = '0';
	while (n)
	{
		*--str = (n % 10) + 48;
		n = n / 10;
	}
	if (sign)
		*--str = '-';
	return (str);
}
