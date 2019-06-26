/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <unkown@noaddress.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 16:37:00 by nallani           #+#    #+#             */
/*   Updated: 2019/06/26 21:58:08 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	shoot_sound(t_data *d)
{
	static t_sound_thread_arg	arg;
	pthread_t					thread;

	arg = (t_sound_thread_arg){d, .is_music = false};
	d->soundnum = 1;
	if (pthread_create(&thread, NULL, sound_thread, &arg))
		ft_printf("pthread_create error\n");
}

void	shoot_weapon(t_data *d, uint8_t *w)
{
	if (d->weapon_type[*w].type == NORMAL || 1)
	{
		if (d->left_mouse_button == MOUSE_PRESSED)
		{
			d->player.timer_anim_weap = d->player.speed_anim[*w];
			d->player.current_anim_playing = 1;
			d->player.can_shoot = d->weapon_type[*w].rate_of_fire[0];
			d->player.click = LEFT_CLICK;
			if (*w == M16)
				m16_shoot(d);
			shoot_sound(d);
		}
		else if (d->right_mouse_button == MOUSE_PRESSED &&
				d->weapon_type[*w].has_alt_fire)
		{
			d->player.can_shoot = d->weapon_type[*w].rate_of_fire[1];
			d->player.timer_anim_weap = d->player.speed_anim[*w];
			d->player.current_anim_playing = 1;
			d->player.click = RIGHT_CLICK;
		}
	}
	if (d->weapon_type[*w].type == CHARGED)
	{
	}
}

#define TRANSLATE_WEAP_TIME 30

void	change_weap(t_data *d, uint8_t *w)
{
	uint8_t		cur_weap;
	bool		changed;

	cur_weap = *w;
	changed = false;
	if (cur_weap == CRYO_BALLISTA && d->player.current_anim_playing &&
			d->player.current_anim_playing < 6)
		return ;
	if (cur_weap == BLASTER && d->player.can_shoot)
		return ;
	if (cur_weap != CRYO_BALLISTA && d->keys[SDL_SCANCODE_1] &&
			(changed = true))
		*w = CRYO_BALLISTA;
	else if (cur_weap != BLASTER && d->keys[SDL_SCANCODE_2] && (changed = true))
		*w = BLASTER;
	else if (cur_weap != M16 && d->keys[SDL_SCANCODE_3] && (changed = true))
		*w = M16;
	if (changed)
	{
		d->player.timer_change_weap = TRANSLATE_WEAP_TIME;
		d->player.can_shoot = TRANSLATE_WEAP_TIME;
		d->player.current_anim_playing = 0;
		d->player.timer_anim_weap = d->player.speed_anim[*w];
	}
}

void	player_actions(t_data *d)
{
	uint8_t	*w;

	w = &d->player.current_weapon;
	if (d->player.can_shoot)
		d->player.can_shoot--;
	else
		shoot_weapon(d, w);
	if (*w == CRYO_BALLISTA && d->player.current_anim_playing == 5
			&& !d->player.timer_anim_weap)
		create_projectile(d, d->weapon_type[*w].left_projectile);
	if (*w == BLASTER && d->player.current_anim_playing == 11
			&& !d->player.timer_anim_weap)
		blaster_shot(d);
	if (d->player.timer_change_weap)
		d->player.timer_change_weap--;
	if (d->player.timer_change_weap < 15)
		change_weap(d, w);
}
