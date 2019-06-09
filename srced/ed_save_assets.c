#include "editor.h"

void	clear_list(t_data *d)
{
	if (!d->monsters)
		return ;
	free(d->monsters);
	d->monsters = NULL;
}

int		fill_monster_structure(t_data *d)
{
	t_monster_list	*lst;
	int				i;

	clear_list(d);
	if (d->nbmonsters <= 0)
		return (0);
	if (!(d->monsters = (t_monster*)malloc(sizeof(t_monster) * d->nbmonsters)))
		return (ft_printf("Failed to malloc monsters structure.\n"));
	lst = d->interface.monster_list->begin;
	i = 0;
	while (lst)
	{
		d->monsters[i] = (t_monster){lst->pos, 0, 0, 0, lst->sectnunm, 0,
									0, 0, 0, 0, 0, 0, 0, 0, 1};
		lst = lst->next;
		i++;
	}
	return (0);
}

int		write_monster_list(t_data *d, int f)
{
	int	i;

	if (write(f, &d->nbmonsters, sizeof(uint16_t)) < 0)
		return (ft_printf("Failed to write nummonsters\n"));
	if (d->nbmonsters > 0)
	{
		fill_monster_structure(d);
		i = -1;
		while (++i < d->nbmonsters)
			 if (write(f, &d->monsters[i], sizeof(t_monster)) < 0)
			 	return (ft_printf("Failed to write monsters\n"));
		/*	if (write(f, &d->monsters[i].pos, sizeof(t_vec2f)) < 0 ||
				write(f, &d->monsters[i].size, sizeof(double)) < 0 ||
				write(f, &d->monsters[i].health_mult, sizeof(double)) < 0 ||
				write(f, &d->monsters[i].rot, sizeof(double)) < 0 ||
				write(f, &d->monsters[i].cursectnum, sizeof(int16_t)) < 0 ||
				write(f, &d->monsters[i].id_type, sizeof(uint8_t)) < 0 ||
				write(f, &d->monsters[i].anim_state, sizeof(uint8_t)) < 0 ||
				write(f, &d->monsters[i].anim_time, sizeof(uint8_t)) < 0 ||
				write(f, &d->monsters[i].behaviour, sizeof(uint8_t)) < 0 ||
				write(f, &d->monsters[i].timer, sizeof(uint8_t)) < 0 ||
				write(f, &d->monsters[i].life, sizeof(int16_t)) < 0 ||
				write(f, &d->monsters[i].height, sizeof(double)) < 0 ||
				write(f, &d->monsters[i].width, sizeof(double)) < 0 ||
				write(f, &d->monsters[i].can_collide, sizeof(bool)) < 0 ||
				write(f, &d->monsters[i].activated, sizeof(bool)) < 0)
				return (ft_printf("Failed to write monsters\n"));*/
	}

/*
	if (write(f, &d->nbmonsters, sizeof(uint16_t)) < 0)
		return (ft_printf("Failed to write nummonsters\n"));
	if (write(f, &d->monsters, sizeof(d->monsters)) < 0)
		return (ft_printf("Failed to write monsters\n"));*/
	return (0);
}