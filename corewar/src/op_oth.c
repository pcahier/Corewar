/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_oth.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajugnon <ajugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 22:06:34 by ajugnon           #+#    #+#             */
/*   Updated: 2019/03/12 22:40:25 by ajugnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	op_aff(t_vm *vm, t_list *process)
{
	t_process	*p_c;

	p_c = (t_process *)process->content;
	if (ocp1((vm->arena[(p_c->pc + 1) % MEM_SIZE])) == 1
		&& vm->arena[(p_c->pc + 2) % MEM_SIZE] >= 1
			&& vm->arena[(p_c->pc + 2) % MEM_SIZE] <= REG_NUMBER)
		ft_printf("Aff: %c\n"
			, (t_uc)p_c->reg[vm->arena[(p_c->pc + 2) % MEM_SIZE] - 1]);
	if (verbose_print(vm, 16))
		print_adv(vm, process, calc_shift((vm->arena[(p_c->pc + 1) % MEM_SIZE])
			, 4, 1));
	p_c->pc = (p_c->pc + calc_shift((vm->arena[(p_c->pc + 1) % MEM_SIZE])
		, 4, 1)) % MEM_SIZE;
}

void	op_live(t_vm *vm, t_list *process)
{
	int			num_p;
	int			id_p;
	t_process	*p_c;

	p_c = (t_process *)process->content;
	num_p = reverse_bytes(vm, p_c->pc + 1, 4);
	id_p = search_id_player(vm, num_p);
	if (id_p >= 0 && id_p < vm->nplayer)
	{
		vm->last_player_id = id_p;
		if (!verbose_print(vm, 1))
			ft_printf("Player %u (%s) is said to be alive\n", num_p
			, vm->list_player[id_p].name);
	}
	if (verbose_print(vm, 4))
		ft_printf("P %9d | live %u\n", p_c->nprocess, num_p);
	if (verbose_print(vm, 16))
		print_adv(vm, process, 5);
	p_c->pc = (p_c->pc + 5) % MEM_SIZE;
	p_c->llc = vm->ncycle;
	vm->nlive_ctd++;
}

void	op_fork(t_vm *vm, t_list *process)
{
	int			new_pc;
	t_process	*p_c;

	p_c = (t_process *)process->content;
	new_pc = reverse_bytes(vm, p_c->pc + 1, 2);
	process_creation(vm, process
		, (unsigned int)((p_c->pc + (new_pc % IDX_MOD)) % MEM_SIZE));
	if (verbose_print(vm, 4))
		ft_printf("P %9d | fork %d (%d)\n", p_c->nprocess, new_pc
		, p_c->pc + (new_pc % IDX_MOD));
	if (verbose_print(vm, 16))
		print_adv(vm, process, 3);
	p_c->pc = (p_c->pc + 3) % MEM_SIZE;
}

void	op_lfork(t_vm *vm, t_list *process)
{
	int			new_pc;
	t_process	*p_c;

	p_c = (t_process *)process->content;
	new_pc = reverse_bytes(vm, p_c->pc + 1, 2);
	if (verbose_print(vm, 4))
		ft_printf("P %9d | lfork %d (%d)\n"
			, p_c->nprocess, new_pc, p_c->pc + new_pc);
	process_creation(vm, process, (unsigned int)(p_c->pc + new_pc) % MEM_SIZE);
	if (verbose_print(vm, 16))
		print_adv(vm, process, 3);
	p_c->pc = (p_c->pc + 3) % MEM_SIZE;
}

void	op_zjmp(t_vm *vm, t_list *process)
{
	int			address;
	t_process	*p_c;

	p_c = (t_process *)process->content;
	address = reverse_bytes(vm, p_c->pc + 1, 2) % IDX_MOD;
	if (verbose_print(vm, 4))
		ft_printf("P %9d | zjmp %d %s\n", p_c->nprocess, address
		, p_c->carry ? "OK" : "FAILED");
	p_c->pc = p_c->carry == 1 ? (p_c->pc + address) % MEM_SIZE
								: (p_c->pc + 3) % MEM_SIZE;
}
