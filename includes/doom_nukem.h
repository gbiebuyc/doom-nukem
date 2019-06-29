/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 21:53:29 by nallani           #+#    #+#             */
/*   Updated: 2019/06/29 21:14:42 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_NUKEM_H
# define DOOM_NUKEM_H

# include <common.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <pthread.h>
# include <limits.h>

# define WIDTH 800
# define HEIGHT 600
# define MUST_BE_DESTROYED 255
# define FPS 60
# define MAX_Y_OFFSET (HEIGHT/2)
# define PLAYER_HITBOX 0.1
# include <structs_doom.h>
# define PATH_MAP "./maps/"
# define POSTER_W 1.3
# define MINIMUM_HEIGHT 0.5
# define BLASTER_SOUND 1
# define CRYO_SOUND 2
# define M16_SOUND 3
# define EXPLOSION_SOUND 4
# define PLAYER_FELL_SOUND 5
# define PLAYER_GOT_HIT_SOUND 6
# define PLAYER_DEATH_SOUND 7
# define CHARG_AGRO_SOUND 8
# define CHARG_ATK_SOUND 9
# define CHARG_DEATH_SOUND 10
# define MOTHER_AGRO_SOUND 11
# define MOTHER_ATK_SOUND 12
# define MOTHER_DEATH_SOUND 13
# define MINIMUM_CROUCH_HEIGHT 0.2
# define MINIMUM_CEIL_DIST 0.1
# define JUMP_FIX 0.01
# define JUMP_FORCE 0.08
# define M16_HITBOX 0.2
# define EASY 0
# define NORMAL 1
# define HARD 2

void		draw_aim_cross(t_data *d);
void		m16_shoot(t_data *d);
int16_t		scan_sect_point_line(t_data *d, uint16_t sect_to_scan, double dist,
		bool hit_all);
double		find_closest_wall_dist(t_data *d, uint16_t sect_to_scan);
int16_t		recur_scan_point_line(t_data *d,
		int16_t sect_to_scan, int16_t old_sect, bool hit_all);
double		get_dist_to_intersect_wall(t_data *d, t_vec2f wall1, t_vec2f wall2);
void		putpixel(t_data *d, int x, int y, uint32_t color);
uint32_t	getpixel(SDL_Surface *s, double x, double y);
uint32_t	getpixel2(SDL_Surface *s, double x, double y);
uint32_t	getpixel3(SDL_Surface *s, short x, short y);
uint32_t	getpixel4(SDL_Surface *s, int u, double y);
bool		inside(t_data *d, int16_t sectnum, t_vec2f pos);
bool		clip_wall(double *x1, double *z1, double x2, double z2);
void		proj_wall(t_data *d, t_projdata *p, t_frustum *fr, t_vec2f v[2]);
void		draw_wall(t_data *d, t_projdata *p, t_frustum *fr);
void		draw_wall_no_nei(t_data *d, t_projdata *p, t_frustum *fr);
void		draw_wall3(t_data *d, t_projdata *p, t_frustum *nfr, bool *visible);
void		draw_wall_transparent(t_data *d, t_projdata *p, t_frustum *fr);
void		draw_floor(t_data *d, t_projdata *p, t_frustum *fr);
void		draw_ceil(t_data *d, t_projdata *p, t_frustum *fr);
void		*draw_ceil_thread(void *arg);
void		player_actions(t_data *d);
void		render(t_data *d);
void		draw_weapon(t_data *d);
void		blaster_shot(t_data *d);
void		render_sector(t_data *d, t_sector *sect, t_frustum *fr);
void		draw_sprite(t_data *d, t_frustum *fr, t_sprite_list *sprite);
void		init_player(t_data *d, t_player *player);
void		init_monsters(t_data *d);
void		init_projectiles(t_data *d);
void		swap_list(uint8_t type, uint16_t id, t_data *d, int sectnum[2]);
int16_t		update_cursect_smart(t_data *d,
		short depth, t_vec2f pos, uint16_t cursectnum);
int16_t		update_cursect_proj(int16_t sects[2],
		t_data *d, int depth, t_vec3f pos);
void		destroy_mail(short id, t_sector *sector, uint8_t type_to_destroy);
void		update_anim_projectile(
		t_projectile *projectile, t_data *d, short id,
			bool has_collided);
void		monster_anim_state(t_monster *monster,
		t_monster_type *monster_type, t_data *d);
void		monster_hit(t_data *d, uint16_t damage, uint16_t id_monster);
void		collision_monster_monster(t_data *d,
		short cur_sect, t_monster *monster);
void		collision_with_monster(t_data *d, short cur_sect);
bool		collision_proj_monster(t_data *d,
		t_sector *sector, t_projectile *projectile);
bool		collision_proj_player(t_data *d, t_projectile *projectile);
t_vec3f		transform_vec3f_to_screen(t_data *d, t_vec3f v);
void		monster_behaviour(t_data *d, t_monster *monster, uint16_t id);
void		monster_behaviour_chargingdemon(
		t_data *d, t_monster *monster, uint16_t id);
void		charging_demon_wait(t_data *d, t_monster *monster);
double		getshadefactor(t_data *d, t_projdata *p, double dist);
uint32_t	shade(double factor, uint32_t c);
void		reorder_sprite(t_data *d, t_sector *sect);
t_vec3f		vec2to3(t_vec2f v);
t_vec2f		vec3to2(t_vec3f v);
double		vec3f_length(t_vec3f v);
bool		is_inside_vec2f(t_vec2f p1, t_vec2f p2, t_vec2f point);
bool		is_near(double v1, double v2, double range);

t_vec2f		intersect(t_vec2f p0, t_vec2f p1, t_vec2f p2, t_vec2f p3);
uint32_t	alpha(uint32_t	old_colo, uint32_t	new_colo);
void		draw_string(t_data *d, t_font f);
void		init_font(t_data *d);
void		transformvertex(t_data *d, t_vec2f v, double *x, double *z);
double		get_floorheight_point(t_data *d, int16_t sectnum, t_vec2f p);
double		get_floorheight_player(t_data *d, int16_t sectnum);
double		get_floordh(t_data *d, t_sector *sect, t_vec2f v);
double		get_ceilheight_point(t_data *d, int16_t sectnum, t_vec2f p);
double		get_ceilheight_player(t_data *d, int16_t sectnum);
double		get_ceildh(t_data *d, t_sector *sect, t_vec2f v);
void		init_everything(t_data *d, char *map);
void		fix_picnum(t_data *d);
void		handle_finish(t_data *d);
void		*sound_thread(void *void_arg);
int			load_sound(t_data *d, int f);
void		play_sound(t_data *d, uint8_t id);
void		the_end(t_data *d);
t_vec3f		transform_back(t_data *d, t_vec3f v);
void		proj_floor(t_data *d, t_projdata *p);
void		proj_ceil(t_data *d, t_projdata *p);
double		edge_function(t_vec3f a, t_vec3f b, int x, int y);
bool		collision(t_data *d, t_sector *sect);
bool		collision_monster_wall(t_data *d,
		t_sector *sect, t_vec2f *pos, double dist_coll);
void		draw_assets(t_data *d,
		t_projdata *p, t_frustum *fr, int16_t sectnum);
void		asset_collision(t_data *d);
void		use_asset(t_data *d, t_assets *asset);
void		draw_hud(t_data *d);
void		invoke_msg(t_data *d, char *msg);
bool		activate_door(t_data *d, t_sector *sect);
void		press_e(t_data *d);
void		putpixel2(t_data *d, double z, t_vec2 p, uint32_t color);
t_vec2f		get_closest(t_vec2f a, t_vec2f b, t_vec2f p);
void		move_monster(t_data *d, int i);
void		draw_health(t_data *d);
void		draw_fuel(t_data *d);
void		draw_ammo(t_data *d, int ammo);
void		check_dangerous_area(t_data *d);
void		decrease_fuel(t_data *d);
void		handle_respawn(t_data *d);
void		precompute_texanim(t_data *d);
void		intro_screen(t_data *d);
void		help_screen(t_data *d);
void		draw_string_typewriter_effect(t_data *d, t_font f);
void		main_menu(t_data *d);
void		difficulty_menu(t_data *d);
void		pause_menu(t_data *d);
int			ft_mod(int i, int n);

/*
** update_2.c
*/

void		update_2(t_data *d);

/*
** update.c
*/

void		update(t_data *d);

/*
** m16_util.c
*/

bool		set_pos_m16_inside_sec(t_data *d, int16_t id, t_vec2f *pos);

/*
** m16_recur.c
*/

t_m16_inf	m16_recur(t_data *d, int16_t sect_to_scan,
		int16_t old_sect);

/*
** player_damage.c
*/
void		player_hit_projectile(t_data *d, t_projectile *projectile);
void		player_fell(t_data *d);
void		player_contact_monster(t_data *d, t_monster *monster);
/*
** color_buffer.c
*/
void		change_buf_colo(t_data *d, uint16_t amount, uint32_t colo);
void		color_buffer(t_data *d);
/*
** inertia.c
*/
void		change_inertia(t_data *d, double angle, double length);
void		inertia(t_data *d, t_vec2f mvt);
/*
** create_projectile.c
*/

void		create_projectile_monster(
		t_data *d, short id_of_proj_type, t_monster *monster);
void		create_projectile(t_data *d, short id_of_proj_type);

/*
** get_rot_monster.c
*/

uint8_t		get_nb_anim_from_rot(double monster_rot,
		t_vec2f monster_pos, t_vec2f player_pos);
/*
** fly_gravity.c
*/

void		fly_gravity(t_data *d);

/*
** draw_monster.c
*/

void		draw_monster(t_data *d, t_monster monster);

/*
** utils.c
*/

double		lerp(double norm, double min, double max);
double		norm(double val, double min, double max);
int			clamp(int x, int min, int max);
double		fclamp(double x, double min, double max);

/*
** exit.c
*/

void		proper_exit(t_data *d);
void		err_exit(t_data *d, char count, const char *msg);

/*
** ini
*/

void		init_sdl(t_data *d);

/*
** loop.c
*/

void		loop(t_data *d);

/*
** events.c
*/

void		event_key_up(t_data *d, SDL_KeyboardEvent event);
void		event_mouse_motion(t_data *d, SDL_MouseMotionEvent event);
void		event_mouse_button(t_data *d, SDL_MouseButtonEvent event);
void		event_key_down(t_data *d, SDL_KeyboardEvent event);

/*
** jump.c
*/

void		normal_gravity(t_data *d);
void		jump(t_data *d);

/*
**	movement.c
*/

void		movement(t_data *d);

/*
**	load_map.c
*/

void		load_map(t_data *d, char *map);

/*
**	load_assets.c
*/

int			read_posters_data(t_data *d, int f);
int			read_monsters_data(t_data *d, int f);
int			read_assets_texture(t_data *d, int f);
int			read_assets_data(t_data *d, int f);

int			load_monsters_texture(t_data *d, int f);

int			load_weapons_texture(t_data *d,
		int f, int *nb_tex, int *nb_projectiles);

#endif
