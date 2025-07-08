/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:43:54 by yaajagro          #+#    #+#             */
/*   Updated: 2024/11/06 20:21:19 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspliter(char c, char spliter)
{
	if (c == spliter)
		return (1);
	return (0);
}

static int	ft_count(char *str, char spliter)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (str[i])
	{
		while (str[i] && ft_isspliter(str[i], spliter))
			i++;
		if (str[i])
			c++;
		while (str[i] && !ft_isspliter(str[i], spliter))
			i++;
	}
	return (c);
}

static char	*ft_allocate(char *str, char c, int *index)
{
	int		i;
	int		saved_index;
	char	*splited;

	i = 0;
	saved_index = *index;
	while (str[saved_index] && !ft_isspliter(str[saved_index], c))
	{
		saved_index++;
		i++;
	}
	splited = ft_malloc(i + 1);
	splited[i] = '\0';
	i = 0;
	while (str[*index] && !ft_isspliter(str[*index], c))
	{
		splited[i] = str[*index];
		(*index)++;
		i++;
	}
	return (splited);
}

char	**ft_split(char const *s, char c)
{
	char	**splites;
	int		count_spiltes;
	int		i;
	int		index;

	if (!s)
		return (NULL);
	i = 0;
	index = 0;
	count_spiltes = ft_count((char *)s, c);
	splites = ft_malloc(sizeof(char *) * (count_spiltes + 1));
	splites[count_spiltes] = NULL;
	while (i < count_spiltes)
	{
		while (s[index] && ft_isspliter(s[index], c))
			index++;
		splites[i] = ft_allocate((char *)s, c, &index);
		i++;
	}
	return (splites);
}
