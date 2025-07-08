/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_weapon.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 15:02:03 by iezzam            #+#    #+#             */
/*   Updated: 2025/06/18 18:30:32 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

static const char	**get_weapon_texture_paths(void)
{
	static const char	*paths[18] = {
		"./textures/player1/01.xpm",
		"./textures/player1/02.xpm",
		"./textures/player1/03.xpm",
		"./textures/player1/04.xpm",
		"./textures/player1/05.xpm",
		"./textures/player1/06.xpm",
		"./textures/player1/07.xpm",
		"./textures/player1/08.xpm",
		"./textures/player1/09.xpm",
		"./textures/player1/010.xpm",
		"./textures/player1/011.xpm",
		"./textures/player1/012.xpm",
		"./textures/player1/013.xpm",
		"./textures/player1/014.xpm",
		"./textures/player1/015.xpm",
		"./textures/player1/016.xpm",
		"./textures/player1/017.xpm",
		"./textures/player1/018.xpm"
	};

	return (paths);
}

static int	load_single_weapon_texture(t_cub *cub, const char *path, int frame)
{
	cub->texture->weapon[frame].img = mlx_xpm_file_to_image(
			cub->data.mlx,
			(char *)path,
			&cub->texture->weapon[frame].width,
			&cub->texture->weapon[frame].height);
	if (!cub->texture->weapon[frame].img)
	{
		ft_putendl_fd("Error\nFailed to load weapon texture", 2);
		return (1);
	}
	cub->texture->weapon[frame].addr = mlx_get_data_addr(
			cub->texture->weapon[frame].img,
			&cub->texture->weapon[frame].bits_per_pixel,
			&cub->texture->weapon[frame].line_length,
			&cub->texture->weapon[frame].endian);
	return (0);
}

static int	load_all_weapon_textures(t_cub *cub)
{
	const char	**paths;
	int			f;

	paths = get_weapon_texture_paths();
	f = 0;
	while (f < 18)
	{
		if (load_single_weapon_texture(cub, paths[f], f))
			return (1);
		f++;
	}
	return (0);
}

int	init_textures_weapon(t_cub *cub)
{
	cub->texture->weapon = ft_malloc(sizeof(t_img) * 18);
	if (load_all_weapon_textures(cub))
		destroy_imgs_exit(cub, "FAILED TO LOAD WEAPON TEXTURE");
	init_weapon_animation_params(cub);
	return (0);
}
