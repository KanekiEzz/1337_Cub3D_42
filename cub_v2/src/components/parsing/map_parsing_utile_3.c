/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_utile_3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 21:03:11 by yaajagro          #+#    #+#             */
/*   Updated: 2025/05/04 14:10:16 by iezzam           ###   ########.fr       */
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
	line = textures_extracter(line, textur);
	if (!line)
		return (ft_putendl_fd("Error\nNo map Found", 2), 1);
	line = map_extracter(line, &cub->data.map.map);
	if (!line)
		return (ft_putendl_fd("Error\nNo map Found", 2), 1);
	return (0);
}

int	check_file_ext(char *name)
{
	char	*tmp;

	tmp = name;
	while (*name && *name != '.')
		name++;
	if (*name)
	{
		if (!ft_strncmp(name, ".xpm", ft_strlen(".xpm"))
			&& !name[ft_strlen(".xpm")])
			return (0);
	}
	ft_putstr_fd("Error\nfile : ", 2);
	ft_putstr_fd(tmp, 2);
	ft_putstr_fd(" has invalid extention\n", 2);
	return (1);
}

int	check_file(char *filename)
{
	int	fd;

	if (!filename)
		return (ft_putendl_fd("Error\nTextur not found", 2), 1);
	if (check_file_ext(filename))
		return (1);
	fd = open(filename, 0);
	if (fd == -1)
	{
		perror(filename);
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	check_texture(t_cub *cub)
{
	t_texture	*texture;

	texture = cub->texture;
	if (check_file(texture->ea_path) || check_file(texture->so_path)
		|| check_file(texture->we_path) || check_file(texture->no_path))
		return (1);
	return (0);
}
