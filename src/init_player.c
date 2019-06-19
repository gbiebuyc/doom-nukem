/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <unkown@noaddress.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 18:06:18 by nallani           #+#    #+#             */
/*   Updated: 2019/06/10 00:08:36 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

# define MINIMUM_HEIGHT 0.5// defined in jump.c

void	init_player(t_data *d, t_player *player)
{
	(void)d;
	ft_bzero(player, sizeof(*player));
	player->current_weapon = CRYO_BALLISTA;
	player->speed_anim[CRYO_BALLISTA] = 4;
	player->weapon_anim[CRYO_BALLISTA][0] = 0;
	player->weapon_anim[CRYO_BALLISTA][1] = 2;
	player->weapon_anim[CRYO_BALLISTA][2] = 3;
	player->weapon_anim[CRYO_BALLISTA][3] = 4;
	player->weapon_anim[CRYO_BALLISTA][4] = 5;
	player->weapon_anim[CRYO_BALLISTA][5] = 6;
	player->weapon_anim[CRYO_BALLISTA][6] = 7;
	player->weapon_anim[CRYO_BALLISTA][7] = 8;
	player->weapon_anim[CRYO_BALLISTA][8] = 9;
	player->weapon_anim[CRYO_BALLISTA][9] = 10;
	player->weapon_anim[CRYO_BALLISTA][10] = 11;
	player->weapon_anim[CRYO_BALLISTA][11] = 12;
	player->weapon_anim[CRYO_BALLISTA][12] = 0;
	
	player->speed_anim[BLASTER] = 6;
	player->weapon_anim[BLASTER][0] = 3;
	player->weapon_anim[BLASTER][1] = 2;
	player->weapon_anim[BLASTER][2] = 4;
	player->weapon_anim[BLASTER][3] = 0;
	player->weapon_anim[BLASTER][4] = 5;
	player->weapon_anim[BLASTER][5] = 6;
	player->weapon_anim[BLASTER][6] = 7;
	player->weapon_anim[BLASTER][7] = 8;
	player->weapon_anim[BLASTER][8] = 9;
	player->weapon_anim[BLASTER][9] = 10;
	player->weapon_anim[BLASTER][10] = 11;
	player->weapon_anim[BLASTER][11] = 12;
	player->weapon_anim[BLASTER][12] = 13;
	player->weapon_anim[BLASTER][13] = 14;
	player->weapon_anim[BLASTER][14] = 0;
	d->color_buf.value = 0;

	player->speed_anim[M16] = 4;
	player->weapon_anim[M16][0] = 0;
	player->weapon_anim[M16][1] = 2;
	player->weapon_anim[M16][2] = 0;

	player->is_flying = 0;// set to 0 = false, otherwise it is the duration in frame (divide by 60 to get duration in sec)
	player->minimum_height = MINIMUM_HEIGHT;
	player->gravity = 0.0;// dont touch
	player->can_move = 0;// set to 0 unless you don't want to move, same than is_flying
	player->health = 100;
	d->cursectnum = d->startsectnum;
	d->cam = d->startcam;
}
