/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_utile_5.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 22:15:21 by yaajagro          #+#    #+#             */
/*   Updated: 2025/06/16 22:17:15 by yaajagro         ###   ########.fr       */
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
		return (log_state("Color missed!", 0), 1);
	count = count_comas(clr1);
	if (count != 3)
		return (log_state(clr1, 0), 1);
	count = count_comas(clr2);
	if (count != 3)
		return (log_state(clr2, 0), 1);
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
