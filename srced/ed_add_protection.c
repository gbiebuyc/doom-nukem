/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ed_add_protection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/06 10:24:18 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/07/06 10:24:18 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

/*
**	Protection for max walls and sectors
*/

void		add_wall(t_data *d)
{
	if (d->numwalls < MAXNUMWALLS)
		add_wall2(d);
	else
		ft_printf("Too much walls already.\n");
}

void		add_sector(t_data *d)
{
	if (d->numsectors < MAXNUMSECTORS)
		add_sector2(d);
	else
		ft_printf("Too much sectors already.\n");
}
