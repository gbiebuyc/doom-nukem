/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 00:20:57 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/06/19 00:20:57 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	play_sound(t_data *d, bool loop, int i)
{
	SDL_AudioDeviceID	dev;
	bool				playing;

	if (!(dev = SDL_OpenAudioDevice(NULL, 0, &d->wav_spec[i], NULL, 0)))
		return ((void)ft_printf("Failed to open audio: %s\n", SDL_GetError()));
	playing = true;
	while (playing)
	{
		SDL_QueueAudio(dev, d->wav_buffer[i], d->wav_length[i]);
		SDL_PauseAudioDevice(dev, 0);
		while (SDL_GetQueuedAudioSize(dev) > 0)
			;
		playing = loop;
	}
	SDL_CloseAudioDevice(dev);
}

void	*sound_thread(void *void_arg)
{
	t_sound_thread_arg	*arg;

	arg = (t_sound_thread_arg*)void_arg;
	play_sound(arg->d, arg->loop, arg->soundnum);
	return (NULL);
}
