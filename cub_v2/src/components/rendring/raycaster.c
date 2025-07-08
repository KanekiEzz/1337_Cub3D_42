/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 08:49:34 by iezzam            #+#    #+#             */
/*   Updated: 2025/05/30 13:34:04 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

float calculate_brightness(float dist, float max_distance, float min_brightness, float max_brightness)
{
  float brightness = 1.0f - (dist / max_distance);
  return fmaxf(fminf(brightness, max_brightness), min_brightness);
}

unsigned int apply_shading(unsigned int color, float brightness)
{
  int r = ((color >> 16) & 0xFF) * brightness;
  int g = ((color >> 8) & 0xFF) * brightness;
  int b = (color & 0xFF) * brightness;
  int alpha = (color >> 24) & 0xFF;

  return (alpha << 24) | (r << 16) | (g << 8) | b;
}

void draw_wall(t_cub *cub, int screen_x, float ray_dx, float ray_dy,
               float ray_x, float ray_y, int side, float dist)
{
  float wall_height = (BLOCK / dist) * (WIDTH / 2);
  int start_y = (HEIGHT - wall_height) / 2;
  if (start_y < 0)
    start_y = 0;
  int end_y = start_y + wall_height;
  if (end_y > HEIGHT)
    end_y = HEIGHT;

  t_img *tex;
  float wall_hit;

  if (side == 0)
  {
    if (ray_dx < 0)
      tex = &cub->texture->we_img;
    else
      tex = &cub->texture->ea_img;
    wall_hit = fmod(ray_y, BLOCK) / BLOCK;
  }
  else
  {
    if (ray_dy < 0)
      tex = &cub->texture->no_img;
    else
      tex = &cub->texture->so_img;
    wall_hit = fmod(ray_x, BLOCK) / BLOCK;
  }

  int tex_x = (int)(wall_hit * tex->width);
  if ((side == 0 && ray_dx > 0) || (side == 1 && ray_dy < 0))
    tex_x = tex->width - tex_x - 1;

  float step = (float)tex->height / wall_height;
  float tex_pos = (start_y - HEIGHT / 2 + wall_height / 2) * step;

  float max_distance = BLOCK * 6;
  float min_brightness = 0.05f;
  float max_brightness = 1.2f;
  float brightness = calculate_brightness(dist, max_distance, min_brightness, max_brightness);

  if (side == 1)
    brightness *= 0.8f;

  int y = start_y;
  while (y < end_y)
  {
    int tex_y = (int)tex_pos & (tex->height - 1);
    tex_pos += step;
    char *pixel = tex->addr + (tex_y * tex->line_length + tex_x * (tex->bits_per_pixel / 8));
    unsigned int color = *(unsigned int *)pixel;

    unsigned int shaded_color = apply_shading(color, brightness);

    my_pixel_put(screen_x, y, &cub->data.img, shaded_color);
    y++;
  }
}

void draw_door(t_cub *cub, int screen_x, float ray_dx, float ray_dy,
               float ray_x, float ray_y, int side, float dist)
{
  float wall_height = (BLOCK / dist) * (WIDTH / 2);
  int start_y = (HEIGHT - wall_height) / 2;
  if (start_y < 0)
    start_y = 0;
  int end_y = start_y + wall_height;
  if (end_y > HEIGHT)
    end_y = HEIGHT;

  t_img *tex = NULL;
  if (cub->door_anim_active)
    tex = &cub->door_textures[cub->door_anim_frame];
  else
    tex = &cub->door_textures[0];

  if (!tex || !tex->img)
    return;

  float wall_hit;
  if (side == 0)
    wall_hit = fmod(ray_y, BLOCK) / BLOCK;
  else
    wall_hit = fmod(ray_x, BLOCK) / BLOCK;

  int tex_x = (int)(wall_hit * tex->width);
  if ((side == 0 && ray_dx > 0) || (side == 1 && ray_dy < 0))
    tex_x = tex->width - tex_x - 1;

  float step = (float)tex->height / wall_height;
  float tex_pos = (start_y - HEIGHT / 2 + wall_height / 2) * step;

  float max_distance = BLOCK * 6;
  float min_brightness = 0.05f;
  float max_brightness = 1.2f;
  float brightness = calculate_brightness(dist, max_distance, min_brightness, max_brightness);

  if (side == 1)
    brightness *= 0.8f;

  int y = start_y;
  while (y < end_y)
  {
    int tex_y = (int)tex_pos & (tex->height - 1);
    tex_pos += step;
    char *pixel = tex->addr + (tex_y * tex->line_length + tex_x * (tex->bits_per_pixel / 8));
    unsigned int color = *(unsigned int *)pixel;
    unsigned int shaded_color = apply_shading(color, brightness);

    my_pixel_put(screen_x, y, &cub->data.img, shaded_color);
    y++;
  }
}

void cast_ray(t_cub *cub, float ray_angle, int screen_x)
{
  float ray_dir_x = cos(ray_angle);
  float ray_dir_y = sin(ray_angle);

  int map_x = (int)cub->player.x / BLOCK;
  int map_y = (int)cub->player.y / BLOCK;

  float side_dist_x;
  float side_dist_y;

  float delta_dist_x = fabs(1 / ray_dir_x);
  float delta_dist_y = fabs(1 / ray_dir_y);

  int step_x;
  int step_y;
  int side;

  float pos_x = cub->player.x;
  float pos_y = cub->player.y;

  if (ray_dir_x < 0)
  {
    step_x = -1;
    side_dist_x = (pos_x - map_x * BLOCK) * delta_dist_x / BLOCK;
  }
  else
  {
    step_x = 1;
    side_dist_x = ((map_x + 1) * BLOCK - pos_x) * delta_dist_x / BLOCK;
  }

  if (ray_dir_y < 0)
  {
    step_y = -1;
    side_dist_y = (pos_y - map_y * BLOCK) * delta_dist_y / BLOCK;
  }
  else
  {
    step_y = 1;
    side_dist_y = ((map_y + 1) * BLOCK - pos_y) * delta_dist_y / BLOCK;
  }

  char hit_tile = ' ';
  while (1)
  {
    if (side_dist_x < side_dist_y)
    {
      map_x += step_x;
      side_dist_x += delta_dist_x;
      side = 0;
    }
    else
    {
      map_y += step_y;
      side_dist_y += delta_dist_y;
      side = 1;
    }

    hit_tile = cub->data.map.map[map_y][map_x];
    if (hit_tile == '1' || hit_tile == '2' || hit_tile == '3')
      break;
  }

  float hit_x, hit_y;
  if (side == 0)
  {
    hit_x = cub->player.x + (map_x * BLOCK - cub->player.x + (1 - step_x) * BLOCK / 2) / ray_dir_x * ray_dir_x;
    hit_y = cub->player.y + (map_x * BLOCK - cub->player.x + (1 - step_x) * BLOCK / 2) / ray_dir_x * ray_dir_y;
  }
  else
  {
    hit_x = cub->player.x + (map_y * BLOCK - cub->player.y + (1 - step_y) * BLOCK / 2) / ray_dir_y * ray_dir_x;
    hit_y = cub->player.y + (map_y * BLOCK - cub->player.y + (1 - step_y) * BLOCK / 2) / ray_dir_y * ray_dir_y;
  }

  float dist = use_fixed_dist(cub->player.x, cub->player.y, hit_x, hit_y, cub);
  if (hit_tile == '2')
    draw_door(cub, screen_x, ray_dir_x, ray_dir_y, hit_x, hit_y, side, dist);
  else if (hit_tile == '1')
    draw_wall(cub, screen_x, ray_dir_x, ray_dir_y, hit_x, hit_y, side, dist);
}

int game_loop(t_cub *cub)
{
  handle_movement(cub);
  clear_image(cub);
  draw_split_background(cub);

  float ray_step = (PI / 3) / WIDTH;
  float ray_angle = cub->player.angle - (PI / 6);

  int x = 0;
  while (x < WIDTH)
  {
    cast_ray(cub, ray_angle, x);
    ray_angle += ray_step;
    x++;
  }

  draw_enemy(cub);
  draw_weapon(cub);
  draw_eye(cub);
  update_eye_animation(cub);
  render_draw_minimap(cub);
  update_door_animation(cub);
  mlx_put_image_to_window(cub->data.mlx, cub->data.win, cub->data.img.img, 0, 0);
  return 0;
}