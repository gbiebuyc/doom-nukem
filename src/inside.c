/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inside.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 05:45:22 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/06/26 00:07:27 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

/*
**	Used to detect the current sector at each frame.
*/

bool	inside(t_data *d, int16_t sectnum, t_vec2f pos)
{
	int		n[5];
	t_vec2f	p0;
	t_vec2f	p1;

	n[0] = 0;
	n[1] = d->sectors[sectnum].numwalls;
	n[2] = 0;
	n[3] = n[1] - 1;
	while (n[2] < n[1])
	{
		p0 = d->walls[d->sectors[sectnum].firstwallnum + n[2]].point;
		p1 = d->walls[d->sectors[sectnum].firstwallnum + n[3]].point;
		if (((p0.y > pos.y) != (p1.y > pos.y)) &&
				(pos.x < (p1.x - p0.x) * (pos.y - p0.y) / (p1.y - p0.y) + p0.x))
			n[0] = !n[0];
		n[3] = n[2]++;
	}
	return (n[0]);
}

#define DIST_COLL_PROJ_CEIL_FLOOR 0.1

int16_t	update_cursect_proj(int16_t sect_to_scan, t_data *d, int depth,
		int16_t old_sect, t_vec3f pos)
{
	short	i;
	short	j;
	short	ret_value;

	if (inside(d, sect_to_scan, (t_vec2f){pos.x, pos.z}) &&
			(pos.y < get_ceilheight_point(d, sect_to_scan, vec3to2(pos)) +
			DIST_COLL_PROJ_CEIL_FLOOR || d->sectors[sect_to_scan].outdoor) &&
			pos.y > get_floorheight_point(d, sect_to_scan,
			vec3to2(pos)) + DIST_COLL_PROJ_CEIL_FLOOR)
		return (sect_to_scan);
	if (!depth)
		return (-1);
	i = d->sectors[sect_to_scan].firstwallnum - 1;
	j = d->sectors[sect_to_scan].firstwallnum +
		d->sectors[sect_to_scan].numwalls;
	while (++i < j)
		if (d->walls[i].neighborsect != -1 && d->walls[i].neighborsect !=
				old_sect && d->doorstate[i] > 0.7)
			if ((ret_value = update_cursect_proj(d->walls[i].neighborsect, d,
				depth - 1, sect_to_scan, pos)) != -1)
				return (ret_value);
	if (old_sect == -1 && d->sectors[sect_to_scan].outdoor &&
		pos.y > d->sectors[sect_to_scan].ceilheight + DIST_COLL_PROJ_CEIL_FLOOR)
		return (-2);
	return (-1);
}

void	set_tab(t_data *d, short sect_to_scan, short *tab, short old_sect)
{
	short	i;
	short	j;
	short	k;
	short	l;

	k = 0;
	while (tab[k] != -1)
		k++;
	i = d->sectors[sect_to_scan].firstwallnum;
	j = d->sectors[sect_to_scan].firstwallnum +
		d->sectors[sect_to_scan].numwalls;
	while (i < j)
	{
		if (d->walls[i].neighborsect != -1 &&
				d->walls[i].neighborsect != old_sect)
		{
			l = 0;
			while (tab[l] != -1)
			{
				if (tab[l] == d->walls[i].neighborsect)
					break ;
				l++;
			}
			if (tab[l] == -1)
			{
				tab[k] = d->walls[i].neighborsect;
				k++;
			}
		}
		i++;
	}
}

void	swap_tabs(short *tab, short *tmp_tab)
{
	short	i;

	i = 0;
	while (tmp_tab[i] != -1)
	{
		tab[i] = tmp_tab[i];
		tmp_tab[i] = -1;
		i++;
	}
	while (tab[i] != -1)
	{
		tab[i] = -1;
		i++;
	}
}

int16_t	update_cursect_player(t_data *d, short depth)
{
	short	i;
	short	tab[MAXNUMSECTORS];
	short	tmp_tab[MAXNUMSECTORS];

	ft_memset(tab, -1, sizeof(tab));
	ft_memset(tmp_tab, -1, sizeof(tmp_tab));
	tab[0] = d->cursectnum;
	while (depth)
	{
		i = 0;
		while (tab[i] != -1)
		{
			if (inside(d, tab[i], (t_vec2f){d->cam.pos.x, d->cam.pos.z}))
				return (tab[i]);
			set_tab(d, tab[i], &tmp_tab[0], tab[i]);
			i++;
		}
		swap_tabs(&tab[0], &tmp_tab[0]);
		depth--;
	}
	return (-1);
}
