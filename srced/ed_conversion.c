/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ed_conversion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikorale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 02:09:16 by mikorale          #+#    #+#             */
/*   Updated: 2019/05/17 02:09:16 by mikorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

t_vec2f	worldtoscreen(t_data *d, t_vec2f p)
{
	return ((t_vec2f){(p.x - d->pos.x) * d->scale + W / 2,
			-(p.y - d->pos.y) * d->scale + H / 2});
}

t_vec2f	screentoworld(t_data *d, t_vec2f p)
{
	return ((t_vec2f){(p.x - W / 2) / d->scale + d->pos.x,
			-(p.y - H / 2) / d->scale + d->pos.y});
}
