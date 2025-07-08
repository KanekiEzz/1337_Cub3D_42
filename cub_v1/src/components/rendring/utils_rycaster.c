/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_rycaster.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 12:00:30 by iezzam            #+#    #+#             */
/*   Updated: 2025/06/01 12:04:28 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	draw_wall_texture(t_draw_info *info, t_img *tex, int screen_x,
	t_cub *cub)
{
	int		y;
	int		tex_y;
	char	*pixel;
	int		color;

	y = info->start_y;
	while (y < info->end_y)
	{
		tex_y = (int)info->tex_pos & (tex->height - 1);
		info->tex_pos += info->step;
		pixel = tex->addr + (tex_y * tex->line_length
				+ info->tex_x * (tex->bits_per_pixel / 8));
		color = *(unsigned int *)pixel;
		my_pixel_put(screen_x, y, &cub->data.img, color);
		y++;
	}
}

static void	setup_wall_texture(t_draw_info *info, t_cub *cub, t_ray_data *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dx < 0)
			info->tex = &cub->texture->we_img;
		else
			info->tex = &cub->texture->ea_img;
		info->wall_hit = fmod(ray->ray_y, BLOCK) / BLOCK;
	}
	else
	{
		if (ray->ray_dy < 0)
			info->tex = &cub->texture->no_img;
		else
			info->tex = &cub->texture->so_img;
		info->wall_hit = fmod(ray->ray_x, BLOCK) / BLOCK;
	}
	info->tex_x = (int)(info->wall_hit * info->tex->width);
	if ((ray->side == 0 && ray->ray_dx > 0)
		|| (ray->side == 1 && ray->ray_dy < 0))
		info->tex_x = info->tex->width - info->tex_x - 1;
}

void	draw_wall(t_cub *cub, int screen_x, t_ray_data *ray, float dist)
{
	t_draw_info	info;

	info.wall_height = (BLOCK / dist) * (WIDTH / 2);
	info.start_y = (HEIGHT - info.wall_height) / 2;
	if (info.start_y < 0)
		info.start_y = 0;
	info.end_y = info.start_y + info.wall_height;
	if (info.end_y > HEIGHT)
		info.end_y = HEIGHT;
	setup_wall_texture(&info, cub, ray);
	info.step = (float)info.tex->height / info.wall_height;
	info.tex_pos = (info.start_y - HEIGHT / 2 + info.wall_height / 2)
		* info.step;
	draw_wall_texture(&info, info.tex, screen_x, cub);
}

static void	setup_door_texture(t_draw_info *info, t_cub *cub, t_ray_data *ray)
{
	info->tex = &cub->texture->door_img;
	if (ray->side == 0)
		info->wall_hit = fmod(ray->ray_y, BLOCK) / BLOCK;
	else
		info->wall_hit = fmod(ray->ray_x, BLOCK) / BLOCK;
	info->tex_x = (int)(info->wall_hit * info->tex->width);
	if ((ray->side == 0 && ray->ray_dx > 0)
		|| (ray->side == 1 && ray->ray_dy < 0))
		info->tex_x = info->tex->width - info->tex_x - 1;
}

void	draw_door(t_cub *cub, int screen_x, t_ray_data *ray, float dist)
{
	t_draw_info	info;

	info.wall_height = (BLOCK / dist) * (WIDTH / 2);
	info.start_y = (HEIGHT - info.wall_height) / 2;
	if (info.start_y < 0)
		info.start_y = 0;
	info.end_y = info.start_y + info.wall_height;
	if (info.end_y > HEIGHT)
		info.end_y = HEIGHT;
	info.tex = &cub->texture->door_img;
	if (!info.tex || !info.tex->img)
		return ;
	setup_door_texture(&info, cub, ray);
	info.step = (float)info.tex->height / info.wall_height;
	info.tex_pos = (info.start_y - HEIGHT / 2 + info.wall_height / 2)
		* info.step;
	draw_wall_texture(&info, info.tex, screen_x, cub);
}
