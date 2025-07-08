/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 18:38:32 by iezzam            #+#    #+#             */
/*   Updated: 2025/06/18 18:40:56 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

static void	destroy_img(t_cub *cub)
{
	if (cub->texture->door_img.img)
		mlx_destroy_image(cub->data.mlx, cub->texture->door_img.img);
	if (cub->texture->ea_img.img)
		mlx_destroy_image(cub->data.mlx, cub->texture->ea_img.img);
	if (cub->texture->we_img.img)
		mlx_destroy_image(cub->data.mlx, cub->texture->we_img.img);
	if (cub->texture->no_img.img)
		mlx_destroy_image(cub->data.mlx, cub->texture->no_img.img);
	if (cub->texture->so_img.img)
		mlx_destroy_image(cub->data.mlx, cub->texture->so_img.img);
	if (cub->data.img.img)
		mlx_destroy_image(cub->data.mlx, cub->data.img.img);
}

void	destroy_imgs_exit(t_cub *cub, char *msg)
{
	int	i;

	destroy_img(cub);
	i = 0;
	while (i < 18)
	{
		if (cub->texture->weapon[i].img)
			mlx_destroy_image(cub->data.mlx, cub->texture->weapon[i].img);
		i++;
	}
	mlx_destroy_window(cub->data.mlx, cub->data.win);
	mlx_destroy_display(cub->data.mlx);
	free(cub->data.mlx);
	if (msg)
		log_state(msg, 0);
	log_state("CLEANING...", 1);
	ft_malloc(-1);
	printf("[ BYE ! ]\n");
	exit(0);
}
