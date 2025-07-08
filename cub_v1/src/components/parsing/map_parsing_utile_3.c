/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_utile_3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 22:15:33 by yaajagro          #+#    #+#             */
/*   Updated: 2025/06/18 22:58:06 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

t_lines	*map_extracter(t_lines *line, char ***map)
{
	int		len;
	char	**new;
	int		i;

	len = get_map_len(line);
	if (!len)
		return (NULL);
	i = 0;
	len++;
	*map = ft_malloc((sizeof(char *) * len) + 1);
	new = *map;
	while (line && !is_same(line->val, "MAP END"))
	{
		if (!is_same(line->val, "MAP BEGIN"))
		{
			new[i] = line->val;
			i++;
		}
		line = line->next;
	}
	new[i] = NULL;
	return (line);
}

int	extractor(t_cub *cub)
{
	t_lines		*line;
	t_texture	*textur;

	textur = ft_malloc(sizeof(t_texture));
	reset_texture(textur);
	cub->texture = textur;
	line = cub->data.lines;
	if (!line)
		return (1);
	remove_spaces(line);
	line = textures_extracter(line, textur);
	if (!line)
		return (log_state("No map Found", 0), 1);
	line = map_extracter(line, &cub->data.map.map);
	if (!line)
		return (log_state("No map Found", 0), 1);
	return (0);
}

int	check_file_ext(char *name)
{
	static int	i;

	if (!name)
		return (log_state("file is NULL", 0), 1);
	log_state("CHECKING EXTENTION", 3);
	while (*name && *name != '.')
		name++;
	if (*name)
	{
		if (!ft_strncmp(name, ".xpm", ft_strlen(".xpm"))
			&& !name[ft_strlen(".xpm")])
			return (log_state("VALID EXTENTION", 1), 0);
	}
	log_state("INVALID EXTENTION", 0);
	i++;
	return (1);
}

int	check_file(char *filename)
{
	int	fd;

	if (!filename)
		return (log_state("Texture not found", 0), 1);
	log_state(ft_strjoin("CHECKING FILE ", filename), 3);
	if (check_file_ext(filename))
		return (1);
	fd = open(filename, 0);
	if (fd == -1)
	{
		log_state(ft_strjoin(ft_strjoin("FILE : ", filename), \
			" NOT FOUND!"), 0);
		return (1);
	}
	log_state("FILE EXIST", 1);
	close(fd);
	return (0);
}

int	check_texture(t_cub *cub)
{
	t_texture	*texture;

	log_state("CHECKING TEXTURES", 3);
	texture = cub->texture;
	if (check_file(texture->ea_path) || check_file(texture->so_path)
		|| check_file(texture->we_path) || check_file(texture->no_path))
		return (1);
	log_state("VALID TEXTURES", 1);
	return (0);
}
