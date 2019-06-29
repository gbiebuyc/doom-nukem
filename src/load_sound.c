/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_sound.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 00:10:57 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/06/29 19:06:27 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int		load_sound2(t_data *d, int f)
{
	static int	i;

	if (read(f, &d->wav_spec[i], sizeof(d->wav_spec[i])) < 0)
		return (ft_printf("Failed to read wav spec.\n"));
	if (read(f, &d->wav_length[i], sizeof(d->wav_length[i])) < 0)
		return (ft_printf("Failed to read wav length.\n"));
	if (!(d->wav_buffer[i] = malloc(d->wav_length[i])))
		return (ft_printf("Failed to allocate wav buffer.\n"));
	if (read(f, d->wav_buffer[i], d->wav_length[i]) < 0)
		return (ft_printf("Failed to read wav buffer.\n"));
	i++;
	return (0);
}

int		load_sound(t_data *d, int f)
{
	if (d->wav_buffer[0])
		return (0);
	if (load_sound2(d, f) ||
			load_sound2(d, f) ||
			load_sound2(d, f) ||
			load_sound2(d, f) ||
			load_sound2(d, f) ||
			load_sound2(d, f) ||
			load_sound2(d, f) ||
			load_sound2(d, f) ||
			load_sound2(d, f) ||
			load_sound2(d, f) ||
			load_sound2(d, f) ||
			load_sound2(d, f) ||
			load_sound2(d, f) ||
			load_sound2(d, f))
			
		return (1);
	return (0);
}
