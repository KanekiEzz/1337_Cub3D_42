/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two_minimap.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 21:29:40 by iezzam            #+#    #+#             */
/*   Updated: 2025/06/02 12:05:59 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	render_draw_square(int x, int y, int size, t_cub *cub)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i <= size)
	{
		j = 0;
		while (j <= size)
		{
			if (i == 0 || j == 0 || i == size || j == size)
				my_pixel_put(x + i, y + j, &cub->data.img, \
					cub->color - 0x101010);
			else
				my_pixel_put(x + i, y + j, &cub->data.img, \
					cub->color);
			j++;
		}
		i++;
	}
}

void	draw_minimap_player(t_cub *cub, int center_x, int center_y)
{
	int	player_size;
	int	px;
	int	py;

	player_size = PLAYER_SIZE;
	py = -player_size;
	while (py <= player_size)
	{
		px = -player_size;
		while (px <= player_size)
		{
			if (px * px + py * py <= player_size * player_size)
				my_pixel_put(center_x + px, center_y + py,
					&cub->data.img, PLAYER_COLOR);
			px++;
		}
		py++;
	}
}

void	init_minimap_values(t_cub *cub)
{
	cub->minimap.offset_x = WIDTH - MINIMAP_WIDTH - 10;
	cub->minimap.offset_y = HEIGHT - MINIMAP_HEIGHT - 10;
	cub->minimap.center_x = cub->minimap.offset_x + MINIMAP_WIDTH / 2;
	cub->minimap.center_y = cub->minimap.offset_y + MINIMAP_HEIGHT / 2;
	cub->minimap.radius = MINIMAP_WIDTH / 2 - 5;
}

int	calculate_distance_sq(int x, int y, int center_x, int center_y)
{
	int	dx;
	int	dy;

	dx = x - center_x;
	dy = y - center_y;
	return (dx * dx + dy * dy);
}

void	draw_border_pixel(t_cub *cub, int x, int y, int radius)
{
	int	outer_radius;
	int	dist_sq;

	outer_radius = radius + 6;
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		dist_sq = calculate_distance_sq(x, y, cub->minimap.center_x,
				cub->minimap.center_y);
		if (dist_sq <= outer_radius * outer_radius
			&& dist_sq > radius * radius)
			my_pixel_put(x, y, &cub->data.img, 0x000000);
	}
}
