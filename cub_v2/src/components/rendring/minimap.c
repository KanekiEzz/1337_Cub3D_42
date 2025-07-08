/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 08:46:23 by iezzam            #+#    #+#             */
/*   Updated: 2025/06/26 17:16:31 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"
float calculate_light_intensity(t_cub *cub, int px, int py, int center_x, int center_y)
{
    float dx = px - center_x;
    float dy = py - center_y;
    float distance = sqrt(dx*dx + dy*dy);
    
    if (distance > 0) {
        dx /= distance;
        dy /= distance;
    }
    
    float player_dx = cos(cub->player.angle);
    float player_dy = sin(cub->player.angle);
    
    float dot = dx * player_dx + dy * player_dy;
    
    if (dot < 0.5f)
        return 0.0f;
    
    float max_distance = MINIMAP_WIDTH / 2;
    float distance_factor = 1.0f - (distance / max_distance);
    
    return distance_factor * (dot * dot); // Square dot to make falloff sharper
}
void render_draw_squaree(int x, int y, int size, int color, t_cub *cub, int center_x, int center_y)
{
    int i = 0;
    int j = 0;
    while (i <= size)
    {
        j = 0;
        while (j <= size)
        {
            int px = x + i;
            int py = y + j;
            float intensity = calculate_light_intensity(cub, px, py, center_x, center_y);
            
            if (intensity > 0.01f)
            {
                int r = (color >> 16) & 0xFF;
                int g = (color >> 8) & 0xFF;
                int b = color & 0xFF;
                
                r *= intensity;
                g *= intensity;
                b *= intensity;
                
                int shaded_color = (r << 16) | (g << 8) | b;
                
                if (i == 0 || j == 0 || i == size || j == size)
                    my_pixel_put(px, py, &cub->data.img, shaded_color - 0x101010);
                else
                    my_pixel_put(px, py, &cub->data.img, shaded_color);
            }
            j++;
        }
        i++;
    }
}

void draw_minimap_background(t_cub *cub, int center_x, int center_y, int radius)
{
    int y = center_y - radius;
    while (y <= center_y + radius)
    {
        int x = center_x - radius;
        while (x <= center_x + radius)
        {
            if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
            {
                const int dx = x - center_x;
                const int dy = y - center_y;
                if (dx*dx + dy*dy <= radius*radius)
                {
                    float intensity = calculate_light_intensity(cub, x, y, center_x, center_y);
                    
                    int r = 0x20 * intensity;
                    int g = 0xFF * intensity;
                    int b = 0x20 * intensity;
                    
                    my_pixel_put(x, y, &cub->data.img, (r << 16) | (g << 8) | b);
                }
            }
            x++;
        }
        y++;
    }
}

void draw_minimap_doors(t_cub *cub, int center_x, int center_y, int radius)
{
    const int player_map_x = cub->player.x / BLOCK;
    const int player_map_y = cub->player.y / BLOCK;
    const int visible_blocks = radius / BLOCK_SIZE;

    int dy = -visible_blocks;
    while (dy <= visible_blocks)
    {
        int dx = -visible_blocks;
        while (dx <= visible_blocks)
        {
            const int map_x = player_map_x + dx;
            const int map_y = player_map_y + dy;
            if (map_y >= 0 && map_y < MAP_HEIGHT && cub->data.map.map[map_y])
            {
                size_t row_len = ft_strlen(cub->data.map.map[map_y]);
                if (map_x >= 0 && map_x < (int)row_len && cub->data.map.map[map_y][map_x] == '2')
                {
                    const int screen_x = center_x + dx * BLOCK_SIZE;
                    const int screen_y = center_y + dy * BLOCK_SIZE;
                    const int dist_sq = (screen_x - center_x) * (screen_x - center_x) +
                                        (screen_y - center_y) * (screen_y - center_y);
                    if (dist_sq <= radius * radius)
                    {
                        render_draw_squaree(screen_x - BLOCK_SIZE / 2,
                                         screen_y - BLOCK_SIZE / 2,
                                         BLOCK_SIZE, 0xFF9813FF, cub,
                                         center_x, center_y);
                    }
                }
            }
            dx++;
        }
        dy++;
    }
}

void draw_minimap_walls(t_cub *cub, int center_x, int center_y, int radius)
{
    const int player_map_x = cub->player.x / BLOCK;
    const int player_map_y = cub->player.y / BLOCK;
    const int visible_blocks = radius / BLOCK_SIZE;

    int dy = -visible_blocks;
    while (dy <= visible_blocks)
    {
        int dx = -visible_blocks;
        while (dx <= visible_blocks)
        {
            const int map_x = player_map_x + dx;
            const int map_y = player_map_y + dy;
            if (map_y >= 0 && map_y < MAP_HEIGHT && cub->data.map.map[map_y])
            {
                size_t row_len = ft_strlen(cub->data.map.map[map_y]);
                if (map_x >= 0  &&map_x < (int)row_len && cub->data.map.map[map_y][map_x] == '1')
                {
                    const int screen_x = center_x + dx * BLOCK_SIZE;
                    const int screen_y = center_y + dy * BLOCK_SIZE;
                    const int dist_sq = (screen_x - center_x) * (screen_x - center_x) +
                                        (screen_y - center_y) * (screen_y - center_y);
                    if (dist_sq <= radius * radius)
                    {
                        render_draw_squaree(screen_x - BLOCK_SIZE / 2,
                                         screen_y - BLOCK_SIZE / 2,
                                         BLOCK_SIZE, WALL_COLOR, cub,
                                         center_x, center_y);
                    }
                }
            }
            dx++;
        }
        dy++;
    }
}

void draw_minimap_border(t_cub *cub, int center_x, int center_y, int radius, int border_width)
{
    const int outer_radius = radius + border_width;
    int y = center_y - outer_radius;
    
    while (y <= center_y + outer_radius)
    {
        int x = center_x - outer_radius;
        while (x <= center_x + outer_radius)
        {
            if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
            {
                const int dx = x - center_x;
                const int dy = y - center_y;
                const int dist_sq = dx * dx + dy * dy;
                if (dist_sq <= outer_radius * outer_radius && dist_sq > radius * radius)
                    my_pixel_put(x, y, &cub->data.img, 0x000000);
            }
            x++;
        }
        y++;
    }
}


void draw_minimap_player(t_cub *cub, int center_x, int center_y)
{
    int player_size = PLAYER_SIZE;
    int py = -player_size;
    while (py <= player_size)
    {
        int px = -player_size;
        while (px <= player_size)
        {
            if (px*px + py*py <= player_size*player_size)
                my_pixel_put(center_x + px, center_y + py, &cub->data.img, PLAYER_COLOR);
            px++;
        }
        py++;
    }
}

void render_draw_minimap(t_cub *cub)
{
    const int offset_x = WIDTH - MINIMAP_WIDTH - 10;
    const int offset_y = HEIGHT - MINIMAP_HEIGHT - 10;
    const int center_x = offset_x + MINIMAP_WIDTH / 2;
    const int center_y = offset_y + MINIMAP_HEIGHT / 2;
    const int radius = MINIMAP_WIDTH / 2 - 5;
    const int border_width = 6;

    draw_minimap_background(cub, center_x, center_y, radius);
    draw_minimap_walls(cub, center_x, center_y, radius);
    draw_minimap_doors(cub, center_x, center_y, radius);
    draw_minimap_border(cub, center_x, center_y, radius, border_width);
    draw_minimap_player(cub, center_x, center_y);
}