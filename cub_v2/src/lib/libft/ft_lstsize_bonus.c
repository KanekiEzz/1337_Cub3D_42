/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 22:56:19 by yaajagro          #+#    #+#             */
/*   Updated: 2024/11/03 16:16:37 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*tmp;
	int		size;

	if (!lst)
		return (0);
	size = 0;
	tmp = lst;
	while (tmp)
	{
		size++;
		tmp = tmp -> next;
	}
	return (size);
}
