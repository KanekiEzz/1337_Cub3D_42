/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_utile_5.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:18:23 by yaajagro          #+#    #+#             */
/*   Updated: 2025/04/30 18:32:43 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	count_comas(char *s)
{
	int	i;

	i = 1;
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == ',')
			i++;
		s++;
	}
	return (i);
}

int	check_comas(char *clr1, char *clr2)
{
	int	count;

	if (!clr1 || !clr2)
		return (ft_putendl_fd("Error\nColor missed!", 2), 1);
	count = count_comas(clr1);
	if (count != 3)
		return (ft_putendl_fd("Error", 2),
			ft_putendl_fd(clr1, 2), 1);
	count = count_comas(clr2);
	if (count != 3)
		return (ft_putendl_fd("Error", 2),
			ft_putendl_fd(clr2, 2), 1);
	return (0);
}

int	get_map_len(t_lines *line)
{
	int	i;

	i = 0;
	while (line)
	{
		if (is_same(line->val, "MAP END"))
			break ;
		if (!is_same(line->val, "MAP BEGIN"))
			i++;
		line = line->next;
	}
	return (i);
}
