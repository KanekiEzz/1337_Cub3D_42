/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:44:15 by yaajagro          #+#    #+#             */
/*   Updated: 2024/10/23 16:40:44 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*dest;

	if (!s || !f)
		return (NULL);
	i = 0;
	dest = ft_malloc(ft_strlen(s)+1);
	while (s[i])
	{
		dest[i] = f(i, (char)s[i]);
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
