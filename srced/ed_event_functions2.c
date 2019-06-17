#include "editor.h"

void	fix_default_texture(t_data *d, int x, int y)
{
	int	texture_i;

	texture_i = ((x - (W - TEXTURE_TOOLBAR + 10)) >> 6) + ((y - 10) >> 6) * 4;
	if (texture_i >= d->nb_texture)
		texture_i = d->default_texture;
	if (d->selected_wall == -1 && d->interface.texture_case_select == 2)
		d->default_wall_texture = texture_i;
	if (d->selected_sector == -1 && d->interface.texture_case_select == 1)
		d->default_ceil_texture = texture_i;
	if (d->selected_sector == -1 && d->interface.texture_case_select == 0)
		d->default_floor_texture = texture_i;
}