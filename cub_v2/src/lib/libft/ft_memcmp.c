/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 18:22:47 by yaajagro          #+#    #+#             */
/*   Updated: 2024/11/06 20:07:02 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;
	char	*s_1;
	char	*s_2;

	i = 0;
	s_1 = (char *)s1;
	s_2 = (char *)s2;
	while (i < n)
	{
		if (s_1[i] != s_2[i])
			return ((unsigned char)s_1[i] - (unsigned char)s_2[i]);
		i++;
	}
	return (0);
}
