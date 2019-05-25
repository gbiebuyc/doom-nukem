/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ed_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikorale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 23:57:29 by mikorale          #+#    #+#             */
/*   Updated: 2019/05/14 23:57:29 by mikorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

// folder ammo, monster etc...

static int		load_assets(t_toolbar *tb, char **file, char **file32)
{
	int	*n;
	int	m;
	int	j;
	int	i;

	m = 0;
	i = 0;
	n = (int[3]){3, 5, 2};
	while (m < 3)
	{
		j = -1;
		while (++j < n[m])
		{
			if (!(tb->assets[m].assets[j] = SDL_LoadBMP(file[i])))
				return (ft_printf("Loading failed : %s\n", file[i]));
			if (!(tb->assets[m].assets_icon[j] = SDL_LoadBMP(file32[i])))
				return (ft_printf("Loading failed : %s\n", file32[i]));
			remove_backgorund_image(tb->assets[m].assets_icon[j]);
			i++;
		}
		m++;
	}
	return (0);
}

static int		init_assets(t_toolbar *tb)
{
	char	**file;
	char	**file32;

	file = (char*[]){"./Menu/ammo_energy.bmp", "./Menu/ammo_energy.bmp",
	"./Menu/ammo_energy.bmp", "./Menu/momDemon.bmp", "./Menu/momDemon.bmp",
	"./Menu/momDemon.bmp", "./Menu/momDemon.bmp", "./Menu/momDemon.bmp",
	"./Menu/healpack.bmp", "./Menu/healpack.bmp"};
	file32 = (char*[]){"./Menu/ammo_energy.bmp", "./Menu/ammo_energy.bmp",
	"./Menu/ammo_energy.bmp", "./Menu/momDemon32.bmp", "./Menu/momDemon32.bmp",
	"./Menu/momDemon32.bmp", "./Menu/momDemon32.bmp", "./Menu/momDemon32.bmp",
	"./Menu/healpack32.bmp", "./Menu/healpack32.bmp"};
	if (!(tb->player_start = SDL_LoadBMP("./Menu/playerstart.bmp")))
		return (ft_printf("Loading failed : playerstart"));
	remove_backgorund_image(tb->player_start);
	load_assets(tb, file, file32);
	return (0);
}

static int		init_toolbar(t_toolbar *tb)
{
	char	**file;
	int		i;
	int		j;

	file = (char*[]){
		"./Menu/Select_disable.bmp", "./Menu/Select_enable.bmp",
		"./Menu/Move_disable.bmp", "./Menu/Move_enable.bmp",
		"./Menu/sector_title.bmp", "./Menu/lblsector_info.bmp",
		"./Menu/wall_title.bmp", "./Menu/lblTexture.bmp",
		"./Menu/lblAmmo.bmp", "./Menu/lblMonsters.bmp",
		"./Menu/lblHealPack.bmp", "./Menu/lblPlayerStart.bmp",
		"./Menu/minus.bmp", "./Menu/plus.bmp"};
	i = -1;
	if (!(tb->select[0] = SDL_LoadBMP(file[++i])) ||
		!(tb->select[1] = SDL_LoadBMP(file[++i])) ||
		!(tb->move[0] = SDL_LoadBMP(file[++i])) ||
		!(tb->move[1] = SDL_LoadBMP(file[++i])))
		return (ft_printf("Failed to load %s\n", file[i]));
	j = -1;
	while (++j < 10)
		if (!(tb->properties[j] = SDL_LoadBMP(file[++i])))
			return (ft_printf("Failed to load %s\n", file[i]));
	return (0);
}

static int		init_interface(t_data *d)
{
	if (!(d->interface.menu = SDL_LoadBMP("./Menu/testmenu.bmp")))
		return (ft_printf("Error when creating escape menu.\n"));
	if (init_toolbar(&d->interface.toolbar) ||
		init_assets(&d->interface.toolbar))
		return (1);
	return (0);
}

// TODO init monster structure

int				init_editor(t_data *d)
{
	ft_memset(d, 0, sizeof(t_data));
	d->scale = W / 64;
	d->pos = (t_vec2f){0, 0};
	d->selectedwall = NULL;
	d->selectedwall2 = NULL;
	d->grid_locking = true;
	d->sectordrawing = false;
	d->interface.show_menu = 0;
	d->interface.select = 1;
	d->interface.move = 0;
	d->texture_to_scale = -1;
	d->interface.texture_case_select = -1;
	d->selected_texture = -2;
	d->interface.selection_cat_pos = -1;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS))
		return (ft_printf("Failed to init SDL.\n"));
	if (!(d->win = SDL_CreateWindow("editor", SDL_WINDOWPOS_CENTERED,
					SDL_WINDOWPOS_CENTERED, W, H, 0)))
		return (ft_printf("Failed to create editor's window.\n"));
	if (!(d->screen = SDL_GetWindowSurface(d->win)))
		return (ft_printf("Failed to get window's surface.\n"));
	if (init_interface(d) || init_texture(d))
		return (1);
	return (0);
}
