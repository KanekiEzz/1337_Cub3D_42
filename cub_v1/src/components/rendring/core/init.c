/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:06:51 by iezzam            #+#    #+#             */
/*   Updated: 2025/06/17 23:32:26 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

static void	set_player_angle(t_player *player, char dir)
{
	if (!player)
		return ;
	if (dir == 'N')
		player->angle = PI / 2;
	else if (dir == 'S')
		player->angle = 3 * PI / 2;
	else if (dir == 'E')
		player->angle = 0;
	else if (dir == 'W')
		player->angle = PI;
}

void	init_player(t_player *player, t_cub *cub)
{
	int		x;
	int		y;
	char	dir;

	(1) && (player->key_up = false, player->key_down = false, \
		player->key_left = false, player->key_right = false, \
		player->left_rotate = false, player->right_rotate = false, y = 0);
	while (cub->data.map.map[y])
	{
		x = 0;
		while (cub->data.map.map[y][x])
		{
			dir = cub->data.map.map[y][x];
			if (dir == 'N' || dir == 'S' || dir == 'E' || dir == 'W')
			{
				player->x = x * BLOCK + BLOCK / 2;
				player->y = y * BLOCK + BLOCK / 2;
				set_player_angle(player, dir);
				cub->data.map.map[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
}

int	init_image(t_cub *cub)
{
	log_state("CREATING MAIN IMG DISPLAY", 3);
	cub->data.img.img = mlx_new_image(cub->data.mlx, WIDTH, HEIGHT);
	if (!cub->data.img.img)
		return (1);
	log_state("CREATING MAIN IMG DISPLAY", 1);
	cub->data.img.addr = mlx_get_data_addr(cub->data.img.img,
			&cub->data.img.bits_per_pixel,
			&cub->data.img.line_length,
			&cub->data.img.endian);
	cub->data.img.mlx = cub->data.mlx;
	cub->data.img.win = cub->data.win;
	return (0);
}

void	init_texture_door(t_cub *cub)
{
	cub->texture->door_img.img = mlx_xpm_file_to_image(cub->data.mlx,
			"./textures/door/__door2.xpm",
			&cub->texture->door_img.width,
			&cub->texture->door_img.height);
	if (!cub->texture->door_img.img)
		destroy_imgs_exit(cub, "FAILED TO LOAD DOOR TEXTURE");
	cub->texture->door_img.addr = mlx_get_data_addr(cub->texture->door_img.img,
			&cub->texture->door_img.bits_per_pixel,
			&cub->texture->door_img.line_length,
			&cub->texture->door_img.endian);
}

int	init_window(t_cub *cub)
{
	log_state("CREATING WINDOW", 3);
	cub->data.mlx = mlx_init();
	if (!cub->data.mlx)
		return (log_state("FAIL TO CREATE CONNECTION", 0), 1);
	cub->data.win = mlx_new_window(cub->data.mlx, WIDTH, HEIGHT, "Cub3d");
	if (!cub->data.win)
		return (mlx_destroy_display(cub->data.mlx), free(cub->data.mlx),
			log_state("FAIL TO CREATE WINDOW", 0), 1);
	log_state("WINDOW CREATED SUCCESSFULLY", 1);
	init_player(&cub->player, cub);
	if (init_image(cub))
		return (destroy_imgs_exit(cub, "FAILED TO CREATE MAIN IMG"), 1);
	log_state("LOADING TEXTURES ...", 3);
	init_textures_weapon(cub);
	init_texture_wall(cub);
	init_texture_door(cub);
	log_state("TEXTURES LOADED", 1);
	if (event_hook_window(cub))
		return (1);
	return (0);
}
