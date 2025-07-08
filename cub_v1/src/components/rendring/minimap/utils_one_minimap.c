/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_one_minimap.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 21:15:40 by iezzam            #+#    #+#             */
/*   Updated: 2025/06/02 11:59:48 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

static int	is_valid_map_position(t_cub *cub, int map_x, int map_y, int map_h)
{
	size_t	row_len;

	if (map_y < 0 || map_y >= map_h || !cub->data.map.map[map_y])
		return (0);
	row_len = ft_strlen(cub->data.map.map[map_y]);
	if (map_x < 0 || map_x >= (int)row_len)
		return (0);
	return (1);
}

static void	draw_block_if_in_radius(t_cub *cub, int dx, int dy, char block_type)
{
	int	screen_x;
	int	screen_y;
	int	dist_sq;

	screen_x = cub->minimap.center_x + dx * BLOCK_SIZE;
	screen_y = cub->minimap.center_y + dy * BLOCK_SIZE;
	dist_sq = (screen_x - cub->minimap.center_x) * \
		(screen_x - cub->minimap.center_x) + \
		(screen_y - cub->minimap.center_y) * \
		(screen_y - cub->minimap.center_y);
	if (dist_sq <= cub->minimap.radius * cub->minimap.radius)
	{
		if (block_type == '1')
			cub->color = WALL_COLOR;
		else
			cub->color = DOOR_COLOR;
		render_draw_square(screen_x - BLOCK_SIZE / 2,
			screen_y - BLOCK_SIZE / 2, BLOCK_SIZE, cub);
	}
}

static void	process_map_block(t_cub *cub, int dx, int dy, char target_char)
{
	int	player_map_x;
	int	player_map_y;
	int	map_x;
	int	map_y;
	int	map_height;

	player_map_x = cub->player.x / BLOCK;
	player_map_y = cub->player.y / BLOCK;
	map_x = player_map_x + dx;
	map_y = player_map_y + dy;
	map_height = get_map_height(cub->data.map.map);
	if (is_valid_map_position(cub, map_x, map_y, map_height))
	{
		if (cub->data.map.map[map_y][map_x] == target_char)
			draw_block_if_in_radius(cub, dx, dy, target_char);
	}
}

void	draw_minimap_doors(t_cub *cub, int center_x, int center_y, int radius)
{
	int	visible_blocks;
	int	dy;
	int	dx;

	cub->minimap.center_x = center_x;
	cub->minimap.center_y = center_y;
	cub->minimap.radius = radius;
	visible_blocks = radius / BLOCK_SIZE;
	dy = -visible_blocks;
	while (dy <= visible_blocks)
	{
		dx = -visible_blocks;
		while (dx <= visible_blocks)
		{
			process_map_block(cub, dx, dy, '2');
			dx++;
		}
		dy++;
	}
}

void	draw_minimap_walls(t_cub *cub, int center_x, int center_y, int radius)
{
	int	visible_blocks;
	int	dy;
	int	dx;

	cub->minimap.center_x = center_x;
	cub->minimap.center_y = center_y;
	cub->minimap.radius = radius;
	visible_blocks = radius / BLOCK_SIZE;
	dy = -visible_blocks;
	while (dy <= visible_blocks)
	{
		dx = -visible_blocks;
		while (dx <= visible_blocks)
		{
			process_map_block(cub, dx, dy, '1');
			dx++;
		}
		dy++;
	}
}
