/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:43:03 by yaajagro          #+#    #+#             */
/*   Updated: 2024/11/03 15:47:00 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	mult;

	mult = count * size;
	if (count && size != mult / count)
		return (NULL);
	ptr = ft_malloc(count * size);
	ft_bzero(ptr, count * size);
	return (ptr);
}
