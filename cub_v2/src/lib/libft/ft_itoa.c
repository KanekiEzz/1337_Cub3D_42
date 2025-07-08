/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:43:25 by yaajagro          #+#    #+#             */
/*   Updated: 2024/11/02 18:34:38 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	ft_int_len(long nbr, int *len, int *sing)
{
	long	saved_nbr;

	*len = 0;
	if (nbr < 0)
	{
		*sing = 1;
		nbr *= -1;
		*len = 1;
	}
	saved_nbr = nbr;
	while (nbr)
	{
		nbr /= 10;
		*len = *len + 1;
	}
	return (saved_nbr);
}

char	*ft_itoa(int n)
{
	long	nbr;
	int		is_nigative;
	int		len;
	char	*str;

	nbr = n;
	is_nigative = 0;
	if (n == 0)
		return (ft_strdup("0"));
	nbr = ft_int_len(nbr, &len, &is_nigative);
	str = ft_malloc(len + 1);
	if (!str)
		return (NULL);
	str[len--] = '\0';
	while (nbr)
	{
		str[len--] = (nbr % 10) + '0';
		nbr /= 10;
	}
	if (is_nigative)
		str[0] = '-';
	return (str);
}
