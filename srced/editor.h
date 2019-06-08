/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 05:06:40 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/06/06 19:57:07 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_H
# define EDITOR_H

# include "../includes/common.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <stdint.h>
# include <fcntl.h>
# include <dirent.h>
# include "bmp_reader.h"
# include <sys/mman.h>
# include <sys/stat.h>

# define W 1600
# define H 1200
# define MAXNUMSECTORS 1024
# define MAXNUMWALLS 8192
# define GRIDSIZE 64
# define TEXTURE_PATH "./textures"

/*
**	Assets paths
*/

# define PATH_GROUNDSPRITES "./textures/assets/groundsprites"
# define PATH_MONSTERS "./textures/assets/monsters"
# define PATH_WEAPONS "./textures/assets/weapons"

# define PATH_AMMO_ED "./textures/assets/editor/ammo"
# define PATH_MONSTER_ED "./textures/assets/editor/monsters"
# define PATH_HEALPACK_ED "./textures/assets/editor/healpack"
# define PATH_PLAYERSTART_ED "./textures/assets/editor/playerstart"

/*
**	ed_interface_*.c
*/

# define MARGIN 8
# define PROPERTIES_LIMIT 275
# define TEXTURE_TOOLBAR 550

/*
**	########### ed_init_assets.c ###########
*/

// need nb types of monsters  to write in the map

typedef struct	s_monsters_data
{
	char	*name;
	// nb_animations = number of folder inside the monster name folder
	// TODO count nb subfolder
	// max state = the number of bmp file inside each animation folder
	// TODO count nb bmp file
	// nb of state in each folder must be fthe same;
	// TODO store everything here
	// how to store death folder ?
}				t_mosters_data;

/*
**	Numbers of asserts for each category is contains in (nb_asset[4])
**	cf.struct s_interface
*/

typedef struct	s_assets_data
{
	char	*file;
	int		used;
	char	*name;
}				t_assets_data;

/*
**	#######################################
*/

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

# define NB_PROPERTIES 14

typedef struct	s_toolbar
{
	SDL_Surface	*select[2];
	SDL_Surface	*move[2];
	SDL_Surface	*properties[NB_PROPERTIES];
	t_assets	assets[3];
	SDL_Surface	*player_start;
}				t_toolbar;

/*
**	int	nb_asset[4] : 	[0] = ammo, [1] = monster, [2] = healpack,
**						[3] = playerstart
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
	int				nb_asset[4];
	t_vec2f			category_pos[4];
	int				selected_asset;
	int				selected_asset_cat;
	t_vec2f			selected_asset_position;
	t_monster_list	*monster_list;
	t_vec2f			mouse_pos;
	t_vec2f			tex_select[3];
	t_vec2f			btn_floor_height_pos;
	t_vec2f			btn_ceil_height_pos;
	t_vec2f			cbox_door_p;
	t_vec2f			cbox_skybox_p;
}				t_interface;

/*
**	texture_to_scale = size to resize the image,
**	texture_to_scale = 32 -> will resize the image to 32x32 pixels
**	hl_wall = highlighted_wall
**
**	t_assets_data	assets_data[100]; index given by nb_asset (cf. s_interface)
*/

typedef struct	s_data
{
	SDL_Window		*win;
	SDL_Surface		*screen;
	SDL_Surface		**textures;
	t_texture_data	*texture_list;
	t_interface		interface;
	t_assets_data	assets_data[100];
	t_vec3f			player_start;
	int16_t			startsectnum;
	t_sector		sectors[MAXNUMSECTORS];
	t_wall			walls[MAXNUMWALLS];
	t_monster		monsters[MAXNUMMONSTERS];
	int16_t			numsectors;
	int16_t			numwalls;
	uint16_t		nummonsters;
	int				nb_texture;
	int32_t			nb_used_texture;
	int				default_texture;
	double			scale;
	t_vec2f			pos;
	t_wall			*selectedwall;
	t_wall			*selectedwall2;
	int				selected_sector;
	int				selected_wall;
	int				selected_texture;
	bool			grid_locking;
	bool			sectordrawing;
	double			texture_to_scale;
	t_vec2f			temp;
	t_wall			*hl_wall;
	int				hl_wallnum;
	int				hl_wallnum_draw;
}				t_data;

/**/int			bmp_reader(t_data *d);
/**/void	add_monster_to_list(t_data *d, t_vec2f *xy,int sectn);
/**/int			delete_monster(t_data *d);

void			debug_print(t_data *d);

/*
**	ed_init_structures.c1
*/

void			init_structure(t_data *d);
void			init_data(t_data *d);

/*
**	ed_init.c
*/

int				init_editor(t_data *d);

/*
**	ed_init_texture.c
*/

int				init_texture(t_data *d);

/*
**	ed_init_assets.c
*/

int				get_interface_assets_files(t_data *d, char **path);

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
void			get_selected_asset(t_data *d);
int				add_asset_to_map(t_data *d, int x, int y);

/*
**	ed_interface.c
*/

void			show_menu(t_data *d);

/*
**	ed_interface_functions.c
*/

t_vec2f			grid_lock(t_data *d, t_vec2f p);
int				is_on_select_move_icon(t_data *d, int x, int y);
int				check_if_mouse_on_menu(t_data *d, int x, int y);
void			btn_height(t_data *d, int x, int y, t_interface *i);
int				is_on_checkbox(t_data *d, int x, int y);

/*
**	ed_interface_properties.c
*/

void			draw_selection_arround_asset(t_data *d, t_vec2f *category);
void			print_properties(t_data *d, SDL_Surface **properties);

/*
**	ed_interface_properties2.c
*/

void			draw_separator(t_data *d, int x, int y, int color);
void			fill_texture_selection(t_data *d, t_interface *i, int wallnum);
void			show_preview(t_data *d, t_assets *a);

/*
**	ed_utils.c
*/

void			copy_surface_to_surface(SDL_Surface *src,
								SDL_Surface *dest, int p[2], t_data *d);
void			save_selected_texture(t_data *d, int x, int y, int wallnum);
void			remove_backgorund_image(SDL_Surface *s);
double			fclamp(double x, double min, double max);

/*
**	ed_event.c
*/

void			event_key_up(t_data *d, SDL_Keycode key);
void			event_key_down(t_data *d, SDL_Keycode key);
void			zoom(t_data *d, SDL_Event *e);
void			event_motion_mouse(t_data *d, SDL_Event *e);

/*
**	ed_event_function.c
*/

int				menu_save_button(t_data *d, SDL_Event *e);
int				menu_exit_button(t_data *d, SDL_Event *e);
int				properties_texture_selection(t_data *d, SDL_Event *e);
int				selecting_assets(t_data *d, SDL_Event *e);

/*
**	ed_event_mouse_button.c
*/

int				event_mouse_button(t_data *d, SDL_Event *e);

/*
**	ed_save_file.c
*/

int				save_file(t_data *d);

/*
**	ed_fix_data_to_save.c
*/

void			set_texture_name(t_data *d, t_sector *s, t_wall *w);
void			set_texture_used(t_data *d, t_sector *s, t_wall *w);

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

#endif
