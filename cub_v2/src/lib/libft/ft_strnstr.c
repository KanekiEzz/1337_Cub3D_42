/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:44:21 by yaajagro          #+#    #+#             */
/*   Updated: 2024/11/01 22:26:05 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strcheck(const char *str, const char *word,
		size_t index, size_t len)
{
	size_t	i;
	size_t	word_len;

	word_len = ft_strlen(word);
	if (index + word_len > len)
		return (0);
	i = 0;
	while (word[i] && str[index + i] == word[i])
		i++;
	return (word[i] == '\0');
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;

	if (needle[0] == '\0')
		return ((char *)haystack);
	if (len == 0)
		return (NULL);
	i = 0;
	while (i < len && haystack[i])
	{
		if (haystack[i] == needle[0])
		{
			if (ft_strcheck(haystack, needle, i, len))
				return ((char *)haystack + i);
		}
		i++;
	}
	return (NULL);
}
