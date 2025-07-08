/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 08:46:23 by iezzam            #+#    #+#             */
/*   Updated: 2025/06/01 21:36:10 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	draw_minimap_background(t_cub *cub, int center_x,
	int center_y, int radius)
{
	int	y;
	int	x;
	int	dx;
	int	dy;

	y = center_y - radius;
	while (y <= center_y + radius)
	{
		x = center_x - radius;
		while (x <= center_x + radius)
		{
			if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
			{
				dx = x - center_x;
				dy = y - center_y;
				if (dx * dx + dy * dy <= radius * radius)
					my_pixel_put(x, y, &cub->data.img, 0x101010 - 0x87CEEB);
			}
			x++;
		}
		y++;
	}
}

void	draw_minimap_border(t_cub *cub, int radius)
{
	int	y;
	int	x;

	y = cub->minimap.center_y - (radius + 6);
	while (y <= cub->minimap.center_y + (radius + 6))
	{
		x = cub->minimap.center_x - (radius + 6);
		while (x <= cub->minimap.center_x + (radius + 6))
		{
			draw_border_pixel(cub, x, y, radius);
			x++;
		}
		y++;
	}
}

static void	draw_direction_line(t_cub *cub, float x, float y, int radius)
{
	int	px;
	int	py;

	px = (int)x;
	py = (int)y;
	if (calculate_distance_sq(px, py, cub->minimap.center_x,
			cub->minimap.center_y) > radius * radius)
		return ;
	if (touch_one(px, py, cub))
		my_pixel_put(px, py, &cub->data.img, 0xFF0000);
}

void	draw_minimap_direction(t_cub *cub, int radius)
{
	float	dx;
	float	dy;
	float	x;
	float	y;
	int		i;

	dx = cosf(cub->player.angle);
	dy = sinf(cub->player.angle);
	x = cub->minimap.center_x;
	y = cub->minimap.center_y;
	i = 0;
	while (i < 40)
	{
		draw_direction_line(cub, x, y, radius);
		if ((int)x != cub->minimap.center_x || (int)y != cub->minimap.center_y)
			if (!touch_one((int)x, (int)y, cub))
				break ;
		x += dx;
		y += dy;
		i++;
	}
}

void	render_draw_minimap(t_cub *cub)
{
	init_minimap_values(cub);
	draw_minimap_background(cub, cub->minimap.center_x,
		cub->minimap.center_y, cub->minimap.radius);
	draw_minimap_walls(cub, cub->minimap.center_x,
		cub->minimap.center_y, cub->minimap.radius);
	draw_minimap_doors(cub, cub->minimap.center_x,
		cub->minimap.center_y, cub->minimap.radius);
	draw_minimap_border(cub, cub->minimap.radius);
	draw_minimap_player(cub, cub->minimap.center_x, cub->minimap.center_y);
	draw_minimap_direction(cub, cub->minimap.radius);
}
