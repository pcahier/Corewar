/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajugnon <ajugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 22:06:34 by ajugnon           #+#    #+#             */
/*   Updated: 2019/04/27 17:01:20 by pcahier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	vm_init_var(t_vm *vm)
{
	vm->list_process = NULL;
	vm->nplayer = 0;
	vm->nprocess = 0;
	vm->dump_value = -1;
	vm->verbose_val = 0;
	vm->last_player_id = -1;
	vm->ncycle = 0;
	vm->nlive_ctd = 0;
	vm->ncycle_ctd = 0;
	vm->ncycle_fctd = 0;
	vm->cycle_to_die = CYCLE_TO_DIE;
	vm->nb_check_dec_ctd = 0;
	vm->width = 32;
}

static void	vm_init_array(t_vm *vm)
{
	int	i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		vm->list_player[i].number = 0;
		ft_memset(vm->list_player[i].name, 0, PROG_NAME_LENGTH);
		ft_memset(vm->list_player[i].comment, 0, COMMENT_LENGTH);
		ft_memset(vm->list_player[i].code, 0, CHAMP_MAX_SIZE);
		i++;
	}
	ft_memset(vm->arena, 0, sizeof(unsigned char) * MEM_SIZE);
}

void		vm_init(t_vm *vm)
{
	ft_bzero(vm, sizeof(t_vm));
	vm_init_array(vm);
	vm_init_var(vm);
}
