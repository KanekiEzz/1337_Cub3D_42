/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:27:20 by iezzam            #+#    #+#             */
/*   Updated: 2025/05/30 11:58:28 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"


void update_enemy_animation(t_cub *cub)
{
  cub->enemy_anim_tick++;
  if (cub->enemy_anim_tick > cub->enemy_anim_speed)
  {
    cub->enemy_anim_tick = 0;
    cub->enemy_anim_frame = (cub->enemy_anim_frame + 1) % MAX_ENEMY;
  }
}

void calculate_enemy_sprites(t_cub *cub)
{
  for (int i = 0; i < cub->enemy_count; i++)
  {
    if (!cub->enemies[i].alive)
      continue;

    float dx = cub->enemies[i].x - cub->player.x;
    float dy = cub->enemies[i].y - cub->player.y;
    cub->enemies[i].dist = sqrt(dx * dx + dy * dy);

    float angle = atan2(dy, dx) - cub->player.angle;
    while (angle > PI)
      angle -= 2 * PI;
    while (angle < -PI)
      angle += 2 * PI;

    if (fabs(angle) < PI / 2)
    {
      cub->enemies[i].sprite_x = (int)((WIDTH / 2) * (1 + angle / (PI / 3)));
    }
    else
    {
      cub->enemies[i].sprite_x = -1;
    }
  }
}

void sort_enemies_by_distance(t_cub *cub)
{
  int i = 0;
  while (i < cub->enemy_count - 1)
  {
    int j = 0;
    while (j < cub->enemy_count - i - 1)
    {
      if (cub->enemies[j].dist < cub->enemies[j + 1].dist)
      {
        t_enemy temp = cub->enemies[j];
        cub->enemies[j] = cub->enemies[j + 1];
        cub->enemies[j + 1] = temp;
      }
      j++;
    }
    i++;
  }
}

float cast_single_ray(t_cub *cub, float ray_angle)
{
  float ray_dir_x = cos(ray_angle);
  float ray_dir_y = sin(ray_angle);

  int map_x = (int)cub->player.x / BLOCK;
  int map_y = (int)cub->player.y / BLOCK;

  float side_dist_x, side_dist_y;
  float delta_dist_x = fabs(1 / ray_dir_x);
  float delta_dist_y = fabs(1 / ray_dir_y);

  int step_x;
  if (ray_dir_x < 0)
    step_x = -1;
  else
    step_x = 1;

  int step_y;
  if (ray_dir_y < 0)
    step_y = -1;
  else
    step_y = 1;

  if (ray_dir_x < 0)
    side_dist_x = (cub->player.x - map_x * BLOCK) * delta_dist_x / BLOCK;
  else
    side_dist_x = ((map_x + 1) * BLOCK - cub->player.x) * delta_dist_x / BLOCK;

  if (ray_dir_y < 0)
    side_dist_y = (cub->player.y - map_y * BLOCK) * delta_dist_y / BLOCK;
  else
    side_dist_y = ((map_y + 1) * BLOCK - cub->player.y) * delta_dist_y / BLOCK;

  while (1)
  {
    if (side_dist_x < side_dist_y)
    {
      map_x += step_x;
      side_dist_x += delta_dist_x;
    }
    else
    {
      map_y += step_y;
      side_dist_y += delta_dist_y;
    }

    char tile = cub->data.map.map[map_y][map_x];
    if (tile == '1' || tile == '2' || tile == '3')
      break;
  }

  float dist;
  if (side_dist_x < side_dist_y)
    dist = side_dist_x * BLOCK;
  else
    dist = side_dist_y * BLOCK;

  return dist;
}

void draw_enemy(t_cub *cub)
{
  update_enemy_animation(cub);
  calculate_enemy_sprites(cub);
  sort_enemies_by_distance(cub);

  t_img *tex = &cub->texture->enemy[cub->enemy_anim_frame];
  if (!tex->img)
    return;

  int i = 0;
  while (i < cub->enemy_count)
  {
    if (!cub->enemies[i].alive || cub->enemies[i].sprite_x < 0)
    {
      i++;
      continue;
    }

    float dist = cub->enemies[i].dist;
    if (dist < 10.0f)
    {
      i++;
      continue;
    }

    float angle = atan2(cub->enemies[i].y - cub->player.y,
                        cub->enemies[i].x - cub->player.x);
    float ray_dist = cast_single_ray(cub, angle);
    if (ray_dist < dist - 10.0f)
    {
      i++;
      continue;
    }

    int sprite_size = (int)(HEIGHT / dist * BLOCK);
    int draw_x = cub->enemies[i].sprite_x - sprite_size / 2;
    int draw_y = (HEIGHT - sprite_size) / 2;

    float brightness = fmaxf(0.1f, 1.0f - (dist / (BLOCK * 8)));

    int y = 0;
    while (y < sprite_size)
    {
      int screen_y = draw_y + y;
      if (screen_y < 0 || screen_y >= HEIGHT)
      {
        y++;
        continue;
      }

      int x = 0;
      while (x < sprite_size)
      {
        int screen_x = draw_x + x;
        if (screen_x < 0 || screen_x >= WIDTH)
        {
          x++;
          continue;
        }

        int tex_x = x * tex->width / sprite_size;
        int tex_y = y * tex->height / sprite_size;

        unsigned int color = *(unsigned int *)(tex->addr +
                                               (tex_y * tex->line_length + tex_x * (tex->bits_per_pixel / 8)));

        if ((color & 0x00FFFFFF) != 0)
        {
          int r = ((color >> 16) & 0xFF) * brightness;
          int g = ((color >> 8) & 0xFF) * brightness;
          int b = (color & 0xFF) * brightness;
          my_pixel_put(screen_x, screen_y, &cub->data.img, (r << 16) | (g << 8) | b);
        }
        x++;
      }
      y++;
    }
    i++;
  }
}
