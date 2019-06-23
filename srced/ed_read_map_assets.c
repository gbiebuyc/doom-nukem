#include "editor.h"

static void	fill_list(t_data *d, t_interface *itf)
{
	int		i;
	int		s;

	s = -1;
	while (++s < d->numsectors)
	{
		i = -1;
		while (++i < d->assets[s][0].nb_assets)
		{
			itf->selected_asset = d->assets[s][i].picnum;
			add_assets_to_list(d, &d->assets[s][i].world_pos, s, itf);
			itf->assets_list->is_on_floor = d->assets[s][i].is_on_floor;
			itf->assets_list->is_on_ceil = d->assets[s][i].is_on_ceil;
			itf->assets_list->is_interactive = d->assets[s][i].is_interactive;
			itf->assets_list->is_autopick = d->assets[s][i].is_autopick;
			itf->assets_list->collision = d->assets[s][i].collision;
			itf->assets_list->stat_mod = d->assets[s][i].stat_mod;
		}
	}
}

int			read_assets_data(t_data *d, int f)
{
	int	i;
	int	s;

	if (read(f, &d->nb_assets, sizeof(int16_t)) < 0)
		return (ft_printf("Failed to read map nb_assets.\n"));
	if (!(d->assets = (t_assets**)malloc(sizeof(t_assets*) * d->numsectors)))
			return (ft_printf("Failed to malloc assets structures.\n"));
	if (d->nb_assets > 0)
	{
		s = -1;
		while (++s < d->numsectors)
		{
			if (!(d->assets[s] = (t_assets*)malloc(sizeof(t_assets) * 10)))
				return (ft_printf("Failed to malloc assets structures.\n"));
			if (read(f, &d->assets[s][0].nb_assets, sizeof(int)) < 0)
				return (ft_printf("Failed to read nb_assets for sector.\n"));
			i = -1;
			while (++i < d->assets[s][0].nb_assets)
				if (read(f, &d->assets[s][i], sizeof(t_assets)) < 0)
					return (ft_printf("Failed to read d->asset[][].\n"));
		}
		fill_list(d, &d->interface);
	}
	return (0);
}
