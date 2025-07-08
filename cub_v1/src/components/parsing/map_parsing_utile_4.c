/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_utile_4.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 22:15:27 by yaajagro          #+#    #+#             */
/*   Updated: 2025/06/16 22:17:29 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	palyer_chars(char c)
{
	return (c == 'W' || c == 'S' || c == 'E' || c == 'N');
}

int	valid_chars(char c)
{
	return (c == ' ' || c == '0' || c == '1' || c == 'W' \
		|| c == 'S' || c == 'E' || c == 'N' || c == '2');
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

int	check_chars(char *s)
{
	int	i;

	if (!s)
		return (1);
	i = 0;
	while (s[i])
	{
		if (!valid_chars(s[i]))
		{
			s[i + 1] = '\0';
			log_state(ft_strjoin("INVALID CHAR : ", s + i), 0);
		}
		i++;
	}
	return (0);
}
