/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajugnon <ajugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 22:06:34 by ajugnon           #+#    #+#             */
/*   Updated: 2019/03/12 22:40:25 by ajugnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		check_ctd(t_vm *vm)
{
	if (vm->ncycle_ctd == vm->cycle_to_die)
	{
		if (vm->nlive_ctd >= NBR_LIVE)
		{
			vm->cycle_to_die -= CYCLE_DELTA;
			if (verbose_print(vm, 2))
				ft_printf("Cycle to die is now %d\n", vm->cycle_to_die);
			vm->nb_check_dec_ctd = 0;
		}
		else
			vm->nb_check_dec_ctd++;
		if (vm->nb_check_dec_ctd >= MAX_CHECKS)
		{
			vm->cycle_to_die -= CYCLE_DELTA;
			if (verbose_print(vm, 2))
				ft_printf("Cycle to die is now %d\n", vm->cycle_to_die);
			vm->nb_check_dec_ctd = 0;
		}
		vm->ncycle_fctd = vm->ncycle;
		vm->nlive_ctd = 0;
		vm->ncycle_ctd = 0;
	}
	vm->ncycle++;
	vm->ncycle_ctd++;
}

void			vm_launch_game(t_vm *vm)
{
	while (vm->list_process)
	{
		if (vm->ncycle == vm->dump_value)
		{
			display_arena(vm);
			break ;
		}
		check_ctd(vm);
		if (vm->list_process)
		{
			browse_list_process(vm);
			if (vm->ncycle_ctd >= vm->cycle_to_die || vm->cycle_to_die < 0)
				kill_list_process(vm);
		}
	}
	if (vm->ncycle != vm->dump_value)
	{
		if (vm->last_player_id == -1)
			ft_printf("No contestant has won\n");
		else
			ft_printf("Contestant %u, \"%s\", has won !\n"
			, vm->list_player[vm->last_player_id].number
			, vm->list_player[vm->last_player_id].name);
	}
}
