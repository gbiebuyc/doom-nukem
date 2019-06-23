/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ed_event_sector_options.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikorale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 23:20:18 by mikorale          #+#    #+#             */
/*   Updated: 2019/06/23 23:20:19 by mikorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	handle_checkbox(t_data *d, int x, int y, t_btn_option_p *p)
{
	t_sector	*s;

	s = &d->sectors[d->selected_sector];
	if (is_on_button(p->cbox_blinking, x, y))
		s->blinking = !s->blinking;
	else if (is_on_button(p->cbox_harmful, x, y))
		s->is_harmful = !s->is_harmful;
	else if (is_on_button(p->cbox_floor_animated, x, y))
		s->is_animatedslope = !s->is_animatedslope;
	else if (is_on_button(p->cbox_ceil_animated, x, y))
		s->is_animatedslopeceil = !s->is_animatedslopeceil;
}

void		event_sector_option_handler(t_data *d, int x, int y,
														t_btn_option_p *p)
{
	t_sector	*s;

	s = &d->sectors[d->selected_sector];
	handle_checkbox(d, x, y, p);
	if (is_on_button(p->btn_slopeceil_minus, x, y) && s->slopeceil > -20)
		s->slopeceil -= 1;
	else if (is_on_button(p->btn_slopeceil_plus, x, y) && s->slopeceil < 20)
		s->slopeceil += 1;
	else if (is_on_button(p->btn_slopeceil_orientation_minus, x, y))
		s->slopeceil_orientation -= 1;
	else if (is_on_button(p->btn_slopeceil_orientation_plus, x, y))
		s->slopeceil_orientation += 1;
	else if (is_on_button(p->btn_slopefloor_minus, x, y) && s->slope > -20)
		s->slope -= 1;
	else if (is_on_button(p->btn_slopefloor_plus, x, y) && s->slope < 20)
		s->slope += 1;
	else if (is_on_button(p->btn_slopefloor_orientation_minus, x, y))
		s->slope_orientation -= 1;
	else if (is_on_button(p->btn_slopefloor_orientation_plus, x, y))
		s->slope_orientation += 1;
}
