/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_utile.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 22:15:06 by yaajagro          #+#    #+#             */
/*   Updated: 2025/06/16 22:17:09 by yaajagro         ###   ########.fr       */
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

	log_state("CHECKING FILE EXTENTION", 3);
	if (check_file_extention(filename))
		return (log_state("INVALID FILE EXTENTION", 0), 1);
	log_state("VALID EXTENTION", 1);
	log_state("OPENING FILE", 3);
	fd = open(filename, 0);
	if (fd == -1)
		return (log_state("FAILED TO OPEN FILE", 0), 1);
	log_state("FILE OPENED WITH SUCCESS", 1);
	log_state("READING FILE", 3);
	cub->data.map.map = ft_split(read_map(fd), '\n');
	if (!cub->data.map.map)
		return (log_state("EMPTY FILE", 0), 1);
	log_state("DONE READING FILE", 1);
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
