/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzblah <mehdi.zblah@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 12:35:59 by mzblah            #+#    #+#             */
/*   Updated: 2021/05/30 22:30:04 by mzblah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/*
**	INCLUDES
*/

# include <mlx.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include "libft.h"
# include "get_next_line.h"

/*
**	DEFINES
*/

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 128
# endif

# define MLX_IMG_NBR 2
# define NBR_TEXTURE 4
# define NBR_TEX_BNS 8

# define EXTENSION ".cub"
# define EXTENSION_LENGTH 4
# define ERR_FILE_PATH "./srcs/exit_management/code_error"
# define MSG_FAIL_OPEN_READ "Erreur ouverture/lecture fichier code erreur\n"

# define STR_VALID_BONUS "012345NSEW "
# define STR_SPR "2345"
# define STR_NO_SPR "01NSEW "

# define KEY_W 119
# define KEY_S 115
# define KEY_A 97
# define KEY_D 100
# define ARROW_LEFT 65361
# define ARROW_RIGHT 65363

# define ROT_SPEED 0.0396
# define MOV_SPEED 0.03

# define MIN_STEP 0.0000000000001
# define MAX_INT 2147483647

/*
**	STRUCTS
*/

typedef struct s_str_list
{
	char				*str;
	struct s_str_list	*next;
}				t_l_str;

typedef struct s_minlibx
{
	void	*mlx_ptr;
	void	*mlx_win;
}				t_mlx;

typedef struct s_img_mlx
{
	void			*img;
	char			*addr;
	unsigned int	***img_tab;
	int				x;
	int				y;
	int				bpp;
	int				bpp_8;
	int				line_len;
	int				endian;
}				t_img;

typedef struct s_sprite
{
	char				type;
	int					x;
	int					y;
	double				dist;
	double				pos_cam_x;
	double				pos_cam_y;
	double				transform_x;
	double				transform_y;
	int					spr_screen_x;
	int					spr_height;
	int					draw_start_x;
	int					draw_end_x;
	int					draw_start_y;
	int					draw_end_y;
	int					spr_width;
	int					tex_x;
	int					tex_y;
	int					ix;
	int					iy;
}				t_spr;

typedef struct s_raycasting
{
	double				posx;
	double				posy;
	double				dirx;
	double				diry;
	double				planex;
	double				planey;
	double				time;
	double				old_time;
	int					x;
	double				camerax;
	double				raydirx;
	double				raydiry;
	int					mapx;
	int					mapy;
	double				sidedistx;
	double				sidedisty;
	double				deltadistx;
	double				deltadisty;
	double				perp_w_d;
	int					stepx;
	int					stepy;
	int					hit;
	int					side;
	int					lineheight;
	int					drawstart;
	int					drawend;
	int					tex_idx;
	double				spr_inv_det;
	double				wall_x;
	int					tex_x;
	int					tex_y;
	double				step;
	double				step_sum;
}				t_ray;

typedef struct s_minimap
{
	t_img			*img;
	int				draw_x_start;
	int				draw_y_start;
	int				draw_x_end;
	int				draw_y_end;
	int				width;
	int				height;
	int				square_width;
	int				square_height;
	int				map_draw_x_start;
	int				map_draw_y_start;
	int				map_draw_x_end;
	int				map_draw_y_end;
}				t_mm;

# define S_SNIPE "./textures/intervention_mw2.xpm"
# define S_NEIN "./textures/nein.xpm"
# define S_HEART "./textures/heart.xpm"
# define S_BARREL "./textures/tonneau.xpm"

# define NB_HUD_TEX 5
# define S_BAR "./textures/minecraft/barre_uniforme.xpm"
# define S_FULL "./textures/minecraft/coeur_plein.xpm"
# define S_HALF "./textures/minecraft/coeur_moitie.xpm"
# define S_VOID "./textures/minecraft/coeur_vide.xpm"
# define ADR_I_SNIPE "./textures/icon_intervention_mw2.xpm"
# define MC_BAR 0
# define HP_FULL 1
# define HP_HALF 2
# define HP_VOID 3
# define ICN_SNIPE 4

# define NB_WEAPONS 1
# define W_SNIPE 0
# define H_SNIPE 1
# define ADR_W_SNIPE "./textures/intervention_hand_mw2.xpm"
# define ADR_H_SNIPE "./textures/intervention_shot_hand_mw2.xpm"

typedef struct s_heads_up_display
{
	t_img			**hud_tex;
	t_img			**weapons_tex;
	t_img			*hud_img;
	int				*items;
	int				item_select;
	int				old_hp;
	int				shoot_key;
	int				firing;
	unsigned long	ms_shoot_start;
}				t_hud;

typedef struct s_cub3d_info
{
	unsigned long		ms_life;
	unsigned long		ms_life_diff;
	unsigned long		ms_start;
	unsigned long		ms_diff;
	int					hp;
	int					save;
	t_hud				*hud;
	t_mm				*mm;
	t_ray				*s_ray;
	t_img				**img;
	t_img				**img_textures;
	int					idx_img;
	int					is_mov_forward;
	int					is_mov_backward;
	int					is_mov_left;
	int					is_mov_right;
	int					is_rot_left;
	int					is_rot_right;
	char				**map;
	size_t				map_width;
	size_t				map_height;
	size_t				pos_x;
	size_t				pos_y;
	char				pos_direction;
	int					res_width;
	int					res_height;
	char				*n_t;
	char				*s_t;
	char				*w_t;
	char				*e_t;
	char				*sprite_t;
	int					nb_spr;
	int					nb_spr_final;
	t_spr				**spr_tab;
	int					floor_rgb;
	int					ceil_rgb;
	int					is_res_set;
	int					is_f_rgb_set;
	int					is_c_rgb_set;
	t_l_str				*map_str;
	t_mlx				*mlx;
	double				*dist_buffer;
}				t_c3d;

/*
**	PROTOTYPES
*/

/*
** srcs/cub3d.c
*/

int				t(int c, int a, int b);
int				a(int *a, int b, int c, int d);
char			*ac(void **a, void *b);
double			d(int c, double a, double b);

/*
** srcs/cub3d_parse_cub.c
*/

int				ft_parse_cub(t_c3d **cub, char *cub_pat, char *argv2);

/*
** srcs/cub3d_parse_cub_color_res.c
*/

int				ft_set_color_and_resolution(t_c3d *cub, char *str);

/*
** srcs/cub3d_parse_map.c
*/

int				ft_parse_map(t_c3d *cub, int fd, char **first_str);

/*
** srcs/cub3d_read_map.c
*/

int				ft_read_map(t_c3d *cub, int fd, char ***f_str);
int				ft_stock_sprites(t_c3d *cub);
int				skip_spaces_comma(char *str, int *idx);

/*
** srcs/game/game_init.c
*/

int				game_init(t_c3d *cub);

/*
** srcs/game/game_raycasting.c
*/

int				ft_init_s_ray(t_c3d *cub);
void			ft_raycasting_loop(t_c3d *cub, t_ray *s_ray);
void			init_delta(t_ray *s_r, double ray_dirx_2, double ray_diry_2);

/*
** srcs/game/game_move.c
*/

void			rotate_view(t_c3d *cub, t_ray *s_ray, double opx, double odx);
void			move_forward_backward(t_c3d *cub, t_ray *s_r);
void			move_left_right(t_c3d *cub, t_ray *s_r);
int				key_press(int key_event, t_c3d *cub);
int				key_release(int key_event, t_c3d *cub);

/*
** srcs/game/game_texture_pixels.c
*/

void			pixels_color(t_c3d *cub, t_ray *s_ray);

/*
** srcs/game/game_init_img_textures.c
*/

int				ft_mlx_img_init(t_c3d *cub);
int				ft_load_textures(t_c3d *cub, t_img *tmp, char *file_addr);
int				ft_init_textures_normal(t_c3d *cub);
int				ft_init_sprite_tab(t_c3d *cub, t_ray *s_r);
int				ft_init_img(t_c3d *cub, t_img *img);

/*
** srcs/game/game_raycasting_sprite.c
*/

void			ft_draw_sprite(t_c3d *cub, t_ray *s_r, double *zbuffer);
void			ft_delete_sprite(t_c3d *cub, int x, int y);

/*
** srcs/exit_management/cub3d_exit_management.c
*/

int				ft_exit(t_c3d *cub, int state);
int				ft_exit_cub3d(t_c3d *cub, int state);

/*
** srcs/exit_management/cub3d_error_message.c
*/

int				ft_error_message(int state, int fd, int gnl);
int				ft_exit_inutile(t_c3d *cub);
int				ft_keep_reading_gnl(int fd, char **s);

/*
** BONUS
*/

void			free_t_image_b(void *mlx_ptr, t_img *img);
int				ft_init_textures(t_c3d *cub, int idx);
int				ft_init_mm(t_c3d *cub);
int				ft_draw_minimap(t_c3d *cub);
int				ft_hud(t_c3d *cub);
void			free_bonus(t_c3d *cub);
int				ft_init_hud_textures(t_c3d *cub);
int				ft_init_hud_img(t_c3d *cub);
int				ft_init_weapons_textures(t_c3d *cub);
void			ft_draw_weapon(t_c3d *cub, t_hud *hud, int x, int y);
void			ft_shot_sprite(t_c3d *cub, t_ray *s_ray);
void			ft_fire(t_c3d *cub, t_hud *hud);

#endif
