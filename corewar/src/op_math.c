/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajugnon <ajugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 22:06:34 by ajugnon           #+#    #+#             */
/*   Updated: 2019/04/16 10:22:03 by pcahier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		exec_add(t_vm *vm, t_process *p_c)
{
	int		value;

	value = p_c->reg[vm->arena[(p_c->pc + 2) % MEM_SIZE] - 1]
			+ p_c->reg[vm->arena[(p_c->pc + 3) % MEM_SIZE] - 1];
	if (verbose_print(vm, 4))
		ft_printf("P %9d | add r%d r%d r%d\n", p_c->nprocess
			, vm->arena[(p_c->pc + 2) % MEM_SIZE]
			, vm->arena[(p_c->pc + 3) % MEM_SIZE]
			, vm->arena[(p_c->pc + 4) % MEM_SIZE]);
	p_c->carry = value ? 0 : 1;
	p_c->reg[vm->arena[p_c->pc + 4] - 1] = value;
}

void			op_add(t_vm *vm, t_list *process)
{
	t_process	*p_c;

	p_c = (t_process *)process->content;
	if (check_arg_validity(3, (vm->arena[(p_c->pc + 1) % MEM_SIZE]), 3))
	{
		if ((vm->arena[(p_c->pc + 2) % MEM_SIZE] > 0
		&& vm->arena[(p_c->pc + 2) % MEM_SIZE] <= REG_NUMBER)
		&& (vm->arena[(p_c->pc + 3) % MEM_SIZE] > 0
		&& vm->arena[(p_c->pc + 3) % MEM_SIZE] <= REG_NUMBER)
		&& (vm->arena[(p_c->pc + 4) % MEM_SIZE] > 0
		&& vm->arena[(p_c->pc + 4) % MEM_SIZE] <= REG_NUMBER))
			exec_add(vm, p_c);
	}
	if (verbose_print(vm, 16))
		print_adv(vm, process
			, calc_shift((vm->arena[(p_c->pc + 1) % MEM_SIZE]), 4, 3));
	p_c->pc = (p_c->pc + calc_shift((vm->arena[(p_c->pc + 1) % MEM_SIZE])
		, 4, 3)) % MEM_SIZE;
}

static void		exec_sub(t_vm *vm, t_process *p_c)
{
	int		value;

	value = p_c->reg[vm->arena[(p_c->pc + 2) % MEM_SIZE] - 1]
			- p_c->reg[vm->arena[(p_c->pc + 3) % MEM_SIZE] - 1];
	if (verbose_print(vm, 4))
		ft_printf("P %9d | sub r%d r%d r%d\n", p_c->nprocess
			, vm->arena[(p_c->pc + 2) % MEM_SIZE]
			, vm->arena[(p_c->pc + 3) % MEM_SIZE]
			, vm->arena[(p_c->pc + 4) % MEM_SIZE]);
	p_c->carry = value ? 0 : 1;
	p_c->reg[vm->arena[(p_c->pc + 4) % MEM_SIZE] - 1] = value;
}

void			op_sub(t_vm *vm, t_list *process)
{
	t_process	*p_c;

	p_c = (t_process *)process->content;
	if (check_arg_validity(4, (vm->arena[(p_c->pc + 1) % MEM_SIZE]), 3))
	{
		if ((vm->arena[(p_c->pc + 2) % MEM_SIZE] > 0
		&& vm->arena[(p_c->pc + 2) % MEM_SIZE] <= REG_NUMBER)
		&& (vm->arena[(p_c->pc + 3) % MEM_SIZE] > 0
		&& vm->arena[(p_c->pc + 3) % MEM_SIZE] <= REG_NUMBER)
		&& (vm->arena[(p_c->pc + 4) % MEM_SIZE] > 0
		&& vm->arena[(p_c->pc + 4) % MEM_SIZE] <= REG_NUMBER))
			exec_sub(vm, p_c);
	}
	if (verbose_print(vm, 16))
		print_adv(vm, process, calc_shift((vm->arena[(p_c->pc + 1) % MEM_SIZE])
			, 4, 3));
	p_c->pc = (p_c->pc + calc_shift((vm->arena[(p_c->pc + 1) % MEM_SIZE])
		, 4, 3)) % MEM_SIZE;
}
