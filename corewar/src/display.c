/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajugnon <ajugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 22:06:34 by ajugnon           #+#    #+#             */
/*   Updated: 2019/03/12 22:40:25 by pcahier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	display_arena(t_vm *vm)
{
	int i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (i % vm->width == 0 && i != 0)
			ft_printf(" \n");
		if (i % vm->width == 0 && i != (MEM_SIZE - 1))
			ft_printf("0x%04x :", i);
		if (i % 1 == 0)
			ft_printf(" ");
		ft_printf("%02x", vm->arena[i]);
		i++;
	}
	ft_printf(" \n");
	vm->cycle_to_die = -1;
	kill_list_process(vm);
}

int		verbose_print(t_vm *vm, int verbosity)
{
	int ret;

	ret = 0;
	if (vm->verbose_val & verbosity)
		ret = 1;
	return (ret);
}

void	print_adv(t_vm *vm, t_list *process, int shift)
{
	t_process	*p_c;
	int			i;

	i = -1;
	p_c = (t_process *)process->content;
	ft_printf("ADV %d (0x%04x -> 0x%04x) ", shift, p_c->pc, p_c->pc + shift);
	while (++i < shift)
		ft_printf("%02x ", vm->arena[(p_c->pc + i) % MEM_SIZE]);
	ft_printf("\n");
}

void	ft_print_intro(t_vm *vm)
{
	int		i;

	i = 0;
	ft_printf("Welcome to corewar arena, today our %d champions are :\n",
		vm->nplayer);
	while (i < vm->nplayer)
	{
		ft_printf("number %u, with a weight of %u.\n%s !\nA word ? \"%s\"\n\n",
			vm->list_player[i].number, vm->list_player[i].code_length,
				vm->list_player[i].name, vm->list_player[i].comment);
		i++;
	}
	ft_printf("And now, let the deathmatch begin !\n");
}
