/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ed_event_functions2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikorale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 16:51:42 by mikorale          #+#    #+#             */
/*   Updated: 2019/06/18 16:51:43 by mikorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		fix_default_texture(t_data *d, int x, int y)
{
	int	textur_i;

	if (x >= (W - TEXTURE_TOOLBAR + 6) && x < W - PROPERTIES_LIMIT - 6)
	{
		textur_i = ((x - W - TEXTURE_TOOLBAR + 10) >> 6) + ((y - 10) >> 6) * 4;
		if (textur_i >= d->nb_texture)
			textur_i = d->default_texture;
		if (d->selected_wall == -1 && !d->hl_wall
									&& d->interface.texture_case_select == 2)
			d->default_wall_texture = textur_i;
		if (d->selected_sector == -1 && d->interface.texture_case_select == 1)
			d->default_ceil_texture = textur_i;
		if (d->selected_sector == -1 && d->interface.texture_case_select == 0)
			d->default_floor_texture = textur_i;
	}
}

static void	save_sector_texture(t_data *d, t_sector *s)
{
	if (d->interface.texture_case_select == 1)
		s->ceilpicnum = d->selected_texture;
	else if (d->interface.texture_case_select == 0)
		s->floorpicnum = d->selected_texture;
}

void		save_selected_texture(t_data *d, int x, int y, int wallnum)
{
	t_sector	*s;

	s = &d->sectors[d->selected_sector];
	if (x >= (W - TEXTURE_TOOLBAR + 6) && x < W - PROPERTIES_LIMIT - 6)
	{
		x = (x - (W - TEXTURE_TOOLBAR + MARGIN)) >> 6;
		y = (y - MARGIN) >> 6;
		d->selected_texture = x + y * 4;
		if (d->selected_texture < d->nb_texture ||
			d->interface.texture_case_select == 3)
		{
			if (d->interface.texture_case_select == 2 && wallnum >= 0)
				d->walls[wallnum].middlepicnum = d->selected_texture;
			else if (d->interface.texture_case_select == 3)
				d->walls[wallnum].posterpicnum =
										(d->selected_texture < d->nb_posters)
										? d->selected_texture : -1;
			else if (d->selected_sector >= 0)
				save_sector_texture(d, s);
		}
		else
			d->selected_texture = -1;
	}
	else
		d->selected_texture = -2;
}
