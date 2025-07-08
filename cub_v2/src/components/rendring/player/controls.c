/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:37:28 by iezzam            #+#    #+#             */
/*   Updated: 2025/05/30 11:53:02 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

int key_press(int key, t_cub *cub)
{
	if (key == XK_Escape)
		close_window(cub);
	if (key == XK_w)
		cub->player.key_up = true;
	if (key == XK_s)
		cub->player.key_down = true;
	if (key == XK_a)
		cub->player.key_left = true;
	if (key == XK_d)
		cub->player.key_right = true;
	if (key == XK_Left)
		cub->player.left_rotate = true;
	if (key == XK_Right)
		cub->player.right_rotate = true;
	if (key == XK_space)
		try_open_door(cub);
	return (0);
}

int key_release(int key, t_cub *cub)
{
	if (key == XK_Escape)
		close_window(cub);
	if (key == XK_w)
		cub->player.key_up = false;
	if (key == XK_s)
		cub->player.key_down = false;
	if (key == XK_a)
		cub->player.key_left = false;
	if (key == XK_d)
		cub->player.key_right = false;
	if (key == XK_Left)
		cub->player.left_rotate = false;
	if (key == XK_Right)
		cub->player.right_rotate = false;
	return (0);
}
