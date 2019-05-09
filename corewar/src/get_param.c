/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_param.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajugnon <ajugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 22:06:34 by ajugnon           #+#    #+#             */
/*   Updated: 2019/03/12 22:40:25 by ajugnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		get_param_direct(t_vm *vm, t_list *process, t_uc *sft, t_uc arg_type)
{
	t_process		*p_c;
	int				param;

	p_c = (t_process *)process->content;
	if (arg_type == 1)
	{
		param = p_c->reg[vm->arena[(p_c->pc + 2 + *sft) % MEM_SIZE] - 1];
		*sft += 1;
	}
	else if (arg_type == 2)
	{
		param = reverse_bytes(vm, p_c->pc + 2 + *sft, 4);
		*sft += 4;
	}
	else
	{
		param = reverse_bytes(vm, p_c->pc + 2 + *sft, 2) % IDX_MOD;
		param = reverse_bytes(vm, p_c->pc + param, 4);
		*sft += 2;
	}
	return (param);
}

int		get_param_indirect(t_vm *vm, t_process *p_c, t_uc *sft, t_uc arg_type)
{
	int		param;

	if (arg_type == 1)
	{
		param = p_c->reg[vm->arena[(p_c->pc + 2 + *sft) % MEM_SIZE] - 1];
		*sft += 1;
	}
	else if (arg_type == 2)
	{
		param = reverse_bytes(vm, p_c->pc + 2 + *sft, 2);
		*sft += 2;
	}
	else
	{
		param = reverse_bytes(vm, p_c->pc + 2 + *sft, 2) % IDX_MOD;
		param = reverse_bytes(vm, p_c->pc + param, 4);
		*sft += 2;
	}
	return (param);
}
