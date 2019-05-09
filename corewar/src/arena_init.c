/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajugnon <ajugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 22:06:34 by ajugnon           #+#    #+#             */
/*   Updated: 2019/03/12 22:40:25 by ajugnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		load_players(t_vm *vm)
{
	int		distance;
	int		num_player;
	int		mem_address;

	distance = MEM_SIZE / vm->nplayer;
	vm->last_player_id = 0;
	num_player = 0;
	mem_address = 0;
	while (num_player < vm->nplayer)
	{
		vm->list_player[num_player].start_address = mem_address;
		ft_memcpy(&(vm->arena[mem_address]), vm->list_player[num_player].code
		, vm->list_player[num_player].code_length);
		mem_address += distance;
		num_player++;
	}
}

static void		generate_processes(t_vm *vm)
{
	t_process	process;
	int			num_player;
	t_list		*lst;

	num_player = 0;
	while (num_player < vm->nplayer)
	{
		process.nprocess = num_player + 1;
		vm->nprocess++;
		ft_memset(&process.reg, 0, (REG_NUMBER) * sizeof(int));
		process.reg[0] = vm->list_player[num_player].number;
		process.pc = vm->list_player[num_player].start_address;
		process.carry = 0;
		process.llc = -1;
		process.next_op = -1;
		process.op_exec = 0;
		if ((lst = ft_lstnew(&process, sizeof(t_process))) == NULL)
		{
			ft_dprintf(2, "corewar: %s\n", strerror(errno));
			kill_list_process(vm);
			exit(1);
		}
		ft_lstadd(&(vm->list_process), lst);
		num_player++;
	}
}

void			vm_generate_arena(t_vm *vm)
{
	load_players(vm);
	generate_processes(vm);
}
