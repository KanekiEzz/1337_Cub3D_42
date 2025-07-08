/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_sky.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 16:11:23 by iezzam            #+#    #+#             */
/*   Updated: 2025/05/29 16:12:35 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"


void draw_split_background(t_cub *cub)
{
  int screen_middle = HEIGHT / 2;
  int floor_width = cub->texture->floor_img.width;
  int floor_height = cub->texture->floor_img.height;

  float posX = cub->player.x;
  float posY = cub->player.y;

  float planeX = cos(cub->player.angle + PI / 2) * 0.66f;
  float planeY = sin(cub->player.angle + PI / 2) * 0.66f;

  float light_radius = 2.0f;
  float max_brightness = 1.0f;
  float min_brightness = 0.1f;
  int y = screen_middle;
  while (y < HEIGHT)
  {
    float rayDirZ = (float)(y - HEIGHT / 2);
    float rowDistance = (float)(HEIGHT / 2) / rayDirZ;
    int x = 0;
    while (x < WIDTH)
    {
      float cameraX = 2 * x / (float)WIDTH - 1;
      float rayDirX = cos(cub->player.angle) + planeX * cameraX;
      float rayDirY = sin(cub->player.angle) + planeY * cameraX;
      float floorX = posX + rowDistance * rayDirX;
      float floorY = posY + rowDistance * rayDirY;
      int tx = (int)(floorX * floor_width) % floor_width;
      int ty = (int)(floorY * floor_height) % floor_height;
      if (tx < 0)
        tx += floor_width;
      if (ty < 0)
        ty += floor_height;
      char *pixel_addr = cub->texture->floor_img.addr + (ty * cub->texture->floor_img.line_length) + (tx * (cub->texture->floor_img.bits_per_pixel / 8));
      unsigned int color = *(unsigned int *)pixel_addr;
      float dx = floorX - posX;
      float dy = floorY - posY;
      float dist = sqrtf(dx * dx + dy * dy);
      float brightness = 1.0f - (dist / light_radius);
      brightness = fmaxf(fminf(brightness, max_brightness), min_brightness);
      int r = ((color >> 16) & 0xFF) * brightness;
      int g = ((color >> 8) & 0xFF) * brightness;
      int b = (color & 0xFF) * brightness;
      int shaded_color = (r << 16) | (g << 8) | b;
      my_pixel_put(x, y, &cub->data.img, shaded_color);
      x++;
    }
    y++;
  }
}
