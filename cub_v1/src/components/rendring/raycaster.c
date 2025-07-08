/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 08:49:34 by iezzam            #+#    #+#             */
/*   Updated: 2025/06/17 23:30:25 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	perform_dda(t_ray_params *params, t_cub *cub)
{
	char	hit_tile;

	hit_tile = ' ';
	while (1)
	{
		if (params->side_dist_x < params->side_dist_y)
		{
			params->map_x += params->step_x;
			params->side_dist_x += params->delta_dist_x;
			params->side = 0;
		}
		else
		{
			params->map_y += params->step_y;
			params->side_dist_y += params->delta_dist_y;
			params->side = 1;
		}
		hit_tile = cub->data.map.map[params->map_y][params->map_x];
		if (hit_tile == '1' || hit_tile == '2' || hit_tile == '3')
		{
			params->hit_tile = hit_tile;
			break ;
		}
	}
}

static void	calculate_hit_point(t_ray_params *params, t_cub *cub,
	float *hit_x, float *hit_y)
{
	if (params->side == 0)
	{
		*hit_x = cub->player.x + (params->map_x * BLOCK - cub->player.x
				+ (1 - params->step_x) * BLOCK / 2) / params->ray_dir_x
			* params->ray_dir_x;
		*hit_y = cub->player.y + (params->map_x * BLOCK - cub->player.x
				+ (1 - params->step_x) * BLOCK / 2) / params->ray_dir_x
			* params->ray_dir_y;
	}
	else
	{
		*hit_x = cub->player.x + (params->map_y * BLOCK - cub->player.y
				+ (1 - params->step_y) * BLOCK / 2) / params->ray_dir_y
			* params->ray_dir_x;
		*hit_y = cub->player.y + (params->map_y * BLOCK - cub->player.y
				+ (1 - params->step_y) * BLOCK / 2) / params->ray_dir_y
			* params->ray_dir_y;
	}
}

static void	calculate_step_distances(t_ray_params *params)
{
	if (params->ray_dir_x < 0)
	{
		params->step_x = -1;
		params->side_dist_x = (params->pos_x - params->map_x * BLOCK)
			* params->delta_dist_x / BLOCK;
	}
	else
	{
		params->step_x = 1;
		params->side_dist_x = ((params->map_x + 1) * BLOCK - params->pos_x)
			* params->delta_dist_x / BLOCK;
	}
	if (params->ray_dir_y < 0)
	{
		params->step_y = -1;
		params->side_dist_y = (params->pos_y - params->map_y * BLOCK)
			* params->delta_dist_y / BLOCK;
	}
	else
	{
		params->step_y = 1;
		params->side_dist_y = ((params->map_y + 1) * BLOCK - params->pos_y)
			* params->delta_dist_y / BLOCK;
	}
}

void	cast_ray(t_cub *cub, float ray_angle, int screen_x)
{
	t_ray_params	params;
	t_ray_data		ray;
	float			hit_x;
	float			hit_y;
	float			dist;

	init_ray_params(&params, cub, ray_angle);
	calculate_step_distances(&params);
	perform_dda(&params, cub);
	calculate_hit_point(&params, cub, &hit_x, &hit_y);
	ray.ray_dx = params.ray_dir_x;
	ray.ray_dy = params.ray_dir_y;
	ray.ray_x = hit_x;
	ray.ray_y = hit_y;
	ray.side = params.side;
	dist = use_fixed_dist(hit_x, hit_y, cub);
	if (params.hit_tile == '2')
		draw_door(cub, screen_x, &ray, dist);
	else if (params.hit_tile == '1')
		draw_wall(cub, screen_x, &ray, dist);
}

int	game_loop(t_cub *cub)
{
	static int		i;
	float			ray_step;
	float			ray_angle;
	int				x;

	if (!i)
		log_state("GAME LOADED", 1);
	i++;
	handle_movement(cub);
	clear_image(cub);
	draw_split_background(cub);
	ray_step = (PI / 3) / WIDTH;
	ray_angle = cub->player.angle - (PI / 6);
	x = 0;
	while (x < WIDTH)
	{
		cast_ray(cub, ray_angle, x);
		ray_angle += ray_step;
		x++;
	}
	draw_weapon(cub);
	render_draw_minimap(cub);
	mlx_put_image_to_window(cub->data.mlx, cub->data.win,
		cub->data.img.img, 0, 0);
	return (0);
}
