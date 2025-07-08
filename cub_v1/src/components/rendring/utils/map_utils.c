/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 08:35:35 by iezzam            #+#    #+#             */
/*   Updated: 2025/06/02 13:18:00 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

bool	touch_one(float px, float py, t_cub *cub)
{
	int		i;
	int		j;
	float	check_x;
	float	check_y;

	i = -1;
	while (i <= 1)
	{
		j = -1;
		while (j <= 1)
		{
			check_x = (px + i * BLOCK / 9) / BLOCK;
			check_y = (py + j * BLOCK / 9) / BLOCK;
			if (cub->data.map.map[(int)check_y][(int)check_x] == '1' \
			|| cub->data.map.map[(int)check_y][(int)check_x] == '2')
				return (true);
			j++;
		}
		i++;
	}
	return (false);
}

float	use_distance(float x, float y)
{
	return (sqrt(x * x + y * y));
}

float	use_fixed_dist(float x2, float y2, t_cub *game)
{
	float	delta_x;
	float	delta_y;
	float	angle;
	float	fix_dist;

	delta_x = x2 - game->player.x;
	delta_y = y2 - game->player.y;
	angle = atan2(delta_y, delta_x) - game->player.angle;
	fix_dist = use_distance(delta_x, delta_y) * cos(angle);
	return (fix_dist);
}

void	init_ray_params(t_ray_params *params, t_cub *cub, float ray_angle)
{
	params->ray_dir_x = cos(ray_angle);
	params->ray_dir_y = sin(ray_angle);
	params->map_x = (int)cub->player.x / BLOCK;
	params->map_y = (int)cub->player.y / BLOCK;
	params->delta_dist_x = fabs(1 / params->ray_dir_x);
	params->delta_dist_y = fabs(1 / params->ray_dir_y);
	params->pos_x = cub->player.x;
	params->pos_y = cub->player.y;
}

int	get_map_height(char **map)
{
	int	h;

	h = 0;
	while (map && map[h])
		h++;
	return (h);
}
