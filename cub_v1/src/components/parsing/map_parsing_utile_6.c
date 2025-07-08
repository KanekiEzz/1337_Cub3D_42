/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_utile_6.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 22:15:13 by yaajagro          #+#    #+#             */
/*   Updated: 2025/06/18 22:58:24 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	check_walls(char **map)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		log_state(ft_strjoin("CHECKING LINE > ", map[y]), 3);
		x = 0;
		if (check_chars(map[y]))
			return (1);
		while (map[y][x])
		{
			if (map[y][x] == '0' || map[y][x] == '2')
			{
				if (xe_cond(map[y][x + 1]) || xe_cond(map[y][x - 1]) || \
						xe_cond(map[y + 1][x]) || xe_cond(map[y - 1][x]))
					log_state("Player will be out of the map", 0);
			}
			x++;
		}
		log_state("VALID LINE", 1);
		y++;
	}
	return (0);
}

int	only_ones(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (1);
	while (line[i])
	{
		if (line[i] != '1' && line[i] != ' '
			&& line[i] != '\t')
			return (1);
		i++;
	}
	return (0);
}

t_lines	*textures_extracter(t_lines *line, t_texture *textur)
{
	while (line && line->next && !is_same(line->val, "MAP BEGIN"))
	{
		if (!is_same(line->val, "TEXTUR BEGIN"))
		{
			if (!ft_strncmp(line->val, "NO ", ft_strlen("NO ")))
				add_texture(ft_split(line->val, ' ')[1], textur, 1);
			else if (!ft_strncmp(line->val, "SO ", ft_strlen("SO ")))
				add_texture(ft_split(line->val, ' ')[1], textur, 2);
			else if (!ft_strncmp(line->val, "WE ", ft_strlen("WE ")))
				add_texture(ft_split(line->val, ' ')[1], textur, 3);
			else if (!ft_strncmp(line->val, "EA ", ft_strlen("EA ")))
				add_texture(ft_split(line->val, ' ')[1], textur, 4);
			else if (!ft_strncmp(line->val, "F ", ft_strlen("F ")))
				add_texture(ft_split(line->val, ' ')[1], textur, 5);
			else if (!ft_strncmp(line->val, "C ", ft_strlen("C ")))
				add_texture(ft_split(line->val, ' ')[1], textur, 6);
			else
				return (log_state("Invalid texture", 0), NULL);
		}
		line = line->next;
	}
	return (line);
}

int	chech_map_help(char **map)
{
	int		count;
	int		i;
	int		j;

	i = 0;
	count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (count > 1)
				return (log_state("Multiple players Dedected", 0), 1);
			if (palyer_chars(map[i][j]))
				count++;
			j++;
		}
		if (!map[i + 1] && only_ones(map[i]))
			log_state(ft_strjoin(ft_strjoin("Unclosed wall Line ",
						ft_strjoin(ft_itoa(i), " ->")), map[i]), 0);
		i++;
	}
	if (!count)
		return (log_state("The map has no player", 0), 1);
	return (0);
}

int	check_map(t_cub *cub)
{
	char	**map;

	map = cub->data.map.map;
	log_state("MAP CHECKING", 3);
	if (!map)
		return (log_state("Thers is no map", 0), 1);
	if (only_ones(map[0]))
		log_state(ft_strjoin(ft_strjoin("Unclosed wall Line ",
					ft_strjoin(ft_itoa(0), " ->")), map[0]), 0);
	if (chech_map_help(map))
		return (1);
	return (check_walls(map));
}
