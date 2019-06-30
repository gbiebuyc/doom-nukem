/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 00:20:57 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/06/30 14:20:06 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"
/*
void	start_playing_sound(t_data *d, bool is_music, uint8_t id)
{
	SDL_AudioDeviceID	dev;
	bool				playing;
	int					i;

	i = is_music ? d->musicnum : id;
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
*/
void	*sound_thread(void *void_arg)
{
	t_sound_thread_arg	*arg;

	arg = (t_sound_thread_arg*)void_arg;
//	start_playing_sound(arg->d, arg->is_music, arg->id);
	if (!arg->is_music)
		free(void_arg);
	return (0);
}

void	play_sound(t_data *d, uint8_t id, t_vec2f pos)
{
	static uint8_t	i;
	char			path[50];
	Mix_Chunk		*sample;
	int16_t			angle;
	uint8_t			dist;
	t_vec2f			tmp;


	if (pos.x == d->cam.pos.x)
		angle = 0;
	else
	{
		pos = sub_vec2f(pos, vec3to2(d->cam.pos));
		actualize_dir(d->cam.rot, &pos);
		angle = -atan2(pos.y, pos.x) * 180 / M_PI + 90;
	}
	dist = ft_min(vec2f_length(sub_vec2f(vec3to2(d->cam.pos), pos)), 254);
//	if (id == M16_SOUND)
//		ft_strcpy(path,  "sounds/m16.wav");
//	else if (id == BLASTER_SOUND)
//		ft_strcpy(path, "sounds/blaster.wav");
//	else if (id == CRYO_SOUND)
//		ft_strcpy(path, "sounds/cryo_bal.wav");
//	else if (id == EXPLOSION_SOUND)
//		ft_strcpy(path, "sounds/explosion.wav");
//	else if (id == PLAYER_FELL_SOUND)
//		ft_strcpy(path, "sounds/player_fell.wav");
//	else if (id == PLAYER_GOT_HIT_SOUND)
//		ft_strcpy(path, "sounds/player_got_hit.wav");
//	else if (id == PLAYER_DEATH_SOUND)
//		ft_strcpy(path, "sounds/player_death.wav");
//	else if (id == CHARG_ATK_SOUND)
//		ft_strcpy(path, "sounds/charg_damage.wav");
//	else if (id == CHARG_DEATH_SOUND)
//		ft_strcpy(path, "sounds/charg_death.wav");
//	else if (id == MOTHER_DEATH_SOUND)
//		ft_strcpy(path, "sounds/mother_death.wav");
//	else if (id == MOTHER_ATK_SOUND)
//		ft_strcpy(path, "sounds/mother_attack.wav");
//	else if (id == CHARG_AGRO_SOUND)
//		ft_strcpy(path, "sounds/charg_agro.wav");
//	else if (id == MOTHER_AGRO_SOUND)
//		ft_strcpy(path, "sounds/mother_agro.wav");
//	else if (id == BLASTER_2_SOUND)
//		ft_strcpy(path, "sounds/blaster_2.wav");
//	else
//		return ;
	//if (!(sample = Mix_LoadWAV(path)))
	//	printf("error no sample");
	Mix_PlayChannel(i, &d->chunk[id], 0);
	Mix_SetPosition(i, angle, dist);
	if (++i > 100)
		i = 0;
}

/*
   void	play_sound(t_data *d, uint8_t id)
   {
   t_sound_thread_arg	*arg;
   SDL_Thread			*thread;

   if (!(arg = malloc(sizeof(t_sound_thread_arg))))
   {
   ft_printf("malloc sound failed\n");
   exit(EXIT_FAILURE);
   }
   arg->d = d;
   arg->is_music = false;
   arg->id = id;
   if (!(thread = SDL_CreateThread(sound_thread,"shit boy", arg)))
   {
   ft_printf(SDL_GetError());
   return ;
   }
   SDL_DetachThread(thread);

//	if (pthread_create(&thread, NULL, sound_thread, arg))
//	{
//		ft_printf("pthread_create error\n");
//		free(arg);
//		return ;
//	}
//	if (pthread_detach(thread))
//	{
//		ft_printf("pthread_deatch error\n");
//		pthread_kill(thread, 0);
//	}
}
*/
