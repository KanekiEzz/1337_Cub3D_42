/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:15:19 by iezzam            #+#    #+#             */
/*   Updated: 2025/05/30 14:24:31 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void update_door_animation(t_cub *cub)
{

  cub->door_anim_tick++;
  cub->door_anim_active = 1;
  cub->door_anim_tick = 1;
  cub->door_anim_frame = 1;
  cub->door_anim_frame++;
}
