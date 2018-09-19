/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdel-car <fdel-car@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/28 17:19:57 by fdel-car          #+#    #+#             */
/*   Updated: 2018/09/19 13:03:56 by fdel-car         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_null(void)
{
	char *str;

	str = (char *)malloc(sizeof(char) * 2);
	str[0] = '0';
	str[1] = '\0';
	return (str);
}

char	*ft_itoa_base(unsigned long long int nbr, int base)
{
	static char	base_char[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8',
								'9', 'a', 'b', 'c', 'd', 'e', 'f'};
	int			number[64];
	char		*str;
	int			i;
	int			n;

	n = nbr;
	i = 0;
	if (nbr == 0)
		return (ft_null());
	while (nbr != 0)
	{
		number[i] = nbr % base;
		nbr = nbr / base;
		++i;
	}
	--i;
	str = (char *)malloc(sizeof(char) * i);
	n = 0;
	while (i >= 0)
		str[n++] = base_char[number[i--]];
	str[n] = '\0';
	return (str);
}