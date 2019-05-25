/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 00:57:43 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/05/05 11:18:43 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

#define SHADOWDIST 20

uint32_t	shade(double z, uint32_t c)
{
	double factor = 1 - norm(z, 0, SHADOWDIST);
	factor = fclamp(factor, 0, 1);
	return (((int)(((c >> 16) & 0xff) * factor) << 16) |
			((int)(((c >> 8) & 0xff) * factor) << 8) |
			((int)(((c >> 0) & 0xff) * factor) << 0));
}
