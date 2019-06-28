/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hud2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 02:47:04 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/06/28 17:13:02 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	draw_health(t_data *d)
{
	static char buf[100] = "Health: ";

	ft_strcpy(buf + 8, ft_itoa_static(d->player.health));
	draw_string(d, (t_font){buf, 50, 50, 0x0, 2});
}

void	draw_ammo(t_data *d, int ammo)
{
	static char buf[100] = "Ammo: ";

	ft_strcpy(buf + 6, ft_itoa_static(ammo));
	draw_string(d, (t_font){buf, 50, 80, 0x0, 2});
}

void	draw_fuel(t_data *d)
{
	static char buf[100] = "Fuel: ";

	ft_strcpy(buf + 6, ft_itoa_static(d->player.is_flying));
	draw_string(d, (t_font){buf, 50, 110, 0x0, 2});
}
