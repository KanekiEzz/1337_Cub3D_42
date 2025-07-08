/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_utile_4.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 21:15:15 by yaajagro          #+#    #+#             */
/*   Updated: 2025/05/01 17:08:59 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	palyer_chars(char c)
{
	return (c == 'W' || c == 'S' || c == 'E'
		|| c == 'N');
}

int	valid_chars(char c)
{
	return (c == ' ' || c == '0' || c == '1'
		|| c == 'W' || c == 'S' || c == 'E'
		|| c == 'N');
}

void	reset_texture(t_texture *textur)
{
	textur->cn = 0;
	textur->no = 0;
	textur->ea = 0;
	textur->fn = 0;
	textur->so = 0;
	textur->we = 0;
}

int	only_walls_map(char *s)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (*s != '1')
			return (0);
		s++;
	}
	return (1);
}

int	check_walls(char **map)
{
	int	y;

	y = 0;
	while (map[y])
	{
		if (map[y] && map[y + 1] && ft_strlen(map[y]) < ft_strlen(map[y + 1]))
		{
			if (!only_walls_map(*(map + y + 1) + ft_strlen(map[y])))
				return (ft_putstr_fd("Error\nInvalid map : ", 2), 
					ft_putendl_fd(ft_strjoin(ft_strjoin(map[y], " <<< line : "),
					ft_itoa(y)), 2), 1);
		}
		y++;
	}
	return (0);
}

int	check_map(t_cub *cub)
{
	char	**map;
	int		count;
	int		i;
	int		j;

	i = 0;
	count = 0;
	map = cub->data.map.map;
	if (!map)
		return (1);
	while (map[i])
	{
		if (map[i][0] != '1' || map[i][ft_strlen(map[i]) - 1] != '1')
			return (ft_putendl_fd("Error\nUnclosed wall Dedected", 2), 1);
		j = 0;
		while (map[i][j])
		{
			if (count > 1)
				return (ft_putendl_fd("Error\nMultiple players Dedected", 2), 1);
			if (palyer_chars(map[i][j]))
				count++;
			j++;
		}
		i++;
	}
	if (!count)
		return (ft_putendl_fd("Error\nMap has no player", 2), 1);
	return (check_walls(map));
}
