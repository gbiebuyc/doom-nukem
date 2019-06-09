/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 21:53:29 by nallani           #+#    #+#             */
/*   Updated: 2019/06/09 20:05:35 by nallani          ###   ########.fr       */
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

# define WIDTH 1000
# define HEIGHT 750
# define MUST_BE_DESTROYED 255// used by projectiles animation
# define FPS 60
# define MAX_Y_OFFSET (HEIGHT/2)
# define PLAYER_HITBOX 0.1
# include <structs_doom.h>

void	draw_aim_cross(t_data *d);
void	m16_shoot(t_data *d);
double	find_closest_wall_dist(t_data *d, uint16_t sect_to_scan);
double	get_dist_to_intersect_wall(t_data *d, t_vec2f wall1, t_vec2f wall2);
void	putpixel(t_data *d, int x, int y, uint32_t color);
uint32_t	getpixel(SDL_Surface *s, double x, double y);
uint32_t	getpixel2(SDL_Surface *s, double x, double y);
uint32_t	getpixel3(SDL_Surface *s, short x, short y);
bool	inside(t_data *d, int16_t sectnum, t_vec2f pos);
bool	clip_wall(double *x1, double *z1, double x2, double z2);
void	draw_wall(t_data *d, t_projdata *p, t_frustum *fr);
void	draw_floor(t_data *d, t_projdata *p, t_frustum *fr);
void	draw_ceil(t_data *d, t_projdata *p, t_frustum *fr);
void	*draw_ceil_thread(void *arg);
void	clamp_wall(bool visible[], int *x1, int *x2);
void	player_actions(t_data *d);
void	update(t_data *d);
void	render(t_data *d);
void	draw_weapon(t_data *d);
void	blaster_shot(t_data *d);
void	render_sector(t_data *d, t_sector *sect, t_frustum *fr);
void	draw_monster(t_data *d, t_sector *sect, t_frustum *fr, t_monster monster);
void	draw_sprite(t_data *d, t_sector *sector, t_frustum *fr, t_sprite_list *sprite);
void	init_player(t_data *d, t_player *player);
void	init_monsters(t_data *d);
void	init_projectiles(t_data *d);
void	swap_list(uint8_t type, uint16_t id, t_data *d, uint16_t cursectnum, uint16_t new_sect_num);
int16_t	update_cursect_player(int16_t sect_to_scan, t_data *d, short depth, int16_t old_sect);
int16_t	update_cursect_proj(int16_t sect_to_scan, t_data *d, int depth, int16_t old_sect, t_vec3f pos);
void	destroy_mail(short id, t_sector *sector, uint8_t type_to_destroy);
void	update_anim_projectile(t_projectile *projectile, t_data *d, short id,
		bool has_collided); // in monster_anim_state.c
void	monster_anim_state(t_monster *monster, t_monster_type *monster_type, t_data *d);
void	monster_hit(t_data *d, uint16_t damage, uint16_t id_monster); // projectile_collision.c
bool	collision_proj_monster(t_data *d, t_sector *sector, t_projectile *projectile);
bool	collision_proj_player(t_data *d, t_projectile *projectile);
void	monster_behaviour(t_data *d, t_monster *monster);
double		getshadefactor(t_data *d, t_projdata *p);
uint32_t	shade(double factor, uint32_t c);
void	activate_door(t_data *d);
void	reorder_sprite(t_data *d, t_sector *sect);
t_vec3f		vec2to3(t_vec2f v);
t_vec2f		vec3to2(t_vec3f v);
double vec3f_length(t_vec3f v);
bool	is_inside_vec2f(t_vec2f p1, t_vec2f p2, t_vec2f point);
bool	is_near(double v1, double v2, double range);
t_vec2f	intersect(t_vec2f p0, t_vec2f p1, t_vec2f p2, t_vec2f p3);
uint32_t	alpha(uint32_t	old_colo, uint32_t	new_colo);
void	draw_string(t_data *d, const char* str, int x, int y, uint32_t color);
void	init_font(t_data *d);

/*
** color_buffer.c
*/
void	change_buf_colo(t_data *d, uint16_t amount, uint32_t colo);
void	color_buffer(t_data *d);
/*
** inertia.c
*/
void	change_inertia(t_data *d, double angle, double length);
void	inertia(t_data *d, t_vec2f mvt);
/*
** create_projectile.c
*/

void	create_projectile_monster(t_data *d, short id_of_proj_type, t_monster *monster);
void	create_projectile(t_data *d, short id_of_proj_type);

/*
** utils.c
*/

double	lerp(double norm, double min, double max);
double	norm(double val, double min, double max);
int		clamp(int x, int min, int max);
double	fclamp(double x, double min, double max);

/*
** exit.c
*/

void	proper_exit(t_data *d);
void	err_exit(t_data *d, char count, const char *msg);

/*
** ini*/

void	init_sdl(t_data *d);

/*
** loop.c
*/

void	loop(t_data *d);

/*
** events.c
*/

void	event_mouse_motion(t_data *d, SDL_MouseMotionEvent event);
void	event_mouse_button(t_data *d, SDL_MouseButtonEvent event);
void	event_key_down(t_data *d, SDL_KeyboardEvent event);

/*
** jump.c
*/

void	gravity(t_data *d, int mod);
void	jump(t_data *d, bool pressed);

/*
**	movement.c
*/

void	movement(t_data *d);

/*
**	load_map.c
*/

void	load_map(t_data *d);

/*
**	load_assets.c
*/

int		read_monsters_data(t_data *d, int f);

#endif
