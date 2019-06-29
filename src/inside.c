/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inside.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 05:45:22 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/06/29 14:22:31 by nallani          ###   ########.fr       */
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

int16_t	update_cursect_proj(int16_t sects[2], t_data *d, int depth,
		t_vec3f pos)
{
	short	i;
	short	j;
	short	ret_value;

	if (inside(d, sects[0], (t_vec2f){pos.x, pos.z}) &&
			(pos.y < get_ceilheight_point(d, sects[0], vec3to2(pos)) +
			DIST_COLL_PROJ_CEIL_FLOOR || d->sectors[sects[0]].outdoor) &&
			pos.y > get_floorheight_point(d, sects[0],
			vec3to2(pos)) + DIST_COLL_PROJ_CEIL_FLOOR)
		return (sects[0]);
	if (!depth)
		return (-1);
	i = d->sectors[sects[0]].firstwallnum - 1;
	j = d->sectors[sects[0]].firstwallnum +
		d->sectors[sects[0]].numwalls;
	while (++i < j)
		if (d->walls[i].neighborsect != -1 && d->walls[i].neighborsect !=
				sects[1] && d->doorstate[i] > 0.7)
			if ((ret_value = update_cursect_proj((int16_t[2]){d->walls[i].
							neighborsect, sects[0]}, d, depth - 1, pos)) != -1)
				return (ret_value);
	if (sects[1] == -1 && d->sectors[sects[0]].outdoor &&
			pos.y > d->sectors[sects[0]].ceilheight + DIST_COLL_PROJ_CEIL_FLOOR)
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
	i = d->sectors[sect_to_scan].firstwallnum - 1;
	j = d->sectors[sect_to_scan].firstwallnum +
		d->sectors[sect_to_scan].numwalls;
	while (++i < j)
		if (d->walls[i].neighborsect != -1 &&
				d->walls[i].neighborsect != old_sect)
		{
			l = -1;
			while (tab[++l] != -1)
				if (tab[l] == d->walls[i].neighborsect)
					break ;
			if (tab[l] == -1)
			{
				tab[k] = d->walls[i].neighborsect;
				k++;
			}
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

int16_t	update_cursect_smart(t_data *d, short depth, t_vec2f pos,
		uint16_t cursectnum)
{
	short	i;
	short	tab[MAXNUMSECTORS];
	short	tmp_tab[MAXNUMSECTORS];

	ft_memset(tab, -1, sizeof(tab));
	ft_memset(tmp_tab, -1, sizeof(tmp_tab));
	tab[0] = cursectnum;
	while (depth)
	{
		i = 0;
		while (tab[i] != -1)
		{
			if (inside(d, tab[i], pos))
				return (tab[i]);
			set_tab(d, tab[i], &tmp_tab[0], tab[i]);
			i++;
		}
		swap_tabs(&tab[0], &tmp_tab[0]);
		depth--;
	}
	return (-1);
}
