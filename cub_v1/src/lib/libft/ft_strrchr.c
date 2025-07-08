/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:44:25 by yaajagro          #+#    #+#             */
/*   Updated: 2024/11/03 16:10:04 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	size_t	len;

	len = ft_strlen(str);
	if (str[len] == (unsigned char)c)
		return ((char *)str + len);
	while (len-- > 0)
		if (str[len] == (unsigned char)c)
			return ((char *)str + len);
	return (NULL);
}
