/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajugnon <ajugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 22:06:34 by ajugnon           #+#    #+#             */
/*   Updated: 2019/04/27 02:23:55 by agrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	process_creation(t_vm *vm, t_list *process, unsigned int new_pc)
{
	t_process	son_process;
	t_process	*p_content;
	t_list		*lst;
	int			n;

	vm->nprocess++;
	p_content = (t_process *)process->content;
	son_process.nprocess = vm->nprocess;
	son_process.pc = new_pc;
	son_process.carry = p_content->carry;
	son_process.llc = p_content->llc;
	son_process.next_op = -1;
	son_process.op_exec = 0;
	n = REG_NUMBER;
	while (n--)
		son_process.reg[n] = p_content->reg[n];
	if ((lst = ft_lstnew(&son_process, sizeof(t_process))) == NULL)
	{
		ft_dprintf(2, "corewar: %s\n", strerror(errno));
		kill_list_process(vm);
		exit(1);
	}
	ft_lstadd(&(vm->list_process), lst);
}

void	browse_list_process(t_vm *vm)
{
	t_list		*process;
	t_process	*p_content;

	process = vm->list_process;
	if (verbose_print(vm, 2))
		ft_printf("It is now cycle %d\n", vm->ncycle);
	while (process)
	{
		p_content = (t_process *)process->content;
		if (!(p_content->next_op >= 0 && p_content->next_op <= 15))
			define_next_op(vm, p_content);
		if (p_content->op_exec == 0)
		{
			if (p_content->next_op >= 0 && p_content->next_op <= 15)
			{
				g_op_tab[p_content->next_op].f(vm, process);
				p_content->next_op = -1;
			}
		}
		else
			p_content->op_exec--;
		process = process->next;
	}
}

void	kill_list_process(t_vm *vm)
{
	t_list		*process;
	t_list		*previous;
	t_process	*p_c;

	process = vm->list_process;
	previous = NULL;
	while (process)
	{
		p_c = (t_process *)process->content;
		if (p_c->llc < vm->ncycle_fctd || vm->cycle_to_die < 0)
		{
			if (verbose_print(vm, 8) && vm->ncycle != vm->dump_value)
				ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n"
					, p_c->nprocess, vm->ncycle - p_c->llc, vm->cycle_to_die);
			if (process == vm->list_process)
				process = del_head_lst_process(vm, process);
			else
				process = del_elem_lst_process(process, &previous);
		}
		else
		{
			previous = process;
			process = process->next;
		}
	}
}
