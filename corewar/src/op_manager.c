/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_manager.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajugnon <ajugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 22:06:34 by ajugnon           #+#    #+#             */
/*   Updated: 2019/03/12 22:40:25 by ajugnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	define_next_op(t_vm *vm, t_process *process)
{
	if (vm->arena[(unsigned int)process->pc % MEM_SIZE] > 0
		&& vm->arena[(unsigned int)process->pc % MEM_SIZE] <= 16)
	{
		process->next_op = vm->arena[(unsigned int)process->pc % MEM_SIZE] - 1;
		process->op_exec = g_op_tab[process->next_op].cycle - 1;
	}
	else
	{
		process->next_op = -1;
		process->pc = (process->pc + 1) % MEM_SIZE;
	}
}
