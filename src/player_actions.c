/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <unkown@noaddress.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 16:37:00 by nallani           #+#    #+#             */
/*   Updated: 2019/06/07 21:57:11 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	shoot_weapon(t_data *d)
{
//	static unsigned short	charged_time;

	if (d->weapon_type[d->player.current_weapon].type == NORMAL || 1)
	{
//	printf("can shoot weapon\n");
		if (d->left_mouse_button == MOUSE_PRESSED)
		{
			d->player.timer_anim_weap = d->player.speed_anim[d->player.current_weapon];
			d->player.current_anim_playing = 1;
			d->player.can_shoot = d->weapon_type[d->player.current_weapon].rate_of_fire[0];
		}
		if (d->right_mouse_button == MOUSE_PRESSED && d->weapon_type[d->player.current_weapon].has_alt_fire)
		{
			d->player.can_shoot = d->weapon_type[d->player.current_weapon].rate_of_fire[1];
			d->player.timer_anim_weap = d->player.speed_anim[d->player.current_weapon];
			d->player.current_anim_playing = 1;
		}
	}
	if (d->weapon_type[d->player.current_weapon].type == CHARGED)
	{
//		if (d->left_mouse_button == 
	}
}

# define TRANSLATE_WEAP_TIME 30

void	change_weap(t_data *d)
{
	uint8_t		cur_weap;
	bool		changed;

	cur_weap = d->player.current_weapon;
	changed = false;
	if (cur_weap == CRYO_BALLISTA && d->player.current_anim_playing &&
			d->player.current_anim_playing < 6)
		return ;
	if (cur_weap == BLASTER && d->player.can_shoot)
		return ;
	if (cur_weap != CRYO_BALLISTA && d->keys[SDL_SCANCODE_1])
	{
		d->player.current_weapon = CRYO_BALLISTA;
		changed = true;
	}
	else if (cur_weap != BLASTER && d->keys[SDL_SCANCODE_2])
	{
		d->player.current_weapon = BLASTER;
		changed = true;
	}
	if (changed)
	{
		d->player.timer_change_weap = TRANSLATE_WEAP_TIME;
		d->player.can_shoot = TRANSLATE_WEAP_TIME;
		d->player.current_anim_playing = 0;
		d->player.timer_anim_weap = d->player.speed_anim[d->player.current_weapon];
	}
}

void	player_actions(t_data *d)
{
	if (d->player.can_shoot)
		d->player.can_shoot--;
	else
		shoot_weapon(d);
	if (d->player.current_weapon == CRYO_BALLISTA && d->player.current_anim_playing == 5
			&& !d->player.timer_anim_weap)
		create_projectile(d, d->weapon_type[d->player.current_weapon].left_projectile);
	if (d->player.current_weapon == BLASTER && d->player.current_anim_playing == 11
			&& !d->player.timer_anim_weap)
		blaster_shot(d);
	if (d->player.timer_change_weap)
		d->player.timer_change_weap--;
	if (d->player.timer_change_weap < 15)
		change_weap(d);
}
