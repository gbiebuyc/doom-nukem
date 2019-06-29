/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_doom.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 23:02:19 by nallani           #+#    #+#             */
/*   Updated: 2019/06/29 21:16:24 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_DOOM_H
# define STRUCTS_DOOM_H

typedef struct		s_display_data
{
	t_vec2f			start;
	t_vec2f			end;
	t_vec2f			scale;
	int				cut_start;
	int				cut_end;
	int				*ytop;
	int				*ybot;
}					t_display_data;

typedef	struct		s_m16_inf
{
	double			dist;
	int16_t			id_of_monst;
}					t_m16_inf;

typedef struct		s_col_inf
{
	t_vec3f			pos;
	bool			ok;
}					t_col_inf;

typedef struct		s_cam
{
	t_vec3f			pos;
	double			rot;
	double			sin;
	double			cos;
	double			y_offset;
}					t_cam;

typedef struct		s_frustum
{
	int				ytop[WIDTH];
	int				ybottom[WIDTH];
	int				x1;
	int				x2;
	bool			visitedportals[MAXNUMWALLS];
}					t_frustum;

typedef struct		s_projdata
{
	double			x1;
	double			x2;
	int				cx1;
	int				cx2;
	double			z1;
	double			z2;
	int				y1a;
	int				y2a;
	int				y1b;
	int				y2b;
	int				y1c;
	int				y2c;
	int				y1d;
	int				y2d;
	t_sector		*neighbor;
	int				ny1a;
	int				ny2a;
	int				ny1b;
	int				ny2b;
	double			u1;
	double			u2;
	double			y_scale;
	t_wall			*wall;
	t_sector		*sector;
	double			n;
	double			z;
	int				x;
	int				y;
	double			u;
	int				ya;
	int				yb;
	int				yc;
	int				yd;
	int				nya;
	int				nyb;
	double			zbuffer[WIDTH];
	bool			visible[WIDTH];
	double			doorheight;
	double			doorbottom;
	double			u1_poster;
	double			u2_poster;
	double			poster_h;
	t_vec3f			v[3];
	t_vec3f			c[3];
	double			area;
	t_vec3f			a[3];
	t_vec3f			b[3];
	double			areaa;
	bool			is_on_floor;
	double			shadefactor;
	double			len;
	double			scale1;
	double			scale2;
	int				u_tex;
	int				u_poster;
	SDL_Surface		*tex;
	SDL_Surface		*poster;
	int				ya_poster;
	int				yb_poster;
	int				margin;
}					t_projdata;

# define MAX_STATE_OF_PROJ_ANIM 21
# define COLLISION_ID MAX_STATE_OF_PROJ_ANIM - 1

typedef struct		s_projectile
{
	bool			is_active;
	bool			has_collided;
	uint8_t			id_type;
	uint16_t		cursectnum;
	t_vec3f			pos;
	t_vec3f			dir;
	uint8_t			weapon_id;
	uint8_t			time_remaining_anim;
	uint8_t			current_anim_playing;
	t_monster		*target;
}					t_projectile;

typedef struct		s_proj_type
{
	double			hitbox_radius;
	double			speed;
	double			size;
	uint16_t		damage;
	uint8_t			anim_order[MAX_STATE_OF_PROJ_ANIM];
	uint8_t			kind;
	bool			threat_to_player;
	bool			threat_to_monster;
}					t_proj_type;

# define NORMAL 1
# define CHARGED 2
# define DELAY 3

typedef struct		s_weapon_type
{
	uint8_t			rate_of_fire[2];
	uint8_t			time_to_reload[2];
	uint8_t			shooting_type[2];
	uint8_t			type;
	uint8_t			left_projectile;
	uint8_t			right_projectile;
	uint16_t		max_ammo;
	uint16_t		current_ammo;
	bool			has_alt_fire;
}					t_weapon_type;

# define MAX_STATE_MONSTER 20

typedef struct		s_monster_type
{
	double			height;
	double			size;
	uint16_t		health;
	double			floating;
	double			hitbox_radius;
	uint8_t			id_of_proj;
	uint8_t			anim_order[MAX_STATE_MONSTER];
}					t_monster_type;

# define MAX_KIND_OF_WEAP 3
# define MAX_ANIM_PER_WEAP 15
# define LEFT_CLICK 1
# define RIGHT_CLICK 2

typedef	struct		s_player
{
	int16_t			health;
	uint8_t			can_be_stomped;
	uint8_t			current_weapon;
	uint8_t			can_shoot;
	uint8_t			timer_change_weap;
	uint8_t			timer_anim_weap;
	uint8_t			current_anim_playing;
	uint8_t			speed_anim[MAX_KIND_OF_WEAP];
	uint8_t			weapon_anim[MAX_KIND_OF_WEAP][MAX_ANIM_PER_WEAP];
	uint8_t			click;
	uint16_t		is_flying;
	uint8_t			can_move;
	double			minimum_height;
	double			gravity;
}					t_player;

# define RED 0xFF0000
# define GREEN_BLAST 0x5CE26E
# define MAX_BUF_VALUE 240

typedef struct		s_color_buf
{
	uint32_t		colo;
	int16_t			value;
}					t_color_buf;

# define MAXNBOFANIMATION 5
# define MAX_PROJECTILE_TEX_PER_WEAP MAX_STATE_OF_PROJ_ANIM
# define MAX_KIND_OF_PROJECTILE 3
# define MAX_PROJECTILES 100
# define MOUSE_PRESSED 1
# define MOUSE_RELEASED 2
# define MOUSE_NO_ACTION 3
# define NB_OF_SOUNDS 14

typedef struct		s_data
{
	t_player		player;
	SDL_Window		*win;
	SDL_Surface		*screen;
	SDL_Surface		**textures;
	int32_t			nb_textures;
	SDL_Surface		**posters;
	int32_t			nb_posters;
	SDL_Surface		**assets_texture;
	int16_t			nb_assets_texture;
	char			**tex_name_list;
	SDL_Surface		*monster_text[MAXTYPEMONSTERS]
	[MAX_STATE_MONSTER][MAXNBOFANIMATION];
	SDL_Surface		*projectile_tex[MAX_KIND_OF_PROJECTILE]
	[MAX_PROJECTILE_TEX_PER_WEAP];
	SDL_Surface		*weapon_tex[MAX_KIND_OF_WEAP]
	[MAX_ANIM_PER_WEAP];
	const Uint8		*keys;
	uint8_t			left_mouse_button;
	uint8_t			right_mouse_button;
	t_cam			startcam;
	t_cam			cam;
	t_sector		sectors[MAXNUMSECTORS];
	t_wall			walls[MAXNUMWALLS];
	t_monster		*monsters;
	t_assets		**assets;
	int16_t			nb_assets;
	t_monster_type	monster_type[MAXTYPEMONSTERS];
	t_projectile	projectiles[MAX_PROJECTILES];
	t_proj_type		projectile_type[MAX_KIND_OF_PROJECTILE];
	t_weapon_type	weapon_type[MAX_KIND_OF_WEAP];
	uint16_t		nummonsters;
	int16_t			numsectors;
	int16_t			numwalls;
	int16_t			startsectnum;
	int16_t			cursectnum;
	bool			debug_pause;
	double			dooranimstep[MAXNUMWALLS];
	double			doorstate[MAXNUMWALLS];
	double			lightblink;
	t_color_buf		color_buf;
	t_vec2f			inertia;
	unsigned char	font[96][5];
	double			*zbuffer;
	double			floorheightplayer;
	double			ceilheightplayer;
	char			nextmap[100];
	SDL_AudioSpec	wav_spec[NB_OF_SOUNDS];
	Uint32			wav_length[NB_OF_SOUNDS];
	Uint8			*wav_buffer[NB_OF_SOUNDS];
	int				musicnum;
	int				soundnum;
	pthread_t		music_thread;
	t_assets		*slot1;
	t_assets		*slot2;
	t_assets		*slot3;
	char			msg[100];
	uint32_t		msg_start;
	uint32_t		last_dangerous_area_damage;
	int				difficulty;
}					t_data;

typedef struct		s_thread_arg
{
	t_data			*d;
	t_projdata		*p;
	t_frustum		*fr;
}					t_thread_arg;

typedef	struct		s_args_multi_colo_buf
{
	t_data			*d;
	short			start_x;
	short			max_x;
}					t_args_multi_colo_buf;

typedef struct		s_sound_thread_arg
{
	t_data			*d;
	bool			is_music;
}					t_sound_thread_arg;

#endif
