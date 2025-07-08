/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:55:45 by iezzam            #+#    #+#             */
/*   Updated: 2025/06/17 23:13:06 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

static void	rotate_player(t_cub *cub)
{
	if (cub->player.left_rotate)
		cub->player.angle -= 0.10;
	if (cub->player.right_rotate)
		cub->player.angle += 0.10;
	if (cub->player.angle > 2 * PI)
		cub->player.angle = 0;
	if (cub->player.angle < 0)
		cub->player.angle = 2 * PI;
}

static void	calculate_movement(t_cub *cub, float *new_x, float *new_y)
{
	int		speed;
	float	cos_a;
	float	sin_a;

	speed = 300;
	cos_a = cos(cub->player.angle);
	sin_a = sin(cub->player.angle);
	if (cub->player.key_up)
		*new_x += cos_a * speed;
	if (cub->player.key_up)
		*new_y += sin_a * speed;
	if (cub->player.key_down)
		*new_x -= cos_a * speed;
	if (cub->player.key_down)
		*new_y -= sin_a * speed;
	if (cub->player.key_left)
		*new_x += sin_a * speed;
	if (cub->player.key_left)
		*new_y -= cos_a * speed;
	if (cub->player.key_right)
		*new_x -= sin_a * speed;
	if (cub->player.key_right)
		*new_y += cos_a * speed;
}

void	handle_movement(t_cub *cub)
{
	float	new_x;
	float	new_y;

	rotate_player(cub);
	new_x = cub->player.x;
	new_y = cub->player.y;
	calculate_movement(cub, &new_x, &new_y);
	if (!touch_one(new_x, new_y, cub))
	{
		cub->player.x = new_x;
		cub->player.y = new_y;
	}
}

int	mouse_move(int x, int y, t_cub *cub)
{
	static int	last_x = -1;
	const float	sens = 0.002;
	int			delta_x;

	(void)y;
	if (last_x != -1)
	{
		delta_x = x - last_x;
		cub->player.angle += delta_x * sens;
		if (cub->player.angle < 0)
			cub->player.angle += 2 * PI;
		if (cub->player.angle > 2 * PI)
			cub->player.angle -= 2 * PI;
	}
	last_x = x;
	return (0);
}

void	try_open_door(t_cub *cub)
{
	int	px;
	int	py;
	int	fx;
	int	fy;

	px = (int)(cub->player.x / BLOCK);
	py = (int)(cub->player.y / BLOCK);
	fx = px + (int)round(cos(cub->player.angle));
	fy = py + (int)round(sin(cub->player.angle));
	cub->door_x = fx;
	cub->door_y = fy;
	if (cub->data.map.map[fy][fx] == '2')
	{
		cub->data.map.map[fy][fx] = 'D';
		log_state("OPENING DOOR", 1);
	}
	else if (cub->data.map.map[fy][fx] == 'D')
	{
		cub->data.map.map[fy][fx] = '2';
		log_state("CLOSING DOOR", 1);
	}
}
