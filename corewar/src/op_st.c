/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajugnon <ajugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 22:06:34 by ajugnon           #+#    #+#             */
/*   Updated: 2019/04/16 10:22:39 by pcahier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	exec_st(t_vm *vm, t_process *p_c)
{
	int			new_emp;

	if (ocp2((vm->arena[(p_c->pc + 1) % MEM_SIZE])) == 1
	&& (vm->arena[(p_c->pc + 3) % MEM_SIZE] > 0
	&& vm->arena[(p_c->pc + 3) % MEM_SIZE] <= REG_NUMBER))
		p_c->reg[vm->arena[(p_c->pc + 3)
			% MEM_SIZE] - 1] = p_c->reg[vm->arena[(p_c->pc + 2)
			% MEM_SIZE] - 1];
	else if (ocp2((vm->arena[(p_c->pc + 1) % MEM_SIZE])) == 3)
	{
		new_emp = reverse_bytes(vm, p_c->pc + 3, 2);
		if (verbose_print(vm, 4))
			ft_printf("P %9d | st r%d %d\n", p_c->nprocess
				, vm->arena[(p_c->pc + 2) % MEM_SIZE], new_emp);
		load_reg(vm, (unsigned int)(p_c->reg[vm->arena[(p_c->pc + 2)
		% MEM_SIZE] - 1]), p_c->pc + 3 + (new_emp % IDX_MOD));
	}
}

void		op_st(t_vm *vm, t_list *process)
{
	t_uc		stock;
	t_process	*p_c;

	p_c = (t_process *)process->content;
	stock = (vm->arena[(p_c->pc + 1) % MEM_SIZE]);
	if (ocp1((vm->arena[(p_c->pc + 1) % MEM_SIZE])) == 1
	&& (vm->arena[(p_c->pc + 2) % MEM_SIZE] > 0
	&& vm->arena[(p_c->pc + 2) % MEM_SIZE] <= REG_NUMBER))
		exec_st(vm, p_c);
	if (verbose_print(vm, 16))
		print_adv(vm, process, calc_shift(stock, 4, 2));
	p_c->pc = (p_c->pc + calc_shift(stock, 4, 2)) % MEM_SIZE;
}

static void	exec_sti(t_vm *vm, t_process *p_c, int nb_arg, int value[3])
{
	t_uc		shift;

	shift = 0;
	while (nb_arg--)
	{
		if ((((vm->arena[(p_c->pc + 1) % MEM_SIZE]) >> ((nb_arg + 1) * 2))
			& 0b11) == 1
		&& (vm->arena[(p_c->pc + 2 + shift) % MEM_SIZE] > REG_NUMBER
		|| !vm->arena[(p_c->pc + 2 + shift) % MEM_SIZE]))
			break ;
		value[nb_arg] = nb_arg == 2
			? vm->arena[(p_c->pc + 2 + shift++) % MEM_SIZE] - 1
			: get_param_indirect(vm, p_c, &shift, (((vm->arena[(p_c->pc + 1)
				% MEM_SIZE]) >> ((nb_arg + 1) * 2)) & 0b11));
		if (!nb_arg)
		{
			load_reg(vm, p_c->reg[value[2]], p_c->pc + 3
				+ ((value[0] + value[1]) % IDX_MOD));
			if (verbose_print(vm, 4))
				ft_printf("P %9d | sti r%d %d %d\n       | -> "
				"store to %d + %d = %d (with pc and mod %d)\n", p_c->nprocess
				, value[2] + 1, value[1], value[0], value[1], value[0], value[0]
				+ value[1], p_c->pc + ((value[0] + value[1]) % IDX_MOD));
		}
	}
}

void		op_sti(t_vm *vm, t_list *process)
{
	t_uc		nb_arg;
	int			value[3];
	t_uc		stock;
	t_process	*p_c;

	p_c = (t_process *)process->content;
	nb_arg = 3;
	stock = (vm->arena[(p_c->pc + 1) % MEM_SIZE]);
	if (check_arg_validity(10, (vm->arena[(p_c->pc + 1) % MEM_SIZE]), nb_arg))
		exec_sti(vm, p_c, nb_arg, value);
	if (verbose_print(vm, 16))
		print_adv(vm, process, calc_shift(stock, 2, 3));
	p_c->pc = (p_c->pc + calc_shift(stock, 2, 3)) % MEM_SIZE;
}
