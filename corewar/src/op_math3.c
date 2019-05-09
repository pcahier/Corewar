/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_math3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajugnon <ajugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 22:06:34 by ajugnon           #+#    #+#             */
/*   Updated: 2019/04/16 10:22:03 by pcahier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		exec_and(t_vm *vm, t_list *process, int nb_arg, int val[3])
{
	t_process	*p_c;
	t_uc		arg_type;
	t_uc		st;

	st = 0;
	p_c = (t_process *)process->content;
	while (nb_arg)
	{
		arg_type = ((vm->arena[(p_c->pc + 1) % MEM_SIZE]) >> (nb_arg-- * 2))
		& 0b11;
		if (arg_type == 1 && (vm->arena[(p_c->pc + 2 + st) % MEM_SIZE]
		> REG_NUMBER || !vm->arena[(p_c->pc + 2 + st) % MEM_SIZE]))
			break ;
		val[nb_arg] = !nb_arg
			? vm->arena[(p_c->pc + 2 + st) % MEM_SIZE] - 1
			: get_param_direct(vm, process, &st, arg_type);
		if (!nb_arg)
		{
			p_c->reg[val[0]] = val[1] & val[2];
			if (verbose_print(vm, 4))
				ft_printf("P %9d | and %d %d r%d\n", p_c->nprocess, val[2]
					, val[1], val[0] + 1);
			p_c->carry = p_c->reg[val[0]] ? 0 : 1;
		}
	}
}

void			op_and(t_vm *vm, t_list *process)
{
	int			nb_arg;
	int			value[3];
	t_process	*p_c;

	nb_arg = 3;
	p_c = (t_process *)process->content;
	if (check_arg_validity(5, (vm->arena[(p_c->pc + 1) % MEM_SIZE]), nb_arg))
		exec_and(vm, process, nb_arg, value);
	if (verbose_print(vm, 16))
		print_adv(vm, process, calc_shift((vm->arena[(p_c->pc + 1) % MEM_SIZE])
		, 4, 3));
	p_c->pc = (p_c->pc + calc_shift((vm->arena[(p_c->pc + 1) % MEM_SIZE])
	, 4, 3)) % MEM_SIZE;
}
