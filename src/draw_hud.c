/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hud.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 23:59:01 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/07/09 22:16:06 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

#define SLOT_W 64

void	draw_inventory_slot(t_data *d, SDL_Surface *tex, int x1, int y1)
{
	uint32_t	px;
	int			x;
	int			y;
	int			h;
	int			u;

	h = SLOT_W * (double)tex->h / tex->w;
	x = -1;
	while (++x < SLOT_W)
	{
		u = ((double)x / SLOT_W) * tex->w;
		y = -1;
		while (++y < h)
			if (((px = getpixel4(tex, u, (double)y / h)) >> 24) > 127)
				putpixel(d, x1 + x, y1 + y, px);
	}
}

void	draw_timed_msg(t_data *d)
{
	if (!d->msg[0])
		return ;
	draw_string(d, (t_font){d->msg, 50, HEIGHT - 180, 0xffffff, 4});
	if (SDL_GetTicks() - d->msg_start > 3000)
		d->msg[0] = 0;
}

void	draw_hud(t_data *d)
{
	if (d->slot1)
		draw_inventory_slot(d, d->assets_texture[d->slot1->picnum],
				40, HEIGHT - 100);
	if (d->slot2)
		draw_inventory_slot(d, d->assets_texture[d->slot2->picnum],
				140, HEIGHT - 100);
	if (d->slot3)
		draw_inventory_slot(d, d->assets_texture[d->slot3->picnum],
				240, HEIGHT - 100);
	draw_timed_msg(d);
	draw_health(d);
	draw_ammo(d, d->weapon_type[d->player.current_weapon]);
	if (d->player.is_flying)
		draw_fuel(d);
}
