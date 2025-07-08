/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:55:45 by iezzam            #+#    #+#             */
/*   Updated: 2025/05/30 13:44:48 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

int close_window(t_cub *cub)
{
	mlx_destroy_window(cub->data.mlx, cub->data.win);
	exit(0);
	return (0);
}

void handle_movement(t_cub *cub)
{

	int speed = 300;
	float rotation_speed = 0.10;
	float cos_angle = cos(cub->player.angle);
	float sin_angle = sin(cub->player.angle);
	float new_x = cub->player.x;
	float new_y = cub->player.y;

	if (cub->player.left_rotate)
		cub->player.angle -= rotation_speed;
	if (cub->player.right_rotate)
		cub->player.angle += rotation_speed;
	if (cub->player.angle > 2 * PI)
		cub->player.angle = 0;
	if (cub->player.angle < 0)
		cub->player.angle = 2 * PI;

	if (cub->player.key_up)
	{
		new_x += cos_angle * speed;
		new_y += sin_angle * speed;
	}
	if (cub->player.key_down)
	{
		new_x -= cos_angle * speed;
		new_y -= sin_angle * speed;
	}
	if (cub->player.key_left)
	{
		new_x += sin_angle * speed;
		new_y -= cos_angle * speed;
	}
	if (cub->player.key_right)
	{
		new_x -= sin_angle * speed;
		new_y += cos_angle * speed;
	}

	if (!touch_one(new_x, new_y, cub))
	{
		cub->player.x = new_x;
		cub->player.y = new_y;
	}
}

int mouse_move(int x, int y, t_cub *cub)
{
	static int last_x = -1;
	const float sensitivity = 0.002;

	(void)y;
	if (last_x != -1)
	{
		int delta_x = x - last_x;
		cub->player.angle += delta_x * sensitivity;
		if (cub->player.angle < 0)
			cub->player.angle += 2 * PI;
		if (cub->player.angle > 2 * PI)
			cub->player.angle -= 2 * PI;
	}
	last_x = x;
	return (0);
}

int mouse_scroll(int button, int x, int y, t_cub *cub)
{
	(void)x;
	(void)y;

	if (button == 4)
	{
		cub->current_weapon_index--;
		if (cub->current_weapon_index < 0)
			cub->current_weapon_index = MAX_WEAPONS - 1;
	}
	else if (button == 5)
	{
		cub->current_weapon_index++;
		if (cub->current_weapon_index >= MAX_WEAPONS)
			cub->current_weapon_index = 0;
	}
	else if (button == 1)
	{
		if (!cub->weapon_anim_active)
		{
			cub->weapon_anim_active = 1;
			cub->weapon_anim_frame = 0;
			cub->weapon_anim_tick = 0;
		}
	}
	return (0);
}

void try_open_door(t_cub *cub)
{
	int px = (int)(cub->player.x / BLOCK);
	int py = (int)(cub->player.y / BLOCK);

	int fx = px + (int)round(cos(cub->player.angle));
	int fy = py + (int)round(sin(cub->player.angle));
	cub->door_opened = 0;

	cub->door_x = fx;
	cub->door_y = fy;
	if (cub->data.map.map[fy][fx] == '2')
		cub->data.map.map[cub->door_y][cub->door_x] = 'D';
	else if (cub->data.map.map[fy][fx] == 'D')
		cub->data.map.map[cub->door_y][cub->door_x] = '2';
}
