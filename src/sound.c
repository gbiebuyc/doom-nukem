/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 00:20:57 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/06/29 19:07:18 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	start_playing_sound(t_data *d, bool is_music)
{
	SDL_AudioDeviceID	dev;
	bool				playing;
	int					i;

	i = is_music ? d->musicnum : d->soundnum;
	if (i < 0)
		return ;
	if (!(dev = SDL_OpenAudioDevice(NULL, 0, &d->wav_spec[i], NULL, 0)))
		return ((void)ft_printf("Failed to open audio: %s\n", SDL_GetError()));
	playing = true;
	while (playing)
	{
		SDL_QueueAudio(dev, d->wav_buffer[i], d->wav_length[i]);
		SDL_PauseAudioDevice(dev, 0);
		while (SDL_GetQueuedAudioSize(dev) > 0)
		{
			if (is_music && d->musicnum != i)
				return ((void)SDL_CloseAudioDevice(dev));
			SDL_Delay(100);
		}
		playing = is_music;
	}
	SDL_CloseAudioDevice(dev);
}

void	*sound_thread(void *void_arg)
{
	t_sound_thread_arg	*arg;

	arg = (t_sound_thread_arg*)void_arg;
	start_playing_sound(arg->d, arg->is_music);
	return (NULL);
}

void	play_sound(t_data *d, uint8_t id)
{
	static t_sound_thread_arg	arg;
	pthread_t					thread;

	arg = (t_sound_thread_arg){d, .is_music = false};
	d->soundnum = id;
	if (pthread_create(&thread, NULL, sound_thread, &arg))
		ft_printf("pthread_create error\n");
	pthread_detach(thread);
}
