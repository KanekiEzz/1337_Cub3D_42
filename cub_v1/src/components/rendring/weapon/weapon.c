/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:14:15 by iezzam            #+#    #+#             */
/*   Updated: 2025/06/17 23:19:55 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

static void	update_animation_frame(t_cub *cub)
{
	cub->weapon_anim_tick++;
	if (cub->weapon_anim_tick > cub->weapon_anim_speed)
	{
		cub->weapon_anim_tick = 0;
		cub->weapon_anim_frame++;
		if (cub->weapon_anim_frame >= 3)
			cub->weapon_anim_frame = 0;
	}
}

static void	draw_scaled_weapon(t_cub *cub, t_img *weapon, \
				int x_start, int y_start)
{
	const int		scaled_width = weapon->width / 2;
	const int		scaled_height = weapon->height / 2;
	int				y;
	int				x;
	unsigned int	color;

	y = -1;
	while (++y < scaled_height)
	{
		x = -1;
		while (++x < scaled_width)
		{
			color = *(unsigned int *)(weapon->addr
					+ (y * 2 * weapon->line_length)
					+ (x * 2 * (weapon->bits_per_pixel / 8)));
			if ((color & 0x00FFFFFF) != 0)
				my_pixel_put_img(&cub->data.img,
					x_start + x, y_start + y, color);
		}
	}
}

void	init_weapon_animation_params(t_cub *cub)
{
	cub->weapon_anim_speed = 1;
	cub->current_weapon_index = 1;
	cub->weapon_anim_frame = 1;
	cub->weapon_anim_tick = 1;
}

void	draw_weapon(t_cub *cub)
{
	t_img	*weapon;
	int		x_start;
	int		y_start;
	int		frame;

	update_animation_frame(cub);
	frame = cub->weapon_anim_frame;
	weapon = &cub->texture->weapon[cub->current_weapon_index
		* 3 + frame];
	x_start = (WIDTH - weapon->width / 2) / 2;
	y_start = HEIGHT - (weapon->height / 2) / 1.2;
	draw_scaled_weapon(cub, weapon, x_start, y_start);
}
