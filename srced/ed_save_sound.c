/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ed_write_sound.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 23:55:56 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/06/18 23:55:56 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int		write_sound2(t_data *d, int f, char *path, SDL_AudioFormat format)
{
	SDL_AudioSpec		wav_spec;
	Uint32				wav_length;
	Uint8				*wav_buffer;

	(void)d;
	ft_memset(&wav_spec, 0, sizeof(wav_spec));
	wav_spec.freq = 44100;
	wav_spec.format = format;
	wav_spec.channels = 1;
	wav_spec.samples = 4096;
	if (SDL_LoadWAV(path, &wav_spec, &wav_buffer, &wav_length) == NULL)
		return (ft_printf("Could not open wav file: %s\n", SDL_GetError()));
	if (write(f, &wav_spec, sizeof(wav_spec)) < 0)
		return (ft_printf("Failed to write wav spec.\n"));
	if (write(f, &wav_length, sizeof(wav_length)) < 0)
		return (ft_printf("Failed to write wav length.\n"));
	if (write(f, wav_buffer, wav_length) < 0)
		return (ft_printf("Failed to write wav buffer.\n"));
	SDL_FreeWAV(wav_buffer);
	return (0);
}

int		write_sound(t_data *d, int f)
{
	if (write_sound2(d, f, "sounds/music.wav", AUDIO_S16LSB) ||
			write_sound2(d, f, "sounds/shoot.wav", AUDIO_S16LSB))
		return (1);
	return (0);
}
