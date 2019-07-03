/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_projectile.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <unkown@noaddress.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 18:16:33 by nallani           #+#    #+#             */
/*   Updated: 2019/07/02 15:07:59 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

#define Y_OFFSET_TO_ROT -0.00125

void	set_projectile_id(t_data *d, short i, short id_of_proj_type)
{
	d->projectiles[i].is_active = true;
	d->projectiles[i].id_type = id_of_proj_type;
	d->projectiles[i].dir.z = d->cam.cos *
		d->projectile_type[id_of_proj_type].speed;
	d->projectiles[i].dir.y = d->cam.y_offset *
		Y_OFFSET_TO_ROT * d->projectile_type[id_of_proj_type].speed;
	d->projectiles[i].dir.x = d->cam.sin *
		d->projectile_type[id_of_proj_type].speed;
	d->projectiles[i].current_anim_playing =
		d->projectile_type[id_of_proj_type].anim_order[0];
	d->projectiles[i].pos = d->cam.pos;
	d->projectiles[i].has_collided = false;
	d->projectiles[i].cursectnum = d->cursectnum;
	d->projectiles[i].time_remaining_anim = 5;
	d->projectiles[i].current_anim_playing = 0;
	d->projectiles[i].weapon_id = d->player.current_weapon;
	d->projectiles[i].target = NULL;
}

void	create_projectile(t_data *d, short id_of_proj_type)
{
	t_sprite_list	*new_projectile;
	short			i;

	i = 0;
	while (i < MAX_PROJECTILES && d->projectiles[i].is_active)
		i++;
	if (i == MAX_PROJECTILES)
		return ;
	if (!(new_projectile = malloc(sizeof(*new_projectile))))
	{
		ft_putendl_fd("malloc has failed\n", 2);
		exit(EXIT_FAILURE);
	}
	new_projectile->next = d->sectors[d->cursectnum].sprite_list;
	new_projectile->type = IS_PROJECTILE;
	new_projectile->id = i;
	set_projectile_id(d, i, id_of_proj_type);
	d->sectors[d->cursectnum].sprite_list = new_projectile;
}

void	set_projectile_id_monster(t_data *d, short i,
		short id_of_proj_type, t_monster *monster)
{
	d->projectiles[i].is_active = true;
	d->projectiles[i].id_type = id_of_proj_type;
	d->projectiles[i].pos = (t_vec3f){
		monster->pos.x,
		d->sectors[monster->cursectnum].floorheight + 0.8,
		monster->pos.y};
	d->projectiles[i].dir.z = sin(monster->rot) *
		d->projectile_type[id_of_proj_type].speed;
	d->projectiles[i].dir.y = (d->cam.pos.y -
			(d->sectors[monster->cursectnum].floorheight + 0.8)) /
		vec3f_length(sub_vec3f(d->projectiles[i].pos, d->cam.pos)) *
		d->projectile_type[id_of_proj_type].speed;
	d->projectiles[i].dir.x = cos(monster->rot) *
		d->projectile_type[id_of_proj_type].speed;
	d->projectiles[i].current_anim_playing =
		d->projectile_type[id_of_proj_type].anim_order[0];
	d->projectiles[i].has_collided = false;
	d->projectiles[i].weapon_id = d->monster_type[monster->id_type].id_of_proj;
	d->projectiles[i].cursectnum = monster->cursectnum;
	d->projectiles[i].time_remaining_anim = 5;
	d->projectiles[i].current_anim_playing = 0;
	d->projectiles[i].target = NULL;
}

void	create_projectile_monster(t_data *d, short id_of_proj_type,
		t_monster *monster)
{
	t_sprite_list	*new_projectile;
	short			i;

	i = 0;
	while (i < MAX_PROJECTILES && d->projectiles[i].is_active)
		i++;
	if (i == MAX_PROJECTILES)
		return ;
	if (!(new_projectile = malloc(sizeof(*new_projectile))))
	{
		ft_putendl_fd("malloc has failed\n", 2);
		exit(EXIT_FAILURE);
	}
	new_projectile->next = d->sectors[monster->cursectnum].sprite_list;
	new_projectile->type = IS_PROJECTILE;
	new_projectile->id = i;
	set_projectile_id_monster(d, i, id_of_proj_type, monster);
	d->sectors[monster->cursectnum].sprite_list = new_projectile;
}
