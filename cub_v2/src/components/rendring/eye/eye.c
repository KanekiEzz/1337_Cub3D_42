/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eye.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:05:38 by iezzam            #+#    #+#             */
/*   Updated: 2025/05/30 14:19:59 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	update_eye_animation(t_cub *cub)
{
	cub->eye_anim_tick++;
	if (cub->is_cycling && cub->eye_anim_tick > cub->eye_anim_speed)
	{
		cub->eye_anim_tick = 0;
		cub->eye_anim_frame += cub->eye_direction;
		if (cub->eye_anim_frame >= MAX_EYE - 1
			|| cub->eye_anim_frame <= 0)
		{
			cub->is_cycling = 0;
			cub->eye_pause_timer = 0;
			cub->eye_direction *= -1;
		}
	}
	else if (!cub->is_cycling)
	{
		cub->eye_pause_timer++;
		if (cub->eye_pause_timer > cub->eye_pause_duration)
			cub->is_cycling = 1;
	}
}

void	draw_eye(t_cub *cub)
{
	t_img			*eye;
	int				x;
	int				y;
	int				tex_x;
	int				tex_y;
	char			*src_pixel;
	unsigned int	color;

	eye = &cub->texture->eye[cub->eye_anim_frame];
	if (!eye->addr)
		return ;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			tex_x = x * eye->width / WIDTH;
			tex_y = y * eye->height / HEIGHT;
			src_pixel = eye->addr + (tex_y * eye->line_length
					+ tex_x * (eye->bits_per_pixel / 8));
			color = *(unsigned int *)src_pixel;
			if (color == 0x000000)
				my_pixel_put(x, y, &cub->data.img, color);
			x++;
		}
		y++;
	}
}
