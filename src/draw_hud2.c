/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hud2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 02:47:04 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/07/09 22:19:40 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	draw_health(t_data *d)
{
	static char buf[100] = "Health: ";

	ft_strcpy(buf + 8, ft_itoa_static(d->player.health));
	draw_string(d, (t_font){buf, 50, 50, 0xffffff, 2});
}

void	draw_ammo(t_data *d, t_weapon_type weapon_type)
{
	static char buf[100] = "Ammo: ";

	ft_strcpy(buf + 6, ft_itoa_static(weapon_type.current_ammo));
	ft_strcpy(buf + ft_strlen(buf), " / ");
	ft_strcpy(buf + ft_strlen(buf), ft_itoa_static(weapon_type.max_ammo));
	draw_string(d, (t_font){buf, 50, 80, 0xffffff, 2});
}

void	draw_fuel(t_data *d)
{
	static char buf[100] = "Fuel: ";

	ft_strcpy(buf + 6, ft_itoa_static(d->player.is_flying));
	draw_string(d, (t_font){buf, 50, 110, 0xffffff, 2});
}
