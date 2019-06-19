/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 05:06:40 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/06/14 19:00:54 by mikorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_H
# define EDITOR_H

# include "../includes/common.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/mman.h>
# include <stdint.h>
# include <fcntl.h>
# include <dirent.h>
# include "bmp_reader.h"
# include "font.h"

# define W 1600
# define H 1200
# define GRIDSIZE 64
# define TEXTURE_PATH "./textures/"
# define POSTERS_PATH "./textures/posters/"

/*
**	Assets paths
*/

# define PATH_GROUNDSPRITES "./textures/assets/groundsprites/"
# define PATH_MONSTERS "./textures/assets/monsters/"
# define PATH_WEAPONS "./textures/assets/weapons/"

# define PATH_AMMO_ED "./textures/assets/editor/ammo_healpack/"
# define PATH_MONSTER_ED "./textures/assets/editor/monsters/"
# define PATH_HEALPACK_ED "./textures/assets/editor/ground_assets/"
# define PATH_PLAYERSTART_ED "./textures/assets/editor/playerstart/"

# define PATH_MAP "./maps/"
# define MAP_PROMPT_X (W >> 2)
# define MAP_PROMPT_Y (H >> 1) - 125
# define MAP_PROMPT_ENDX MAP_PROMPT_X + 575
# define MAP_PROMPT_ENDY (H >> 1) + 125

/*
**	ed_interface_*.c
*/

# define MARGIN 6
# define PROPERTIES_LIMIT 350
# define TEXTURE_TOOLBAR 618
# define NB_PROPERTIES 19
# define PROPERTIES_POS (H >> 1) - 20
# define MOVE_WALL_PROP 30

/*
**	Number of assets print per line on the interface toolbar
*/

# define NB_ASSET_LINE (int)((PROPERTIES_LIMIT - 62) / 32)

/*
**	########### ed_init_assets.c ###########
*/

typedef struct	s_monsters_texture
{
	char		*name;
	int			nb_walk_anim;
	int			nb_walk_orientation;
	SDL_Surface	**walk;
	int			nb_attack_anim;
	int			nb_attack_orientation;
	SDL_Surface	**attack;
	int			nb_death_anim;
	SDL_Surface	**death;
}				t_monsters_texture;

/*
**	Numbers of asserts for each category is contains in (nb_asset[4])
**	cf.struct s_interface
*/

typedef struct	s_assets_data
{
	char	file[100];
	int		used;
	char	name[50];
}				t_assets_data;

/*
**	#######################################
*/

typedef struct	s_map_list
{
	char				*name;
	struct s_map_list	*begin;
	struct s_map_list	*prev;
	struct s_map_list	*next;
}				t_map_list;

typedef struct	s_monster_list
{
	char					*name;
	t_vec2f					pos;
	int						sectnunm;
	int						category;
	int						selected_asset;
	int						is_highlighted;
	int						is_select;
	struct s_monster_list	*begin;
	struct s_monster_list	*prev;
	struct s_monster_list	*next;
}				t_monster_list;

typedef struct	s_assets
{
	SDL_Surface	*assets[100];
}				t_assets;

typedef struct	s_toolbar
{
	SDL_Surface	*select[2];
	SDL_Surface	*move[2];
	SDL_Surface	*properties[NB_PROPERTIES];
	t_assets	assets[3];
	SDL_Surface	*player_start;
}				t_toolbar;

/*
**	int	nb_asset[4] : 	[0] = ammo/healpack, [1] = monster,
**						[2] = ,	[3] = playerstart
*/

typedef struct	s_interface
{
	SDL_Surface		*menu;
	t_toolbar		toolbar;
	int				separate_sector;
	int				show_menu;
	int				is_on_menu;
	int				select;
	int				move;
	int				btn_right_pressed;
	int				texture_case_select;
	int				category;
	int16_t			nb_asset[4];
	t_vec2f			category_pos[4];
	int				selected_asset;
	int				selected_asset_cat;
	t_vec2f			selected_asset_position;
	t_monster_list	*monster_list;
	t_vec2f			mouse_pos;
	t_vec2f			tex_select[4];
	t_vec2			btn_floor_height_pos;
	t_vec2			btn_ceil_height_pos;
	t_vec2			cbox_door_p;
	t_vec2			cbox_skybox_p;
	t_vec2			cbox_end_p;
	t_vec2			box_nex_map_p;
	t_map_list		*map_list;
	t_map_list		**map_list_sort;
	int				nb_map;
	int				map_list_start_i;
	int				prompt_map_open;
	int				map_folder_empty;
	int				selected_map;
	t_vec2			selected_map_pos;
}				t_interface;

/*
**	texture_to_scale = size to resize the image,
**	texture_to_scale = 32 -> will resize the image to 32x32 pixels
**	hl_wall = highlighted_wall
**
**	t_assets_data	assets_data[100]; index given by nb_asset (cf. s_interface)
*/

# define MAX_ASSETS 100

typedef struct	s_data
{
	SDL_Window			*win;
	SDL_Surface			*screen;
	SDL_Surface			**textures;
	int					nb_texture;
	SDL_Surface			**posters;
	int32_t				nb_posters;
	t_texture_data		*texture_list;
	t_texture_data		*posters_list;
	char				*path;
	t_monsters_texture	*texture_monster;
	SDL_Surface			*weap_tex[3][20];
	SDL_Surface			*weap_proj[3][20];
	char				*weap_list[3][2][20];
	t_interface			interface;
	t_assets_data		assets_data[MAX_ASSETS];
	t_vec3f				player_start;
	int16_t				startsectnum;
	char				next_map[100];
	int					get_next_map;
	t_vec2f				pos;
	char				*map_to_open;
	char				current_loaded_map[100];
	char				*path_to_save;
	t_sector			sectors[MAXNUMSECTORS];
	t_wall				walls[MAXNUMWALLS];
	t_monster			*monsters;
	int16_t				numsectors;
	int16_t				numwalls;
	uint16_t			nbmonsters;
	int32_t				nb_used_texture;
	int					nb_anim_tmp;
	int					nb_orientation_tnp;
	double				scale;
	int					default_texture;
	int					default_wall_texture;
	int					default_floor_texture;
	int					default_ceil_texture;
	t_wall				*selectedwall;
	t_wall				*selectedwall2;
	int					selected_sector;
	int					selected_wall;
	int					selected_texture;
	bool				grid_locking;
	bool				sectordrawing;
	double				texture_to_scale;
	t_vec2f				mouse;
	t_wall				*hl_wall;
	int					hl_wallnum;
	int					hl_wallnum_draw;
	unsigned char		font[96][CHAR_WIDTH];
}				t_data;

/**/int			bmp_reader(t_data *d);
int			init_texture_test(t_data *d, int n);


void			debug_print(t_data *d);

/*
**	ed_init.c
*/

int				init_editor(t_data *d);

/*
**	ed_init_structures.c
*/

void			init_data(t_data *d);
void			init_sectors(t_data *d);

/*
**	ed_init_texture.c
*/

int				init_texture(t_data *d, int n);

/*
**	ed_init_assets.c
*/

int				is_bmp(struct dirent *de);
int				get_interface_assets_files(t_data *d, char **path);

/*
**	ed_get_monsters_files.c
*/

int				get_monsters_files(t_data *d, char *path, int nb_monster);

/*
**	ed_get_animation_files.c
*/

char			**load_animation_list(t_data *d, char *path);

/*
**	ed_get_weapons_list.c
*/

int				get_weapons_list(t_data *d, char **weap_name, int *nb_tex,
													int *nb_pro);

/*
**	ed_draw.c
*/

void			draw_screen(t_data *d);

/*
**	ed_draw_assets.c
*/

void			draw_assets_to_map(t_data *d, t_assets *a);

/*
**	ed_conversion.c
*/

t_vec2f			worldtoscreen(t_data *d, t_vec2f p);
t_vec2f			screentoworld(t_data *d, t_vec2f p);
double			vec2f_length(t_vec2f v);
t_vec2f			add_vec2f(t_vec2f v1, t_vec2f v2);

/*
**	pixel.c
*/

void			put_pixel_to_surface(SDL_Surface *sur, int x, int y,
														uint32_t color);
void			putpixel(t_data *d, int x, int y, uint32_t color);

/*
**	ed_editor.c
*/

void			ceil_height(t_data *d, double val, int16_t sectnum);
void			floor_height(t_data *d, double val, int16_t sectnum);
void			cancel_last_wall(t_data *d);
int16_t			in_which_sector_is_this_wall(t_data *d, t_wall *w);
void			update_pos(t_data *d, SDL_Event *e);

/*
**	ed_editor_functions.c
*/

bool			same_pos(t_wall *w0, t_wall *w1);
void			detect_neighbors(t_data *d, int16_t sectnum);

/*
**	ed_editor_sector.c
*/

void			add_sector(t_data *d);
void			del_sector(t_data *d, int16_t sectnum, t_sector *sect);
int16_t			find_sect_under_cursor(t_data *d);

/*
**	ed_editor_wall.c
*/

void			add_wall(t_data *d);
void			select_wall_under_cursor(t_data *d, t_vec2f p);
void			update_wall_pos(t_data *d);

/*
**	ed_editor_assets_handler.c
*/

int				select_assets_on_map(t_data *d);
void			draw_selection_arround_selected_asset(t_data *d, t_vec2f *v,
																	int c);
void			draw_selection_arround_asset(t_data *d, t_vec2f *category);
void			get_selected_asset(t_data *d);
int				add_asset_to_map(t_data *d, int x, int y);

/*
**	ed_interface.c
*/

void			print_interface(t_data *d);

/*
**	ed_interface_functions.c
*/

t_vec2f			grid_lock(t_data *d, t_vec2f p);
int				is_on_select_move_icon(t_data *d, int x, int y);
int				check_if_mouse_on_menu(t_data *d, int x, int y);
void			btn_height(t_data *d, int x, int y, t_interface *i);
void			is_on_checkbox(t_data *d, int x, int y, SDL_Event *e);

/*
**	ed_interface_properties.c
*/

void			print_properties(t_data *d, SDL_Surface **properties);

/*
**	ed_interface_properties2.c
*/

void			draw_separator(t_data *d, int x, int y, int color);
void			fill_texture_selection(t_data *d, t_interface *i, int wallnum,
																	int tex_n);
void			show_preview(t_data *d, t_assets *a);
void			draw_ligth_bar(t_data *d);

/*
**	ed_interface_print_values.c
*/

void			print_interface_values(t_data *d, int x, int y);

/*
**	ed_interface_map_list.c
*/

int				get_map_list(t_data *d);

/*
**	ed_interface_select_map.c
*/

void			draw_map_list(t_data *d);
void			detect_selected_map(t_data *d, int x, int y);
char			*get_map_to_open(t_data *d, SDL_Event *e);
void			get_next_level(t_data *d, SDL_Event *e);

/*
**	ed_utils.c
*/

void			copy_surface_to_surface(SDL_Surface *src,
								SDL_Surface *dest, int p[2], t_data *d);
void			remove_backgorund_image(SDL_Surface *s);
double			fclamp(double x, double min, double max);

/*
**	ed_event.c
*/

void			run_game(t_data *d);
void			mouse_wheel(t_data *d, SDL_Event *e);
void			event_motion_mouse(t_data *d, SDL_Event *e);

/*
**	ed_event_keyboard.c
*/

void			event_key_up(t_data *d, SDL_Keycode key);
void			event_key_down(t_data *d, SDL_Keycode key);

/*
**	ed_event_functions.c
*/

int				menu_open_button(t_data *d, SDL_Event *e);
int				menu_save_button(t_data *d, SDL_Event *e);
int				menu_exit_button(t_data *d, SDL_Event *e);
int				properties_texture_selection(t_data *d, SDL_Event *e);
int				selecting_assets(t_data *d, SDL_Event *e);

/*
**	ed_event_functions2.c
*/

void			fix_default_texture(t_data *d, int x, int y);
void			save_selected_texture(t_data *d, int x, int y, int wallnum);

/*
**	ed_event_mouse_button.c
*/

int				event_mouse_button(t_data *d, SDL_Event *e);

/*
**	ed_read_map.c
*/

int				contain_map_path(char *path);
int				load_map(t_data *d, char *path);

/*
**	ed_save_file.c
*/

int				save_file(t_data *d, char *map_name);

/*
**	ed_fix_data_to_save.c
*/

void			set_texture_name(t_data *d, t_sector *s, t_wall *w);
void			set_texture_used(t_data *d, t_sector *s, t_wall *w);
void			set_assets_used(t_data *d);

/*
**	ed_save_assets.c
*/

int				write_monster_data(t_data *d, int f);
int				write_monster_texture(t_data *d, int f, t_monsters_texture *mt);

/*
**	ed_save_weapons_texture.c
*/

int				write_weapons_texture(t_data *d, int f);

/*
**	ed_save_posters.c
*/

int				write_posters_data(t_data *d, int f);

/*
** ed_door_toggle.c
*/

void			toggle_isdoor(t_data *d);

/*
** ed_detect_assets.c
*/

void			detect_assets(t_data *d, int x, int y);

/*
** ed_detect_wall.c
*/

void			detect_wall(t_data *d, int x, int y);
void			detect_select_wall(t_data *d, int x, int y);
double			fclamp(double x, double min, double max);

/*
**	ed_monster_list_manager.c
*/

int				add_monster_to_list(t_data *d, t_vec2f *xy, int sectn,
															t_interface *i);
int				delete_monster(t_data *d, t_monster_list *lst);

/*
**	ed_font.c
*/

void			init_font(t_data *d);
void			draw_string(t_data *d, t_font f);

/*
**	ed_write_sound.c
*/

int		write_sound(t_data *d, int f);

#endif
