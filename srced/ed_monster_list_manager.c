#include "editor.h"

t_monster_list	*new_monster(char *name, t_vec2f *p, int sectnum,
											t_monster_list *prev)
{
	t_monster_list	*monster;

	if (!(monster = (t_monster_list*)malloc(sizeof(t_monster_list))))
		return (NULL);
	monster->name = name;
	monster->pos = *p;
	monster->sectnunm = sectnum;
	monster->prev = prev;
	monster->next = NULL;
	return (monster);
}

void	add_monster_to_list(t_data *d, t_vec2f *xy, int sectnum)
{
	ft_printf("%d\n", d->interface.selected_asset);
	int cat;
	int selected_asset;

	cat = d->interface.selected_asset_cat;
	selected_asset = d->interface.selected_asset;
//	d->interface.toolbar.assets[cat].assets[3selected_asset]*/
	/**************/
	char			*name;

	name = d->assets_data[d->interface.nb_asset[0] + selected_asset].name;
	if (!d->interface.monster_list)
	{
		d->interface.monster_list = new_monster(name, xy, sectnum, NULL);
		d->interface.monster_list->begin = d->interface.monster_list;
	}
	else
	{
		d->interface.monster_list->next = new_monster(name, xy, sectnum, NULL);
		d->interface.monster_list->next->begin = d->interface.monster_list->begin;
		d->interface.monster_list = d->interface.monster_list->next;
	}
	ft_printf("%s\n", d->interface.monster_list->name);
}