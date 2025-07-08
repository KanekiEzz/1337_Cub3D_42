/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_utile.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 20:59:09 by yaajagro          #+#    #+#             */
/*   Updated: 2025/04/30 18:29:25 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

char	*read_map(int fd)
{
	char	*map;
	char	*buffer;

	map = NULL;
	while (1)
	{
		buffer = get_next_line(fd);
		if (!buffer)
			break ;
		map = ft_strjoin(map, buffer);
	}
	return (map);
}

int	check_file_extention(char *str)
{
	if (!str)
		return (1);
	while (*str)
	{
		if (*str == '.')
		{
			str++;
			if (ft_strncmp(str, "cub", 3) == 0 && str[3] == '\0')
				return (0);
			else
				return (1);
		}
		str++;
	}
	return (1);
}

int	init_map(t_cub *cub, char *filename)
{
	int	fd;

	if (check_file_extention(filename))
		return (ft_putendl_fd("Error\nInvalid Extention", 2), 1);
	fd = open(filename, 0);
	if (fd == -1)
		return (ft_putendl_fd("Error\nFailed to open map file", 2), 1);
	cub->data.map.map = ft_split(read_map(fd), '\n');
	if (!cub->data.map.map)
		return (ft_putendl_fd("Error\nFailed to read map", 2), 1);
	close(fd);
	return (0);
}

t_lines	*new_line(char *val)
{
	t_lines	*new;

	new = ft_malloc(sizeof(t_lines));
	new->next = NULL;
	new->val = val;
	return (new);
}

void	ft_add_line(t_lines **head, t_lines *new)
{
	t_lines	*last;

	if (!head || !new)
		return ;
	if (!*head)
		*head = new;
	else
	{
		last = *head;
		while (last->next)
			last = last->next;
		last->next = new;
	}
}
