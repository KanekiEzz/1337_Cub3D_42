/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_sky.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:11:23 by iezzam            #+#    #+#             */
/*   Updated: 2025/05/31 13:20:38 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

static void	draw_half_background(t_img *img, int color, int start_y, int end_y)
{
	int	x;
	int	y;

	y = start_y;
	while (y < end_y)
	{
		x = 0;
		while (x < WIDTH)
		{
			my_pixel_put(x, y, img, color);
			x++;
		}
		y++;
	}
}

void	draw_split_background(t_cub *cub)
{
	int	floor_color;
	int	sky_color;
	int	screen_middle;

	screen_middle = HEIGHT / 2;
	floor_color = (cub->texture->floor_grb[0] << 16)
		| (cub->texture->floor_grb[1] << 8)
		| cub->texture->floor_grb[2];
	sky_color = (cub->texture->sky_grb[0] << 16)
		| (cub->texture->sky_grb[1] << 8)
		| cub->texture->sky_grb[2];
	draw_half_background(&cub->data.img, sky_color, 0, screen_middle);
	draw_half_background(&cub->data.img, floor_color, screen_middle, HEIGHT);
}
