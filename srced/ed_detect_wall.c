/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ed_detect_wall.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 17:38:31 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/06/14 18:54:46 by mikorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int		calc_closest_and_distance(t_data *d, int w1, t_vec2f *p,
															t_vec2f closest)
{
	double	dx;
	double	dy;
	double	dist;
	int		selected_sector;

	dx = p->x - closest.x;
	dy = p->y - closest.y;
	dist = vec2f_length((t_vec2f){dx, dy});
	selected_sector = find_sect_under_cursor(d);
	selected_sector = (selected_sector == -1) ? 0 : selected_sector;
	if (dist < 15 && w1 >= d->sectors[selected_sector].firstwallnum)
		return (1);
	return (0);
}

int		is_on_wall(t_data *d, int w1, t_vec2f *ab, t_vec2f *p)
{
	t_vec2f a_to_p;
	t_vec2f	a_to_b;
	double	atb2;
	double	atp_dot_atb;
	double	t;

	a_to_p = (t_vec2f){p->x - ab[0].x, p->y - ab[0].y};
	a_to_b = (t_vec2f){ab[1].x - ab[0].x, ab[1].y - ab[0].y};
	atb2 = a_to_b.x * a_to_b.x + a_to_b.y * a_to_b.y;
	atp_dot_atb = a_to_p.x * a_to_b.x + a_to_p.y * a_to_b.y;
	t = atp_dot_atb / atb2;
	t = fclamp(t, 0, 1);
	if (calc_closest_and_distance(d, w1, p,
		(t_vec2f){ab[0].x + t * a_to_b.x, ab[0].y + t * a_to_b.y}))
		return (1);
	return (0);
}

int		search_wall(t_data *d, int x, int y)
{
	int16_t	s;
	int16_t	w1;
	int16_t	w2;
	int16_t	last;

	s = -1;
	while (++s < d->numsectors)
	{
		last = d->sectors[s].firstwallnum + d->sectors[s].numwalls;
		w1 = last - 1;
		w2 = d->sectors[s].firstwallnum;
		while (w2 < last)
		{
			if (is_on_wall(d, w1,
				(t_vec2f[2]){worldtoscreen(d, d->walls[w1].point),
				worldtoscreen(d, d->walls[w2].point)}, &(t_vec2f){x, y}))
				return (w1);
			w1 = w2++;
		}
	}
	return (-1);
}

void	detect_wall(t_data *d, int x, int y)
{
	d->hl_wallnum_draw = search_wall(d, x, y);
}

void	detect_select_wall(t_data *d, int x, int y)
{
	d->hl_wallnum = search_wall(d, x, y);
	if (d->hl_wallnum != -1)
	{
		d->hl_wall = &d->walls[d->hl_wallnum];
		ft_printf("[Selected wall] = %d\n", d->hl_wallnum);
	}
}
