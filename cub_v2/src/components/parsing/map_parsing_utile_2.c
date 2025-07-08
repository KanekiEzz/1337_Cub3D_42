/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_utile_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 21:01:07 by yaajagro          #+#    #+#             */
/*   Updated: 2025/04/30 18:28:54 by yaajagro         ###   ########.fr       */
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

	map = cub->data.map.map;
	line = NULL;
	i = 0;
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
	return (ft_putendl_fd("Error\nDuplicate texture found!", 2),
		ft_malloc(-1), exit(1), 1);
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
				return (ft_putendl_fd("Error\nInvalid texture", 2),
					ft_malloc(-1), exit(1), NULL);
		}
		line = line->next;
	}
	return (line);
}
