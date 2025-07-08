/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:38:14 by yaajagro          #+#    #+#             */
/*   Updated: 2025/05/02 23:18:59 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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

int	check_grb_rang(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (cub->texture->sky_grb[i] == -1
			|| cub->texture->floor_grb[i] == -1)
			return (ft_putendl_fd("Error\nInvalid RGB range", 2), 1);
		i++;
	}
	return (0);
}

int	check_rgb(t_cub *cub)
{
	char	**clr1;
	char	**clr2;
	int		i;

	i = 0;
	if (check_comas(cub->texture->sky_clr, cub->texture->floor_clr))
		return (1);
	clr1 = ft_split(cub->texture->floor_clr, ',');
	clr2 = ft_split(cub->texture->sky_clr, ',');
	if (!clr1 || !clr2
		|| get_len(clr1) != 3 || get_len(clr2) != 3)
		return (ft_putendl_fd("Error\nInvalid color format", 2), 1);
	while (i < 3)
	{
		cub->texture->floor_grb[i] = ft_atoi(clr1[i]);
		cub->texture->sky_grb[i] = ft_atoi(clr2[i]);
		i++;
	}
	return (check_grb_rang(cub));
}

int	check_colors(t_cub *cub)
{
	t_texture	*texture;

	texture = cub->texture;
	if (!texture->floor_clr || !texture->sky_clr)
	{
		if (!texture->floor_clr && texture->sky_clr)
			ft_putendl_fd("Error\nFloor color not found", 2);
		else if (!texture->sky_clr && texture->floor_clr)
			ft_putendl_fd("Error\nsky color not found", 2);
		else
			ft_putendl_fd("Error\ncolors not found", 2);
		return (1);
	}
	return (check_rgb(cub));
}

int	map_parsing(int ac, char **av, t_cub *cub)
{
	if (ac != 2)
		return (ft_putendl_fd("Error\nUsage: ./cub3D <map.cub>", 2), 1);
	if (init_map(cub, av[1]))
		return (ft_putendl_fd("Error\nFailed to initialize map", 2), 1);
	if (parse_lines(cub))
		return (ft_putendl_fd("Error\nFailed to parse lines", 2), 1);
	if (extractor(cub))
		return (1);
	// if (check_texture(cub) || check_colors(cub)
	if (check_colors(cub)
		|| check_map(cub))
		return (1);
	return (0);
}
