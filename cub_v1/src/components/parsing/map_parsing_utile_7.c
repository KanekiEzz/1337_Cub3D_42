/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_utile_7.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 22:18:13 by yaajagro          #+#    #+#             */
/*   Updated: 2025/06/18 22:58:31 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	check_rendring_depend(t_cub *cub)
{
	char	*door_path;
	int		fd;

	door_path = "./textures/door/__door1.xpm";
	if (!cub)
		return ;
	log_state("CHECKING DEPENDENCIES", 3);
	fd = open(door_path, 0);
	if (fd == -1)
		log_state("DOOR IMG NOT FOUND", 0);
	close(fd);
	log_state("CHECKING DEPENDENCIES", 1);
}

int	get_len(char **s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	remove_spaces(t_lines *lines)
{
	bool	flag;
	char	*tmp;

	if (!lines)
		return ;
	flag = false;
	while (lines)
	{
		if (is_same("TEXTUR BEGIN", lines->val))
			flag = true;
		if (flag && !is_same("MAP BEGIN", lines->val))
		{
			tmp = lines->val;
			while (*tmp && *tmp == ' ')
				tmp++;
			lines->val = ft_strdup(tmp);
		}
		if (is_same("MAP BEGIN", lines->val))
			break ;
		lines = lines->next;
	}
}

int	xe_cond(int c)
{
	return (!c || c == ' ');
}
