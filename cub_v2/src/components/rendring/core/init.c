/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:06:51 by iezzam            #+#    #+#             */
/*   Updated: 2025/05/30 14:24:29 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void init_player(t_player *player, t_cub *cub)
{
    player->key_up = false;
    player->key_down = false;
    player->key_left = false;
    player->key_right = false;
    player->left_rotate = false;
    player->right_rotate = false;

    for (int y = 0; cub->data.map.map[y]; y++)
    {
        for (int x = 0; cub->data.map.map[y][x]; x++)
        {
            char dir = cub->data.map.map[y][x];
            if (dir == 'N' || dir == 'S' || dir == 'E' || dir == 'W')
            {
                player->x = x * BLOCK + BLOCK / 2;
                player->y = y * BLOCK + BLOCK / 2;

                if (dir == 'N')
                    player->angle = PI / 2;
                else if (dir == 'S')
                    player->angle = 3 * PI / 2;
                else if (dir == 'E')
                    player->angle = 0;
                else if (dir == 'W')
                    player->angle = PI;

                cub->data.map.map[y][x] = '0';
                return;
            }
        }
    }
}

int init_image(t_cub *cub)
{
    cub->data.img.img = mlx_new_image(cub->data.mlx, WIDTH, HEIGHT);
    if (!cub->data.img.img)
        return (perror("Fail to open img"), 1);
    cub->data.img.addr = mlx_get_data_addr(cub->data.img.img, &cub->data.img.bits_per_pixel,
                                           &cub->data.img.line_length, &cub->data.img.endian);
    cub->data.img.mlx = cub->data.mlx;
    cub->data.img.win = cub->data.win;
    return (0);
}

int event_hook_window(t_cub *cub)
{
    mlx_hook(cub->data.win, 17, 0, close_window, cub);
    mlx_hook(cub->data.win, 2, 1L << 0, key_press, cub);
    mlx_hook(cub->data.win, 3, 1L << 1, key_release, cub);
    mlx_hook(cub->data.win, 6, 1L << 6, mouse_move, cub);
    mlx_hook(cub->data.win, 4, 1L << 2, mouse_scroll, cub);
    mlx_loop_hook(cub->data.mlx, game_loop, cub);

    mlx_loop(cub->data.mlx);
    return (0);
}

#define MAX_FRAMES 18

int init_textures_weapon(t_cub *cub)
{
    const char *paths[MAX_FRAMES] = {
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
        "./textures/player1/018.xpm"};

    cub->texture->weapon = malloc(sizeof(t_img) * MAX_FRAMES);
    if (!cub->texture->weapon)
    {
        ft_putendl_fd("Error\nMemory allocation failed for weapon textures", 2);
        exit(1);
    }

    for (int f = 0; f < MAX_FRAMES; f++)
    {
        cub->texture->weapon[f].img = mlx_xpm_file_to_image(
            cub->data.mlx,
            (char *)paths[f],
            &cub->texture->weapon[f].width,
            &cub->texture->weapon[f].height);

        if (!cub->texture->weapon[f].img)
        {
            ft_putendl_fd("Error\nFailed to load weapon texture", 2);
            exit(1);
        }

        cub->texture->weapon[f].addr = mlx_get_data_addr(
            cub->texture->weapon[f].img,
            &cub->texture->weapon[f].bits_per_pixel,
            &cub->texture->weapon[f].line_length,
            &cub->texture->weapon[f].endian);
    }
    cub->weapon_anim_speed = 1;

    cub->current_weapon_index = 1;
    cub->weapon_anim_frame = 1;
    cub->weapon_anim_active = 1;
    cub->weapon_anim_tick = 1;

    return 0;
}

void init_texture_wall(t_cub *cub)
{
    cub->texture->no_img.img = mlx_xpm_file_to_image(cub->data.mlx,
                                                     cub->texture->no_path, &cub->texture->no_img.width, &cub->texture->no_img.height);
    if (!cub->texture->no_img.img)
    {
        perror("Failed to load north texture");
        exit(1);
    }
    cub->texture->no_img.addr = mlx_get_data_addr(cub->texture->no_img.img,
                                                  &cub->texture->no_img.bits_per_pixel, &cub->texture->no_img.line_length,
                                                  &cub->texture->no_img.endian);

    cub->texture->so_img.img = mlx_xpm_file_to_image(cub->data.mlx,
                                                     cub->texture->so_path, &cub->texture->so_img.width, &cub->texture->so_img.height);
    if (!cub->texture->so_img.img)
        perror("Failed to load south texture");
    cub->texture->so_img.addr = mlx_get_data_addr(cub->texture->so_img.img,
                                                  &cub->texture->so_img.bits_per_pixel, &cub->texture->so_img.line_length,
                                                  &cub->texture->so_img.endian);

    cub->texture->we_img.img = mlx_xpm_file_to_image(cub->data.mlx,
                                                     cub->texture->we_path, &cub->texture->we_img.width, &cub->texture->we_img.height);
    if (!cub->texture->we_img.img)
        perror("Failed to load west texture");
    cub->texture->we_img.addr = mlx_get_data_addr(cub->texture->we_img.img,
                                                  &cub->texture->we_img.bits_per_pixel, &cub->texture->we_img.line_length,
                                                  &cub->texture->we_img.endian);

    cub->texture->ea_img.img = mlx_xpm_file_to_image(cub->data.mlx,
                                                     cub->texture->ea_path, &cub->texture->ea_img.width, &cub->texture->ea_img.height);
    if (!cub->texture->ea_img.img)
        perror("Failed to load east texture");
    cub->texture->ea_img.addr = mlx_get_data_addr(cub->texture->ea_img.img,
                                                  &cub->texture->ea_img.bits_per_pixel, &cub->texture->ea_img.line_length,
                                                  &cub->texture->ea_img.endian);
}
void init_texture_door(t_cub *cub)
{
    cub->texture->door_img.img = mlx_xpm_file_to_image(cub->data.mlx,
                                                       "./textures/door/door.xpm", &cub->texture->door_img.width, &cub->texture->door_img.height);
    if (!cub->texture->door_img.img)
    {
        ft_putendl_fd("Error\nFailed to load door texture", 2);
        exit(1);
    }
    cub->texture->door_img.addr = mlx_get_data_addr(cub->texture->door_img.img,
                                                    &cub->texture->door_img.bits_per_pixel, &cub->texture->door_img.line_length,
                                                    &cub->texture->door_img.endian);
}

void init_texture_floor(t_cub *cub)
{
    cub->texture->floor_img.img = mlx_xpm_file_to_image(cub->data.mlx,
                                                        "./textures/floor/floor.xpm", &cub->texture->floor_img.width, &cub->texture->floor_img.height);
    if (!cub->texture->floor_img.img)
    {
        ft_putendl_fd("Error\nFailed to load floor texture", 2);
        exit(1);
    }
    cub->texture->floor_img.addr = mlx_get_data_addr(cub->texture->floor_img.img,
                                                     &cub->texture->floor_img.bits_per_pixel, &cub->texture->floor_img.line_length,
                                                     &cub->texture->floor_img.endian);
}

void init_texture_door_anim(t_cub *cub)
{
    char *door_paths[MAX_DOOR_FRAMES] = {
        "./textures/door/1.xpm",
        "./textures/door/2.xpm",
        "./textures/door/3.xpm",
        "./textures/door/4.xpm",
        "./textures/door/5.xpm",
        "./textures/door/6.xpm"};

    for (int i = 0; i < MAX_DOOR_FRAMES; i++)
    {
        cub->door_textures[i].img = mlx_xpm_file_to_image(cub->data.mlx,
                                                          door_paths[i], &cub->door_textures[i].width, &cub->door_textures[i].height);
        if (!cub->door_textures[i].img)
        {
            ft_putendl_fd("Error loading door animation texture", 2);
            while (--i >= 0)
                mlx_destroy_image(cub->data.mlx, cub->door_textures[i].img);
            exit(EXIT_FAILURE);
        }
        cub->door_textures[i].addr = mlx_get_data_addr(cub->door_textures[i].img,
                                                       &cub->door_textures[i].bits_per_pixel, &cub->door_textures[i].line_length,
                                                       &cub->door_textures[i].endian);
    }

    cub->door_anim_active = 0;
    cub->door_anim_frame = 0;
    cub->door_anim_tick = 0;
}
void put_large_text(t_cub *cub, int frame_number)
{
    char path[256];
    snprintf(path, sizeof(path), "./textures/start%d.xpm", frame_number);

    int img_width, img_height;
    void *img = mlx_xpm_file_to_image(cub->data.mlx, path, &img_width, &img_height);
    if (!img)
    {
        printf("Failed to load large text image: %s\n", path);
        return;
    }

    int bpp, line_length, endian;
    unsigned int *src_pixels = (unsigned int *)mlx_get_data_addr(img, &bpp, &line_length, &endian);

    int win_x = WIDTH / 2 - img_width / 2;
    int win_y = HEIGHT - img_height - 30;

    unsigned int *dst_pixels = (unsigned int *)cub->data.img.addr;
    int dst_line_len = cub->data.img.line_length;

    for (int y = 0; y < img_height; y++)
    {
        for (int x = 0; x < img_width; x++)
        {
            unsigned int color = src_pixels[y * (line_length / 4) + x];
            if ((color & 0x00FFFFFF) != 0x000000)
            {
                int dst_x = win_x + x;
                int dst_y = win_y + y;
                if (dst_x >= 0 && dst_x < WIDTH && dst_y >= 0 && dst_y < HEIGHT)
                    dst_pixels[dst_y * (dst_line_len / 4) + dst_x] = color;
            }
        }
    }

    mlx_destroy_image(cub->data.mlx, img);

    mlx_put_image_to_window(cub->data.mlx, cub->data.win, cub->data.img.img, 0, 0);
}

void init_texture_background_anim(t_cub *cub)
{
    char background_paths[256];

    for (int i = 0; i < MAX_BACKGROUND_FRAMES; i++)
    {
        float progress = (float)(i + 1) / MAX_BACKGROUND_FRAMES;
        int text_frame = 1;
        if (progress >= 0.75f)
            text_frame = 4;
        else if (progress >= 0.5f)
            text_frame = 3;
        else if (progress >= 0.25f)
            text_frame = 2;

        put_large_text(cub, text_frame);

        snprintf(background_paths, sizeof(background_paths), "./textures/background/%d.xpm", i + 1);
        cub->background_textures[i].img = mlx_xpm_file_to_image(cub->data.mlx,
                                                                background_paths,
                                                                &cub->background_textures[i].width,
                                                                &cub->background_textures[i].height);

        if (!cub->background_textures[i].img)
        {
            ft_putendl_fd("Error loading background animation texture", 2);
            while (--i >= 0)
                mlx_destroy_image(cub->data.mlx, cub->background_textures[i].img);
            exit(EXIT_FAILURE);
        }

        int bg_x = WIDTH / 2 - cub->background_textures[i].width / 2;
        int bg_y = HEIGHT / 2 - cub->background_textures[i].height / 2;
        mlx_put_image_to_window(cub->data.mlx, cub->data.win,
                                cub->background_textures[i].img, bg_x, bg_y);
        char frame_text[52];
        snprintf(frame_text, sizeof(frame_text), "Loading %.0f %%", progress * 100.0f);
        mlx_string_put(cub->data.mlx, cub->data.win,
                       WIDTH / 2 - 50, HEIGHT - 30, 0X00FF00, frame_text);

        cub->background_textures[i].addr = mlx_get_data_addr(cub->background_textures[i].img,
                                                             &cub->background_textures[i].bits_per_pixel,
                                                             &cub->background_textures[i].line_length,
                                                             &cub->background_textures[i].endian);
    }
}

int init_textures_eye(t_cub *cub)
{
    const char *paths[MAX_EYE] = {
        "./textures/eye/1.xpm",
        "./textures/eye/2.xpm",
        "./textures/eye/3.xpm",
        "./textures/eye/4.xpm",
        "./textures/eye/5.xpm",
        "./textures/eye/6.xpm",
        "./textures/eye/7.xpm",
        "./textures/eye/8.xpm",
        "./textures/eye/9.xpm",
        "./textures/eye/10.xpm",
        "./textures/eye/11.xpm",
        "./textures/eye/12.xpm",
        "./textures/eye/13.xpm",
        "./textures/eye/14.xpm",
        "./textures/eye/15.xpm",
        "./textures/eye/16.xpm",
        "./textures/eye/17.xpm",
        "./textures/eye/18.xpm",
        "./textures/eye/19.xpm",
        "./textures/eye/20.xpm",
        "./textures/eye/21.xpm",
        "./textures/eye/22.xpm",
        "./textures/eye/23.xpm",
        "./textures/eye/24.xpm",
        "./textures/eye/25.xpm",
        "./textures/eye/26.xpm",
        "./textures/eye/27.xpm",
        "./textures/eye/28.xpm",
        "./textures/eye/29.xpm",
        "./textures/eye/30.xpm",
        "./textures/eye/31.xpm",
        "./textures/eye/32.xpm",
        "./textures/eye/33.xpm",
        "./textures/eye/34.xpm",
        "./textures/eye/35.xpm",
        "./textures/eye/36.xpm",
        "./textures/eye/37.xpm"};
    cub->eye_anim_frame = 0;
    cub->eye_anim_tick = 0;
    cub->eye_anim_speed = 0;
    cub->eye_pause_duration = 120 * 2;
    cub->eye_pause_timer = 0;

    cub->texture->eye = malloc(sizeof(t_img) * MAX_EYE);
    if (!cub->texture->eye)
    {
        ft_putendl_fd("Error\nMemory allocation failed for eye textures", 2);
        exit(1);
    }

    for (int f = 0; f < MAX_EYE; f++)
    {
        cub->texture->eye[f].img = mlx_xpm_file_to_image(
            cub->data.mlx,
            (char *)paths[f],
            &cub->texture->eye[f].width,
            &cub->texture->eye[f].height);

        if (!cub->texture->eye[f].img)
        {
            ft_putendl_fd("Error\nFailed to load eye texture", 2);
            exit(1);
        }

        cub->texture->eye[f].addr = mlx_get_data_addr(
            cub->texture->eye[f].img,
            &cub->texture->eye[f].bits_per_pixel,
            &cub->texture->eye[f].line_length,
            &cub->texture->eye[f].endian);
    }
    cub->eye_anim_speed = 0;
    cub->current_eye_index = 1;
    cub->eye_anim_frame = 1;
    cub->eye_anim_active = 1;
    cub->eye_anim_tick = 1;
    cub->eye_direction = -1;
    cub->is_cycling = 1;
    return 0;
}

#define MAX_ENEMY 65

int init_textures_enemy(t_cub *cub)
{
    const char *paths[MAX_ENEMY] = {
        "./textures/enemy_xa3la/1.xpm",
        "./textures/enemy_xa3la/2.xpm",
        "./textures/enemy_xa3la/3.xpm",
        "./textures/enemy_xa3la/4.xpm",
        "./textures/enemy_xa3la/5.xpm",
        "./textures/enemy_xa3la/6.xpm",
        "./textures/enemy_xa3la/7.xpm",
        "./textures/enemy_xa3la/8.xpm",
        "./textures/enemy_xa3la/9.xpm",
        "./textures/enemy_xa3la/10.xpm",
        "./textures/enemy_xa3la/11.xpm",
        "./textures/enemy_xa3la/12.xpm",
        "./textures/enemy_xa3la/13.xpm",
        "./textures/enemy_xa3la/14.xpm",
        "./textures/enemy_xa3la/15.xpm",
        "./textures/enemy_xa3la/16.xpm",
        "./textures/enemy_xa3la/17.xpm",
        "./textures/enemy_xa3la/18.xpm",
        "./textures/enemy_xa3la/19.xpm",
        "./textures/enemy_xa3la/20.xpm",
        "./textures/enemy_xa3la/21.xpm",
        "./textures/enemy_xa3la/22.xpm",
        "./textures/enemy_xa3la/23.xpm",
        "./textures/enemy_xa3la/24.xpm",
        "./textures/enemy_xa3la/25.xpm",
        "./textures/enemy_xa3la/26.xpm",
        "./textures/enemy_xa3la/27.xpm",
        "./textures/enemy_xa3la/28.xpm",
        "./textures/enemy_xa3la/29.xpm",
        "./textures/enemy_xa3la/30.xpm",
        "./textures/enemy_xa3la/31.xpm",
        "./textures/enemy_xa3la/32.xpm",
        "./textures/enemy_xa3la/33.xpm",
        "./textures/enemy_xa3la/34.xpm",
        "./textures/enemy_xa3la/35.xpm",
        "./textures/enemy_xa3la/36.xpm",
        "./textures/enemy_xa3la/37.xpm",
        "./textures/enemy_xa3la/38.xpm",
        "./textures/enemy_xa3la/39.xpm",
        "./textures/enemy_xa3la/40.xpm",
        "./textures/enemy_xa3la/41.xpm",
        "./textures/enemy_xa3la/42.xpm",
        "./textures/enemy_xa3la/43.xpm",
        "./textures/enemy_xa3la/44.xpm",
        "./textures/enemy_xa3la/45.xpm",
        "./textures/enemy_xa3la/46.xpm",
        "./textures/enemy_xa3la/47.xpm",
        "./textures/enemy_xa3la/48.xpm",
        "./textures/enemy_xa3la/49.xpm",
        "./textures/enemy_xa3la/50.xpm",
        "./textures/enemy_xa3la/51.xpm",
        "./textures/enemy_xa3la/52.xpm",
        "./textures/enemy_xa3la/53.xpm",
        "./textures/enemy_xa3la/54.xpm",
        "./textures/enemy_xa3la/55.xpm",
        "./textures/enemy_xa3la/56.xpm",
        "./textures/enemy_xa3la/57.xpm",
        "./textures/enemy_xa3la/58.xpm",
        "./textures/enemy_xa3la/59.xpm",
        "./textures/enemy_xa3la/60.xpm",
        "./textures/enemy_xa3la/61.xpm",
        "./textures/enemy_xa3la/62.xpm",
        "./textures/enemy_xa3la/63.xpm",
        "./textures/enemy_xa3la/64.xpm",
        "./textures/enemy_xa3la/65.xpm",
    };

    cub->texture->enemy = malloc(sizeof(t_img) * MAX_ENEMY);
    if (!cub->texture->enemy)
    {
        ft_putendl_fd("Error\nMemory allocation failed for enemy textures", 2);
        exit(1);
    }

    for (int f = 0; f < MAX_ENEMY; f++)
    {
        cub->texture->enemy[f].img = mlx_xpm_file_to_image(
            cub->data.mlx,
            (char *)paths[f],
            &cub->texture->enemy[f].width,
            &cub->texture->enemy[f].height);

        if (!cub->texture->enemy[f].img)
        {
            ft_putendl_fd("Error\nFailed to load enemy texture", 2);
            exit(1);
        }

        cub->texture->enemy[f].addr = mlx_get_data_addr(
            cub->texture->enemy[f].img,
            &cub->texture->enemy[f].bits_per_pixel,
            &cub->texture->enemy[f].line_length,
            &cub->texture->enemy[f].endian);
    }
    cub->enemy_anim_frame = 0;
    cub->enemy_anim_tick = 0;
    cub->enemy_anim_speed = 0;

    return 0;
}

void init_enemies_position(t_cub *cub)
{
    int enemy_index = 0;
    cub->enemy_count = 0;
    int y = 0;
    while (cub->data.map.map[y] && y < HEIGHT)
    {
        int x = 0;
        while (cub->data.map.map[y][x] && x < WIDTH)
        {
            if (cub->data.map.map[y][x] == '3')
            {
                if (enemy_index < MAX_ENEMY)
                {
                    cub->enemies[enemy_index].x = x * BLOCK + BLOCK / 2;
                    cub->enemies[enemy_index].y = y * BLOCK + BLOCK / 2;
                    printf("x: %f\n", cub->enemies[enemy_index].x);
                    printf("y: %f\n", cub->enemies[enemy_index].y);
                    cub->enemies[enemy_index].alive = 1;
                    cub->enemies[enemy_index].dist = 0;
                    cub->enemies[enemy_index].sprite_x = 0;
                    enemy_index++;
                    cub->enemy_count++;
                    cub->data.map.map[y][x] = '0';
                }
            }
            x++;
        }
        y++;
    }
    printf("Initialized %d enemies from map positions\n", cub->enemy_count);
}

int init_window(t_cub *cub)
{
    cub->data.mlx = mlx_init();
    if (!cub->data.mlx)
        return (ft_putendl_fd("Error\nFail to create connection", 2), 1);
    cub->data.win = mlx_new_window(cub->data.mlx, WIDTH, HEIGHT, "Cub3d");
    if (!cub->data.win)
        return (ft_putendl_fd("Error\nFail to open window", 2), 1);
    cub->background_anim_frame = 0;
    cub->background_anim_tick = 0;

    init_player(&cub->player, cub);
    if (init_image(cub))
        return 1;
    init_textures_weapon(cub);
    init_textures_eye(cub);
    init_texture_wall(cub);
    init_texture_door(cub);
    init_texture_floor(cub);
    init_texture_door_anim(cub);
    init_texture_background_anim(cub);
    init_textures_enemy(cub);
    init_enemies_position(cub);
    if (event_hook_window(cub))
        return (1);
    return (0);
}
