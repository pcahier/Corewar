/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajugnon <ajugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 22:06:34 by ajugnon           #+#    #+#             */
/*   Updated: 2019/03/12 22:40:25 by ajugnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	exec_ld(t_vm *vm, t_process *p_c)
{
	int		emp_reg;
	int		val_param;

	emp_reg = vm->arena[(p_c->pc
		+ 6 - (((vm->arena[(p_c->pc + 1) % MEM_SIZE]) & 0x60) >> 5))
		% MEM_SIZE];
	if (emp_reg > 0 && emp_reg <= REG_NUMBER)
	{
		if (ocp1((vm->arena[(p_c->pc + 1) % MEM_SIZE])) == 2)
			val_param = reverse_bytes(vm, p_c->pc + 2, 4);
		else
		{
			val_param = reverse_bytes(vm, p_c->pc + 2, 2) % IDX_MOD;
			val_param = reverse_bytes(vm, p_c->pc + val_param, 4);
		}
		p_c->reg[emp_reg - 1] = val_param;
		if (verbose_print(vm, 4))
			ft_printf("P %9d | ld %d r%d\n", p_c->nprocess, val_param, emp_reg);
		p_c->carry = val_param ? 0 : 1;
	}
}

void		op_ld(t_vm *vm, t_list *process)
{
	t_process	*p_c;

	p_c = (t_process *)process->content;
	if (ocp2(vm->arena[(p_c->pc + 1) % MEM_SIZE]) == 1
		&& (ocp1(vm->arena[(p_c->pc + 1) % MEM_SIZE]) == 2
		|| ocp1(vm->arena[(p_c->pc + 1) % MEM_SIZE]) == 3))
		exec_ld(vm, p_c);
	if (verbose_print(vm, 16))
		print_adv(vm, process
			, calc_shift((vm->arena[(p_c->pc + 1) % MEM_SIZE]), 4, 2));
	p_c->pc = (p_c->pc
		+ calc_shift((vm->arena[(p_c->pc + 1) % MEM_SIZE]), 4, 2)) % MEM_SIZE;
}

static int	exec_lld(t_vm *vm, t_process *p_c)
{
	int		emp_reg;
	int		val_pa;

	emp_reg = vm->arena[(p_c->pc
		+ 6 - (((vm->arena[(p_c->pc + 1) % MEM_SIZE]) & 0x60) >> 5))
		% MEM_SIZE];
	if (emp_reg > 0 && emp_reg <= REG_NUMBER)
	{
		if (ocp1((vm->arena[(p_c->pc + 1) % MEM_SIZE])) == 2)
			val_pa = reverse_bytes(vm, p_c->pc + 2, 4);
		else
		{
			val_pa = reverse_bytes(vm, p_c->pc + 2, 2);
			val_pa = reverse_bytes(vm, p_c->pc + val_pa, 4);
		}
		p_c->reg[emp_reg - 1] = val_pa;
		if (verbose_print(vm, 4))
			ft_printf("P %9d | lld %d r%d\n", p_c->nprocess, val_pa, emp_reg);
		p_c->carry = val_pa ? 0 : 1;
	}
	return (emp_reg);
}

void		op_lld(t_vm *vm, t_list *process)
{
	t_process	*p_c;
	int			emp_reg;

	emp_reg = 0;
	p_c = (t_process *)process->content;
	if (ocp2((vm->arena[(p_c->pc + 1) % MEM_SIZE])) == 1
		&& (ocp1((vm->arena[(p_c->pc + 1) % MEM_SIZE])) == 2
			|| ocp1((vm->arena[(p_c->pc + 1) % MEM_SIZE])) == 3))
		emp_reg = exec_lld(vm, p_c);
	if (verbose_print(vm, 16))
		print_adv(vm, process, emp_reg + 1);
	p_c->pc = (p_c->pc + emp_reg + 1) % MEM_SIZE;
}
