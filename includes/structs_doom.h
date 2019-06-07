/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_doom.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 23:02:19 by nallani           #+#    #+#             */
/*   Updated: 2019/06/07 23:22:53 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_DOOM_H
# define STRUCTS_DOOM_H

typedef struct	s_display_data
{
	t_vec2f		start;
	t_vec2f		end;
	t_vec2f		scale;
	int			cut_start;
	int			cut_end;
	int			*ytop;
	int			*ybot;
}				t_display_data;

typedef struct	s_col_inf
{
	t_vec3f		pos;
	bool		ok;
}				t_col_inf;

typedef struct	s_cam
{
	t_vec3f		pos;
	double		rot;
	double		sin;
	double		cos;
	double		y_offset;
}				t_cam;
/* Put in common but not really needed in common beside compilation
# define IS_PROJECTILE 0
# define IS_MONSTER 1

typedef struct	s_sprite_list
{
	int16_t					id;
	struct s_sprite_list	*next;
	uint8_t 				type;
}				t_sprite_list;
*/
typedef struct	s_projdata
{
	double		x1;
	double		x2;
	int			cx1;
	int			cx2;
	double		z1;
	double		z2;
	int			y1a;
	int			y2a;
	int			y1b;
	int			y2b;
	t_sector	*neighbor;
	int			ny1a;
	int			ny2a;
	int			ny1b;
	int			ny2b;
	double		u_begin;
	double		u_end;
	double		y_scale;
	t_wall		*wall;
	t_sector	*sector;
	double		*zbuffer;
	double		n;
	double		z;
	int			x;
	int			y;
	double		u;
	int			ya;
	int			yb;
	int			nya;
	int			nyb;
	bool		visible[WIDTH];
	double		doorheight;
	double		doorbottom;
	double		sin;
	double		cos;
	double		altitude;
}				t_projdata;

typedef struct	s_frustum
{
	int			ytop[WIDTH];
	int			ybottom[WIDTH];
	int			x1;
	int			x2;
	bool		visitedportals[MAXNUMWALLS];
}				t_frustum;

# define MAX_STATE_OF_PROJ_ANIM 21 //add one for collision changes
# define COLLISION_ID MAX_STATE_OF_PROJ_ANIM - 1

typedef struct	s_projectile
{
	bool		is_active;
	bool		has_collided;
	uint8_t		id_type;
	uint16_t	cursectnum;
	t_vec3f		pos;
	t_vec3f		dir;
	uint8_t		weapon_id;
	uint8_t		time_remaining_anim;
	uint8_t		current_anim_playing;
}				t_projectile;

typedef struct	s_proj_type
{
	double		hitbox_radius;
	double		speed;
	double		size;
	uint16_t	damage;
	uint8_t		anim_order[MAX_STATE_OF_PROJ_ANIM];
	uint8_t		kind;
	bool		threat_to_player;
	bool		threat_to_monster;
}				t_proj_type;

# define NORMAL 1 // stands for normal weapon (think of a gun)
# define CHARGED 2 // stand for a charged weapon (laser ?)
# define DELAY 3 //when a weapon has a small time before shooting

typedef struct s_weapon_type
{
	uint8_t		rate_of_fire[2]; // all in frames (read time before shooting again)
	uint8_t		time_to_reload[2]; //all in frames (if we need to reload ?)
	uint8_t		shooting_type[2]; //instant shot, released shot need to reload etc..
	// 0 stand for left click 1 for right click
	uint8_t		type;
	uint8_t		left_projectile;
	uint8_t		right_projectile;
	uint16_t	max_ammo;
	uint16_t	current_ammo; // not really good place but no need to create separate instance of weapons ?
	bool		has_alt_fire;
}				t_weapon_type;

# define MAX_STATE_MONSTER 20//to be changed

typedef struct	s_monster_type
{
	double		height;
	double		width;
	double		size;
	uint16_t	health;
	double		floating;
	double		hitbox_radius;
	uint8_t		id_sprite;
	uint8_t		anim_order[MAX_STATE_MONSTER];	
}				t_monster_type;

# define MAX_KIND_OF_WEAP 3
# define MAX_ANIM_PER_WEAP 15
# define LEFT_CLICK 1
# define RIGHT_CLICK 2

typedef	struct	s_player
{
	uint8_t		life;
//	uint8_t shield; gamedesign
	uint8_t		current_weapon;
	uint8_t		can_shoot;
	uint8_t		timer_change_weap;
	uint8_t		timer_anim_weap;
	uint8_t		current_anim_playing;//weap
	uint8_t		speed_anim[MAX_KIND_OF_WEAP];
	uint8_t		weapon_anim[MAX_KIND_OF_WEAP][MAX_ANIM_PER_WEAP];
	uint8_t		click;
}				t_player;

# define IS_GREEN 8
# define IS_RED 16
# define MAX_BUF_VALUE 180

typedef struct	s_color_buf
{
	uint8_t		colo;
	uint16_t		value;// 16 needed to not exceed uint8_t with additions
}				t_color_buf;

# define MAXNBOFANIMATION 5
# define MAX_PROJECTILE_TEX_PER_WEAP MAX_STATE_OF_PROJ_ANIM
# define MAX_KIND_OF_PROJECTILE 3
# define MAX_PROJECTILES 100
# define MOUSE_PRESSED 1
# define MOUSE_RELEASED 2
# define MOUSE_NO_ACTION 3

typedef struct	s_data
{
	t_player		player;
	SDL_Window		*win;
	SDL_Surface		*screen;
	SDL_Surface		**textures;
	int32_t			nb_textures;
	char			**tex_name_list;
	SDL_Surface		*monster_text[MAXTYPEMONSTERS][MAX_STATE_MONSTER][MAXNBOFANIMATION];
	SDL_Surface		*projectile_tex[MAX_KIND_OF_PROJECTILE][MAX_PROJECTILE_TEX_PER_WEAP];
	SDL_Surface		*weapon_tex[MAX_KIND_OF_WEAP][MAX_ANIM_PER_WEAP];
	const Uint8		*keys;
	uint8_t			left_mouse_button;
	uint8_t			right_mouse_button;
	t_cam			cam;
	t_sector		sectors[MAXNUMSECTORS];
	t_wall			walls[MAXNUMWALLS];
	t_monster		monsters[MAXNUMMONSTERS];
	t_monster_type	monster_type[MAXTYPEMONSTERS];
	t_projectile	projectiles[MAX_PROJECTILES];
	t_proj_type		projectile_type[MAX_KIND_OF_PROJECTILE];
	t_weapon_type	weapon_type[MAX_KIND_OF_WEAP];
	uint16_t		nummonsters;
	int16_t			numsectors;
	int16_t			numwalls;
	int16_t			cursectnum;
	bool			debug_pause;
	double			dooranimstep[MAXNUMWALLS];
	double			doorstate[MAXNUMWALLS];
	double			lightblink;
	t_color_buf		color_buf;
	t_vec2f			inertia;
	unsigned char	font[96][5];
}				t_data;

/*
** Animation defines
*/

#endif
