/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaajagro <yaajagro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:17:09 by yaajagro          #+#    #+#             */
/*   Updated: 2025/06/18 22:58:58 by yaajagro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/time.h>
# include <time.h>
# include <math.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include "../lib/.mlx/mlx.h"
# include "../lib/libft/libft.h"
# include "../lib/gnl/get_next_line.h"
# include "../lib/malloc/ft_malloc.h"

# define COLOR_RESET "\x1b[0m"
# define COLOR_YELLOW "\x1b[33m"
# define COLOR_GREEN "\x1b[32m"
# define COLOR_CYAN "\x1b[36m"
# define COLOR_RED "\x1b[31m"
# define DOOR_COLOR 0xF88379
# define SKY_BOTTOM 0x87CEEB
# define FLOOR_TOP 0x696969
# define FLOOR_BOTTOM 0x36454F
# define WIDTH 1800
# define HEIGHT 720
# define BLOCK 1000
# define MINIMAP_WIDTH 200
# define MINIMAP_HEIGHT 200

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307

# define PI 3.14159265359
# define WALL_COLOR 0x000000
# define PLAYER_COLOR 0x00FF00
# define BLOCK_SIZE 10
# define PLAYER_SIZE 3

typedef struct s_map
{
	char	**map;
	int		width;
	int		height;
}	t_map;

typedef struct s_lines
{
	char			*val;
	struct s_lines	*next;
}	t_lines;

typedef struct s_img
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_texture
{
	int		no;
	int		so;
	int		we;
	int		ea;
	int		fn;
	int		cn;
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	char	*floor_clr;
	char	*sky_clr;
	int		floor_grb[3];
	int		sky_grb[3];
	t_img	*weapon;
	t_img	no_img;
	t_img	so_img;
	t_img	we_img;
	t_img	ea_img;
	t_img	door_img;
}	t_texture;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_map		map;
	t_lines		*lines;
}	t_data;

typedef struct s_player
{
	float	x;
	float	y;
	float	angle;
	bool	key_up;
	bool	key_down;
	bool	key_left;
	bool	key_right;
	bool	left_rotate;
	bool	right_rotate;
}	t_player;

typedef struct s_enemy
{
	float	x;
	float	y;
	int		alive;
	int		anim_frame;
	int		anim_tick;
	float	distance;
	int		is_alive;
	float	dist;
	int		sprite_x;
	int		frame;
}	t_enemy;

typedef struct s_minimap
{
	int	offset_x;
	int	offset_y;
	int	center_x;
	int	center_y;
	int	radius;
}	t_minimap;

typedef struct s_cub
{
	t_minimap	minimap;
	t_data		data;
	t_player	player;
	t_texture	*texture;
	t_img		weapon[1][3];
	int			current_weapon_index;
	int			weapon_anim_frame;
	int			weapon_anim_speed;
	int			weapon_anim_tick;
	int			door_x;
	int			door_y;
	int			color;
}	t_cub;

typedef struct s_draw_info
{
	t_img	*tex;
	float	wall_height;
	float	wall_hit;
	float	step;
	float	tex_pos;
	int		start_y;
	int		end_y;
	int		tex_x;
}	t_draw_info;

typedef struct s_ray_data
{
	float	ray_dx;
	float	ray_dy;
	float	ray_x;
	float	ray_y;
	int		side;
}	t_ray_data;

typedef struct s_ray_params
{
	float	ray_dir_x;
	float	ray_dir_y;
	int		map_x;
	int		map_y;
	float	side_dist_x;
	float	side_dist_y;
	float	delta_dist_x;
	float	delta_dist_y;
	int		step_x;
	int		step_y;
	int		side;
	float	pos_x;
	float	pos_y;
	char	hit_tile;
}	t_ray_params;

int		map_parsing(int ac, char **av, t_cub *cub);
int		init_map(t_cub *cub, char *filename);
char	*read_map(int fd);
int		check_file_extention(char *str);
t_lines	*new_line(char *val);
int		check_map(t_cub *cub);
void	ft_add_line(t_lines **head, t_lines *new);
int		valid_chars(char c);
int		only_walls(char *line);
int		parse_lines(t_cub *cub);
t_lines	*textures_extracter(t_lines *line, t_texture *textur);
int		get_map_len(t_lines *line);
t_lines	*map_extracter(t_lines *line, char ***map);
int		extractor(t_cub *cub);
int		check_file_ext(char *name);
int		check_file(char *filename);
int		check_texture(t_cub *cub);
int		check_comas(char *clr1, char *clr2);
void	reset_texture(t_texture *textur);
int		init_window(t_cub *cub);
int		event_hook_window(t_cub *cub);
int		init_image(t_cub *cub);
int		key_release(int key, t_cub *cub);
int		key_press(int key, t_cub *cub);
int		close_window(t_cub *cub);
void	handle_movement(t_cub *cub);
bool	touch_one(float px, float py, t_cub *cub);
float	use_distance(float x, float y);
float	use_fixed_dist(float x2, float y2, t_cub *game);
void	my_pixel_put(int x, int y, t_img *img, int color);
void	clear_image(t_cub *cub);
void	render_draw_square(int x, int y, int size, t_cub *cub);
void	render_draw_minimap(t_cub *cub);
int		game_loop(t_cub *cub);
int		mouse_move(int x, int y, t_cub *cub);
void	try_open_door(t_cub *cub);
void	my_pixel_put_img(t_img *img, int x, int y, int color);
void	draw_split_background(t_cub *cub);
void	draw_weapon(t_cub *cub);
int		init_textures_weapon(t_cub *cub);
void	init_weapon_animation_params(t_cub *cub);
void	init_texture_wall(t_cub *cub);
void	draw_door(t_cub *cub, int screen_x, t_ray_data *ray, float dist);
void	draw_wall(t_cub *cub, int screen_x, t_ray_data *ray, float dist);
void	init_ray_params(t_ray_params *params, t_cub *cub, float ray_angle);
void	draw_minimap_walls(t_cub *cub, int center_x, int center_y, int radius);
void	draw_minimap_doors(t_cub *cub, int center_x, int center_y, int radius);
void	draw_minimap_player(t_cub *cub, int center_x, int center_y);
void	init_minimap_values(t_cub *cub);
void	draw_border_pixel(t_cub *cub, int x, int y, int radius);
int		calculate_distance_sq(int x, int y, int center_x, int center_y);
int		get_map_height(char **map);
int		check_chars(char *s);
int		add_texture(char *path, t_texture *tex, int flg);
int		palyer_chars(char c);
int		get_len(char **s);
int		xe_cond(int c);
void	check_rendring_depend(t_cub *cub);
void	destroy_imgs_exit(t_cub *cub, char *msg);
void	remove_spaces(t_lines *lines);

#endif
