/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <unkown@noaddress.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 02:27:33 by nallani           #+#    #+#             */
/*   Updated: 2019/06/05 17:14:33 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

// OPEN CIRCLE_ANIM on slack to understand code for 1rst function

uint8_t		get_nb_anim_from_rot(double monster_rot, 
		t_vec2f monster_pos, t_vec2f player_pos)// get the NB of the animation based on where does it face compared to where you are
	//code is in circle_anim on slack
{
	double	rot;
	double	vision_rot;
	t_vec2f	vision;

	vision = sub_vec2f(monster_pos, player_pos);
	vision_rot = atan2(vision.y, vision.x);
	rot = vision_rot - monster_rot;
	rot += M_PI_2; // PANSEMENT ??
	if (rot > 2 * M_PI)
		rot -= 2 * M_PI;
	if (rot < 0)
		rot += 2 * M_PI;
	rot = rot -  0.125 * M_PI;
	if (rot > M_PI)
	{
		if (rot < 1.25 * M_PI)
			return (1);
		if (rot < 1.5 * M_PI)
			return (0);
		if (rot < 1.75 * M_PI)
			return (7);
		if (rot < 2 * M_PI)
			return (6);
	}
	if (rot > 0.75 * M_PI)
		return (2);
	if (rot > M_PI_2)
		return (3);
	if (rot > M_PI_4)
		return (4);
	if (rot < 0)
		return (6);
	return (5);
}

t_vec3f		get_projected_vertex(t_data *d, t_vec3f v, t_vec3f pos) // projection (for sprites only i think ?, unapplicable somewhere else)
{
	t_vec3f	new;
	t_vec3f dist;

	dist = sub_vec3f(pos, d->cam.pos);
	new = sub_vec3f(v, d->cam.pos);
	dist.z = dist.x * d->cam.sin + dist.z * d->cam.cos;
	new = (t_vec3f){
		new.x * d->cam.cos - new.z * d->cam.sin,
			new.y,
			new.x * d->cam.sin + new.z * d->cam.cos
	};
	new.x /= dist.z;
	new.y /= dist.z;
	new.x = new.x *  WIDTH + WIDTH * 0.5;
	new.y = new.y * -WIDTH + HEIGHT * 0.5 - d->cam.y_offset;
	return (new);
}

void	display_sprite(t_display_data a, t_data *d, SDL_Surface *s, bool rev) // display a sprite
	//a contains start end and scale values
	//rev is used to mirror an image
{
	int			x;
	int			y;
	int			colo;

	x = a.cut_start ; // pansement ?
	while (x <= a.cut_end)
	{
		y = ft_max(a.ytop[x], a.start.y); //pansement ?
		while(y <= ft_min(a.ybot[x], a.end.y))
		{
			if (rev)
		colo = getpixel(s, (1 - a.scale.x * (x - a.start.x)), a.scale.y * (y - a.start.y)); // arrive a etre > 1
			else
				colo = getpixel(s, a.scale.x * (x - a.start.x), a.scale.y * (y - a.start.y)); // arrive a etre > 1
			//if (colo >> 24)//wont work on windows
			{
				colo = alpha(((uint32_t *)d->screen->pixels)[x + y * d->screen->w], colo);
				putpixel(d, x, y, colo);
			}
			y++;
		}
		x++;
	}
}

void	draw_monster(t_data *d, t_sector *sector, t_frustum *fr, t_monster monster) //main function to draw a sprite, need
	//to adjust start_x with fr (see problem below in comments)
{
	t_vec3f			top_left;
	t_vec3f			bot_right;
	t_vec3f			monsterpos;
	t_display_data	a;

	monsterpos = (t_vec3f) {monster.pos.x, sector->floorheight + d->monster_type[monster.id_type].floating + monster.height, monster.pos.y};
	(void)fr;

	t_vec2f scale = (t_vec2f){monster.width, 0};
	actualize_dir(-d->cam.rot, &scale); // add ft_max entre pos du monstre et distance min pour affichage; //ou plutot
	// faire les collisions avec le joueur et empecher la bestiole d'avancer si trop proche ?
	top_left = get_projected_vertex(d, (t_vec3f){monsterpos.x - scale.x, monsterpos.y, monsterpos.z - scale.y}, monsterpos);
	bot_right = get_projected_vertex(d, (t_vec3f){monsterpos.x + scale.x,
			monsterpos.y + d->monster_type[monster.id_type].floating - monster.height, monsterpos.z + scale.y}, monsterpos);

	if (top_left.z > 0.0 && bot_right.z > 0.0)
	{
		a.start.x = top_left.x > bot_right.x ? bot_right.x : top_left.x;
		a.end.x = top_left.x > bot_right.x ? top_left.x : bot_right.x;
		a.scale.x = fabs(100.0 / (a.start.x - a.end.x) / 100);
		a.cut_start = ft_max(a.start.x, fr->x1);
		a.cut_end = ft_min(a.end.x, fr->x2);
		a.start.y = bot_right.y > top_left.y ? top_left.y : bot_right.y;
		a.end.y = bot_right.y > top_left.y ? bot_right.y : top_left.y;
		a.scale.y = fabs((100.0 / (a.start.y - a.end.y)) / 100);
		a.start.y +=1;
		a.end.y -=1;
		a.ytop = &fr->ytop[0];
		a.ybot = &fr->ybottom[0];
		printf("%f\n", top_left.x);
		int nb_of_anim = get_nb_anim_from_rot(monster.rot, monster.pos, vec3to2(d->cam.pos));
		if (nb_of_anim > 4)
		{
			nb_of_anim = 8 - nb_of_anim; 
			display_sprite(a, d, d->monster_text[monster.id_type][monster.anim_state][nb_of_anim], false);
		}
		else
			display_sprite(a, d, d->monster_text[monster.id_type][monster.anim_state][nb_of_anim], true);
	}
}

void	display_sprite_one_point(t_data *d, SDL_Surface *s,
		t_display_data display_data);
t_vec3f		transform_vec3f_to_screen(t_data *d, t_vec3f v);

void	display_sprite_one_point_rev(t_data *d, SDL_Surface *s,
		t_display_data display_data)
{
	int		x;
	int		y;
	int		colo;

	x = display_data.cut_start;
	while (x <= display_data.cut_end)
	{
		y = ft_max(display_data.ytop[x], display_data.start.y);
		while (y <= ft_min(display_data.ybot[x], display_data.end.y))
		{
			colo = getpixel(s, 1 - (display_data.scale.x * (x - display_data.start.x)),
					display_data.scale.y * (y - display_data.start.y));
			colo = alpha(((uint32_t *)d->screen->pixels)[x + y * d->screen->w], colo);
			putpixel(d, x, y, colo);
			y++;
		}
		x++;
	}
}
void	draw_monster_test(t_data *d, t_frustum *fr, t_monster monster)
{
	double			dist;
	t_display_data	a;
	t_vec3f			point_in_screen;
	t_vec3f			monsterpos;
	short			nb_of_anim[2];

	monsterpos = (t_vec3f){monster.pos.x,
	d->sectors[monster.cursectnum].floorheight,
	monster.pos.y};

	point_in_screen = transform_vec3f_to_screen(d, monsterpos);

	if (point_in_screen.z <= 0)
		return ;
	nb_of_anim[1] = get_nb_anim_from_rot(monster.rot, monster.pos, vec3to2(d->cam.pos));
	nb_of_anim[0] = nb_of_anim[1];
	if (nb_of_anim[1] > 4)
		nb_of_anim[0] = 8 - nb_of_anim[0];
	dist = vec3f_length(sub_vec3f((t_vec3f){monsterpos.x,
	monsterpos.y + monster.height / 2,
	monsterpos.z}
	, d->cam.pos));
	a.start.x = point_in_screen.x - (d->monster_text[monster.id_type][monster.anim_state][nb_of_anim[0]]->w) / dist * d->monster_type[monster.id_type].size; // a modifier 
	a.end.x = point_in_screen.x + (d->monster_text[monster.id_type][monster.anim_state][nb_of_anim[0]]->w) / dist * d->monster_type[monster.id_type].size; //same
	a.scale.x = fabs(100.0 / (a.start.x - a.end.x) * 0.01);
	a.cut_start = ft_max(a.start.x, fr->x1);
	a.cut_end = ft_min(a.end.x, fr->x2);

	a.start.y = point_in_screen.y - (d->monster_text[monster.id_type][monster.anim_state][nb_of_anim[0]]->h * 2) / dist * d->monster_type[monster.id_type].size; //same
	a.end.y = point_in_screen.y;
	a.scale.y = fabs(100.0 / (a.start.y - a.end.y) * 0.01);
	a.ytop = &fr->ytop[0];
	a.ybot = &fr->ybottom[0];

	if (nb_of_anim[1] < 4 && monster.anim_state < 10)// replace 10 by define of DEATH anim
		display_sprite_one_point_rev(d, d->monster_text[monster.id_type][monster.anim_state][nb_of_anim[0]], a);
	else
		display_sprite_one_point(d, d->monster_text[monster.id_type][monster.anim_state][nb_of_anim[0]],
				a);
}
