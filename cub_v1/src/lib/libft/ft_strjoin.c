/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:44:05 by yaajagro          #+#    #+#             */
/*   Updated: 2024/11/05 20:59:22 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	size_t	len;
	char	*dest;
	int		index;

	if (!s1 && !s2)
		return (NULL);
	if (s1 && !s2)
		return (ft_strdup(s1));
	if (!s1 && s2)
		return (ft_strdup(s2));
	i = 0;
	index = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	dest = ft_malloc(len + 1);
	while (s1[i])
		dest[index++] = s1[i++];
	i = 0;
	while (s2[i])
		dest[index++] = s2[i++];
	dest[index] = '\0';
	return (dest);
}
