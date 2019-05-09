/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ldi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajugnon <ajugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 22:06:34 by ajugnon           #+#    #+#             */
/*   Updated: 2019/03/12 22:40:25 by ajugnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	exec_ldi(t_vm *vm, t_process *p_c, int nb_arg, int val[3])
{
	t_uc		shift;
	t_uc		arg_type;

	shift = 0;
	while (nb_arg)
	{
		arg_type = ((vm->arena[(p_c->pc + 1) % MEM_SIZE]) >> (nb_arg-- * 2))
			& 0b11;
		if (arg_type == 1
		&& (vm->arena[(p_c->pc + 2 + shift) % MEM_SIZE] > REG_NUMBER
		|| !vm->arena[(p_c->pc + 2 + shift) % MEM_SIZE]))
			break ;
		val[nb_arg] = !nb_arg ? vm->arena[(p_c->pc + 2 + shift) % MEM_SIZE] - 1
			: get_param_indirect(vm, p_c, &shift, arg_type);
		if (nb_arg == 0)
		{
			p_c->reg[val[0]] = reverse_bytes(vm, p_c->pc + (val[1] + val[2])
				% IDX_MOD, 4);
			if (verbose_print(vm, 4))
				ft_printf("P %9d | ldi %d %d r%d\n       | -> "
				"load from %d + %d = %d (with pc and mod %d)\n"
				, p_c->nprocess, val[2], val[1], val[0] + 1, val[2], val[1]
				, val[2] + val[1], p_c->pc + ((val[1] + val[2]) % IDX_MOD));
		}
	}
}

void		op_ldi(t_vm *vm, t_list *process)
{
	t_uc		nb_arg;
	int			val[3];
	t_process	*p_c;

	p_c = (t_process *)process->content;
	nb_arg = 3;
	if (check_arg_validity(9, (vm->arena[(p_c->pc + 1) % MEM_SIZE]), nb_arg))
		exec_ldi(vm, p_c, nb_arg, val);
	if (verbose_print(vm, 16))
		print_adv(vm, process
			, calc_shift((vm->arena[(p_c->pc + 1) % MEM_SIZE]), 2, 3));
	p_c->pc = (p_c->pc
		+ calc_shift((vm->arena[(p_c->pc + 1) % MEM_SIZE]), 2, 3)) % MEM_SIZE;
}

static void	exec_lldi(t_vm *vm, t_process *p_c, int nb_arg, int val[3])
{
	t_uc		shift;
	t_uc		arg_type;

	shift = 0;
	while (nb_arg)
	{
		arg_type = ((vm->arena[(p_c->pc + 1) % MEM_SIZE]) >> (nb_arg-- * 2))
			& 0b11;
		if (arg_type == 1
		&& (vm->arena[(p_c->pc + 2 + shift) % MEM_SIZE] > REG_NUMBER
		|| !vm->arena[(p_c->pc + 2 + shift) % MEM_SIZE]))
			break ;
		val[nb_arg] = !nb_arg ? vm->arena[(p_c->pc + 2 + shift) % MEM_SIZE] - 1
			: get_param_indirect(vm, p_c, &shift, arg_type);
		if (!nb_arg)
		{
			p_c->reg[val[0]] = reverse_bytes(vm, p_c->pc + val[1] + val[2], 4);
			p_c->carry = p_c->reg[val[0]] ? 0 : 1;
			if (verbose_print(vm, 4))
				ft_printf("P %9d | lldi %d %d r%d\n       | -> load from %d + "
				"%d = %d (with pc %d)\n", p_c->nprocess, val[2]
				, val[1], val[0] + 1, val[2], val[1], val[2] + val[1]
				, p_c->pc + val[2] + val[1]);
		}
	}
}

void		op_lldi(t_vm *vm, t_list *process)
{
	t_uc		nb_arg;
	int			val[3];
	t_process	*p_c;

	p_c = (t_process *)process->content;
	nb_arg = 3;
	if (check_arg_validity(13, (vm->arena[(p_c->pc + 1) % MEM_SIZE]), nb_arg))
		exec_lldi(vm, p_c, nb_arg, val);
	if (verbose_print(vm, 16))
		print_adv(vm, process, calc_shift((vm->arena[(p_c->pc + 1) % MEM_SIZE])
		, 2, 3));
	p_c->pc = (p_c->pc + calc_shift((vm->arena[(p_c->pc + 1) % MEM_SIZE])
		, 2, 3)) % MEM_SIZE;
}
