/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ed_editor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikorale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 20:09:28 by mikorale          #+#    #+#             */
/*   Updated: 2019/05/16 20:09:29 by mikorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	change_ceil_height(t_data *d, double val, int16_t sectnum)
{
	if (sectnum < 0)
		return ;
	d->sectors[sectnum].ceilheight += val;
	ft_printf("Sector %d ceil H = %f\n", sectnum,
										d->sectors[sectnum].ceilheight);
}

void	change_floor_height(t_data *d, double val, int16_t sectnum)
{
	if (sectnum < 0)
		return ;
	d->sectors[sectnum].floorheight += val;
	ft_printf("Sector %d floor H = %f\n", sectnum,
										d->sectors[sectnum].floorheight);
}

void	cancel_last_wall(t_data *d)
{
	t_sector	*sect;

	if (!d->sectordrawing)
		return ;
	sect = &d->sectors[d->numsectors - 1];
	sect->numwalls--;
	d->numwalls--;
	if (sect->numwalls >= 2)
	{
		d->selectedwall--;
		update_wall_pos(d);
	}
	else
	{
		d->numwalls--;
		d->numsectors--;
		d->selectedwall = NULL;
		d->sectordrawing = false;
	}
}

int16_t	in_which_sector_is_this_wall(t_data *d, t_wall *wall)
{
	int	s;
	int	w;

	s = -1;
	while (++s < d->numsectors)
	{
		w = wall - d->walls;
		if (d->sectors[s].firstwallnum > w)
			break ;
	}
	return (s - 1);
}

void	update_pos(t_data *d, SDL_Event *e)
{
	int	x;
	int	y;

	x = e->motion.xrel;
	y = e->motion.yrel;
	d->pos.x -= (x * 0.04);
	d->pos.y += (y * 0.04);
}
