/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:37:28 by iezzam            #+#    #+#             */
/*   Updated: 2025/06/17 23:29:14 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

int	event_hook_window(t_cub *cub)
{
	mlx_hook(cub->data.win, 17, 0, close_window, cub);
	log_state("KEY BINDING", 1);
	mlx_hook(cub->data.win, 2, 1L << 0, key_press, cub);
	mlx_hook(cub->data.win, 3, 1L << 1, key_release, cub);
	mlx_hook(cub->data.win, 6, 1L << 6, mouse_move, cub);
	log_state("MOUSE BINDING", 1);
	log_state("LOADING GANE ...", 3);
	mlx_loop_hook(cub->data.mlx, game_loop, cub);
	mlx_loop(cub->data.mlx);
	return (0);
}

int	close_window(t_cub *cub)
{
	destroy_imgs_exit(cub, NULL);
	return (0);
}

int	key_press(int key, t_cub *cub)
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

int	key_release(int key, t_cub *cub)
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
