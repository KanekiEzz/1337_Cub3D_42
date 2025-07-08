/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iezzam <iezzam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:17:09 by yaajagro          #+#    #+#             */
/*   Updated: 2025/05/30 14:13:49 by iezzam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>
#include <X11/keysym.h>
#include <X11/X.h>
#include "../lib/.mlx/mlx.h"
#include "../lib/libft/libft.h"
#include "../lib/gnl/get_next_line.h"
#include "../lib/malloc/ft_malloc.h"

#define COLOR_RESET "\x1b[0m"
#define COLOR_YELLOW "\x1b[33m"
#define COLOR_GREEN "\x1b[32m"
#define COLOR_CYAN "\x1b[36m"
#define COLOR_RED "\x1b[31m"
#define DOOR_COLOR 0xF88379

#define SKY_BOTTOM 0x87CEEB
#define FLOOR_TOP 0x696969
#define FLOOR_BOTTOM 0x36454F

#define WIDTH 1200
#define HEIGHT 720
#define BLOCK 1000
#define MINIMAP_WIDTH 200
#define MINIMAP_HEIGHT 200

#define W 119
#define A 97
#define S 115
#define D 100
#define LEFT 65361
#define RIGHT 65363

// For X11/Linux:
#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
#define KEY_UP 65362
#define KEY_DOWN 65364
#define KEY_LEFT 65361
#define KEY_RIGHT 65363
#define KEY_ESC 65307

#define PI 3.14159265359

/* ================== MINIMAP COLORS ================== */
#define WALL_COLOR 0x000000
#define PLAYER_COLOR 0x00FF00
#define RAY_COLOR 0xF7FF00
#define EMPTY_SPACE 0x1A1A2E

/* ================== 3D VIEW COLORS ================== */
#define SKY_COLOR 0x87CEEB
#define FLOOR_COLOR 0x36454F
#define WALL_TOP_COLOR 0x6B8E23
#define WALL_BOTTOM_COLOR 0x98FB98

#define MAP_WIDTH 40
#define MAP_HEIGHT 40
#define BLOCK_SIZE 10
#define PLAYER_SIZE 5
#define ENEMY_RADIUS (BLOCK * 0.3f)
#define FOV (PI / 3)  // 60 degrees


typedef struct s_ray_hit {
    float dist;
    int type;       // 1=wall, 2=door, 3=enemy
    int side;       // for walls/doors (0=NS, 1=EW)
    int enemy_id;    // for enemies
    float hit_x;
    float hit_y;
    float ray_angle;
} t_ray_hit;

typedef struct s_map
{
	char **map;
	int width;
	int height;
} t_map;

typedef struct s_lines
{
	char *val;
	struct s_lines *next;
} t_lines;

typedef struct s_img
{
	void *mlx;
	void *win;
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
	int width;
	int height;
} t_img;

typedef struct s_texture
{
	int no;
	int so;
	int we;
	int ea;
	int fn;
	int cn;
	char *no_path;
	char *so_path;
	char *we_path;
	char *ea_path;
	char *floor_clr;
	char *sky_clr;
	int floor_grb[3];
	int sky_grb[3];
	t_img *weapon;
	t_img *eye;
	t_img *enemy;
	t_img no_img;
	t_img so_img;
	t_img we_img;
	t_img ea_img;
	t_img door_img;
	t_img floor_img;
} t_texture;

typedef struct s_data
{
	void *mlx;
	void *win;
	t_img img;
	t_map map;
	t_lines *lines;
} t_data;

typedef struct s_player
{
	float x;
	float y;
	float angle;
	bool key_up;
	bool key_down;
	bool key_left;
	bool key_right;
	bool left_rotate;
	bool right_rotate;
} t_player;

#define MAX_WEAPONS 3
#define MAX_ANIM_FRAMES 3
#define MAX_DOOR_FRAMES 6
#define MAX_BACKGROUND_FRAMES 57
#define MAX_EYE 37
#define MAX_ENEMY 65
typedef struct s_enemy
{
	float x;		// Enemy X position
	float y;		// Enemy Y position
	int alive;		// Is enemy alive (1) or dead (0)
	int anim_frame; // Current animation frame
	int anim_tick;	// Animation counter
	float distance; // Distance from player (for sorting)
	int is_alive;
	float dist;	  // Distance from player
	int sprite_x; // Screen position X
	int frame;
} t_enemy;

typedef struct s_cub
{
	t_enemy enemies[MAX_ENEMY];
	int num_enemies;
	int screen_h;
	int screen_w;
	t_data data;
	t_player player;
	t_texture *texture;
	t_img weapon[MAX_WEAPONS][MAX_ANIM_FRAMES];
	int eye_anim_speed;
	int current_eye_index;
	int eye_anim_frame;
	int eye_anim_active;
	int eye_anim_tick;
	int current_weapon_index;
	int weapon_anim_frame;
	int weapon_anim_speed;
	int weapon_anim_active;
	int weapon_anim_tick;
	int door_should_close;
	int door_anim_active;
	int door_anim_frame;
	int door_anim_tick;
	int is_moving;
	int door_x;
	int door_y;
	int door_opened;
	t_img door_textures[MAX_DOOR_FRAMES];
	t_img background_textures[MAX_BACKGROUND_FRAMES];
	int background_anim_frame;
	int background_anim_tick;
	int eye_closed_timer;
	int eye_open_timer;
	int eye_pause_timer;	// How long we've been paused
	int eye_pause_duration; // How long to pause between animations

	int enemy_anim_frame; // Start with enemy open
	int enemy_anim_tick;
	int enemy_pause_duration; // 1 second at 60FPS
	int enemy_pause_timer;
	int current_enemy_index;
	int enemy_anim_active;
	// t_enemy enemies[10];  // Array of enemies (adjust size as needed)
	int enemy_count;	  // Number of active enemies
	int enemy_anim_speed; // Animation speed for all enemies
	int door_anim_progress;
	    int eye_direction;  // initialize to -1
    int is_cycling;     // initialize to 1
} t_cub;

int map_parsing(int ac, char **av, t_cub *cub);
int init_map(t_cub *cub, char *filename);
char *read_map(int fd);
int check_file_extention(char *str);
t_lines *new_line(char *val);
int check_map(t_cub *cub);
void ft_add_line(t_lines **head, t_lines *new);
int valid_chars(char c);
int only_walls(char *line);
int parse_lines(t_cub *cub);
t_lines *textures_extracter(t_lines *line, t_texture *textur);
int get_map_len(t_lines *line);
t_lines *map_extracter(t_lines *line, char ***map);
int extractor(t_cub *cub);
int check_file_ext(char *name);
int check_file(char *filename);
int check_texture(t_cub *cub);
int check_comas(char *clr1, char *clr2);
void reset_texture(t_texture *textur);

int init_window(t_cub *cub);
int event_hook_window(t_cub *cub);
int init_image(t_cub *cub);
void initialize_player(t_player *player, t_cub *cub);
int key_release(int key, t_cub *cub);
int key_press(int key, t_cub *cub);
int close_window(t_cub *cub);
void handle_movement(t_cub *cub);
bool touch_one(float px, float py, t_cub *cub);
float use_distance(float x, float y);
float use_fixed_dist(float x1, float y1, float x2, float y2, t_cub *game);
float world_to_minimap_x(float x);
float world_to_minimap_y(float y);
void my_pixel_put(int x, int y, t_img *img, int color);
void clear_image(t_cub *cub);
void render_draw_square(int x, int y, int size, int color, t_cub *cub);
void render_draw_minimap(t_cub *cub);
// void cast_ray(t_cub *cub, float start_x, int i);
int game_loop(t_cub *cub);
int mouse_move(int x, int y, t_cub *cub);
int mouse_scroll(int button, int x, int y, t_cub *cub);

void try_open_door(t_cub *cub);
/*eye*/
void update_eye_animation(t_cub *cub);
void draw_eye(t_cub *cub);
/*graphics*/
void my_pixel_put_img(t_img *img, int x, int y, int color);
/*floor_sky*/
void draw_split_background(t_cub *cub);
/*weapon*/
void draw_weapon(t_cub *cub);
/*door*/
void update_door_animation(t_cub *cub);
void update_door_close(t_cub *cub);
/*enemy*/
void draw_enemy(t_cub *cub);
#endif