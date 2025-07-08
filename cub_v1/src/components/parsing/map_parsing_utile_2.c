/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_utile_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 22:15:39 by yaajagro          #+#    #+#             */
/*   Updated: 2025/06/16 22:15:40 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	only_walls(char *line)
{
	if (!line)
		return (0);
	while (*line)
	{
		if (!valid_chars(*line))
			return (0);
		line++;
	}
	return (1);
}

int	parse_lines(t_cub *cub)
{
	char		**map;
	static int	n;
	t_lines		*line;
	int			i;

	(1) && (map = cub->data.map.map, line = NULL, i = 0);
	while (map[i])
	{
		if (!i)
			ft_add_line(&line, new_line(ft_strdup("TEXTUR BEGIN")));
		if (only_walls(map[i]) && !n)
		{
			ft_add_line(&line, new_line(ft_strdup("MAP BEGIN")));
			ft_add_line(&line, new_line(map[i]));
			n++;
		}
		else
			ft_add_line(&line, new_line(map[i]));
		if (!map[i + 1])
			ft_add_line(&line, new_line(ft_strdup("MAP END")));
		i++;
	}
	cub->data.lines = line;
	return (0);
}

int	add_more_tex(char *path, t_texture *tex, int flg)
{
	if (!path)
		return (1);
	if (flg == 4 && !tex->ea)
	{
		tex->ea++;
		tex->ea_path = path;
		return (0);
	}
	if (flg == 5 && !tex->fn)
	{
		tex->fn++;
		tex->floor_clr = path;
		return (0);
	}
	if (flg == 6 && !tex->cn)
	{
		tex->cn++;
		tex->sky_clr = path;
		return (0);
	}
	return (log_state("Duplicate texture found!", 0), 1);
}

int	add_texture(char *path, t_texture *tex, int flg)
{
	if (!path)
		return (1);
	if (flg == 1 && !tex->no)
	{
		tex->no++;
		tex->no_path = path;
		return (0);
	}
	if (flg == 2 && !tex->so)
	{
		tex->so++;
		tex->so_path = path;
		return (0);
	}
	if (flg == 3 && !tex->we)
	{
		tex->we++;
		tex->we_path = path;
		return (0);
	}
	return (add_more_tex(path, tex, flg));
}
