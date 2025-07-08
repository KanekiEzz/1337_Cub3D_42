/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:14:15 by iezzam            #+#    #+#             */
/*   Updated: 2025/05/29 16:14:45 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"


void draw_weapon(t_cub *cub)
{

  cub->weapon_anim_tick++;
  if (cub->weapon_anim_tick > cub->weapon_anim_speed)
  {
    cub->weapon_anim_tick = 0;
    cub->weapon_anim_frame++;
    if (cub->weapon_anim_frame >= MAX_ANIM_FRAMES)
      cub->weapon_anim_frame = 0;
  }

  int frame = cub->weapon_anim_frame;
  t_img *weapon = &cub->texture->weapon[cub->current_weapon_index * MAX_ANIM_FRAMES + frame];

  int scaled_width = weapon->width / 2;
  int scaled_height = weapon->height / 2;

  int x_start = (WIDTH - scaled_width) / 2;
  int y_start = HEIGHT - scaled_height / 1.2;

  int y = 0;

  while (y < scaled_height)
  {
    int x = 0;
    while (x < scaled_width)
    {
      int orig_x = x * 2;
      int orig_y = y * 2;

      char *src_pixel = weapon->addr + (orig_y * weapon->line_length + orig_x * (weapon->bits_per_pixel / 8));
      unsigned int color = *(unsigned int *)src_pixel;

      if ((color & 0x00FFFFFF) != 0)
      {
        my_pixel_put_img(&cub->data.img, x_start + x, y_start + y, color);
      }
      x++;
    }
    y++;
  }
}
