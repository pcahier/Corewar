/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajugnon <ajugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 22:06:34 by ajugnon           #+#    #+#             */
/*   Updated: 2019/03/12 22:40:25 by ajugnon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_list	*del_head_lst_process(t_vm *vm, t_list *process)
{
	vm->list_process = process->next;
	free(process->content);
	free(process);
	process = vm->list_process;
	return (process);
}

t_list	*del_elem_lst_process(t_list *process, t_list **previous)
{
	process = process->next;
	free((*previous)->next->content);
	free((*previous)->next);
	(*previous)->next = process;
	return (process);
}
