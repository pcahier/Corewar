/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajugnon <ajugnon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 22:06:34 by ajugnon           #+#    #+#             */
/*   Updated: 2019/04/26 13:08:15 by agrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		reverse_bytes(t_vm *vm, int pc, int nbytes)
{
	t_uc two_bytes[2];
	t_uc four_bytes[4];

	if (nbytes == 2)
	{
		two_bytes[0] = vm->arena[(pc + 1) % MEM_SIZE];
		two_bytes[1] = vm->arena[(pc) % MEM_SIZE];
		return (*(short *)&two_bytes[0]);
	}
	if (nbytes == 4)
	{
		four_bytes[0] = vm->arena[(pc + 3) % MEM_SIZE];
		four_bytes[1] = vm->arena[(pc + 2) % MEM_SIZE];
		four_bytes[2] = vm->arena[(pc + 1) % MEM_SIZE];
		four_bytes[3] = vm->arena[(pc) % MEM_SIZE];
		return (*(int *)&four_bytes[0]);
	}
	return (-1);
}

int		search_id_player(t_vm *vm, unsigned int num_player)
{
	int		i;
	int		id;
	int		stop;

	i = 0;
	id = -1;
	stop = 0;
	while (i < vm->nplayer && stop != 1)
	{
		if (num_player == vm->list_player[i].number)
		{
			id = i;
			stop = 1;
		}
		i++;
	}
	return (id);
}

void	load_reg(t_vm *vm, unsigned int value, int address)
{
	char i;

	i = 4;
	if (address < 0)
		address += MEM_SIZE;
	while (i--)
	{
		vm->arena[(address--) % MEM_SIZE] = value & 0xFF;
		value = value >> 8;
	}
}

int		check_arg_validity(t_uc id_op, t_uc b_oct, t_uc narg)
{
	t_uc		arg_type;
	t_uc		param;
	int			shift;
	int			i;

	i = 0;
	shift = 6;
	while (narg--)
	{
		param = (b_oct >> shift) & 0b11;
		arg_type = param != 0 ? 1 << (param - 1) : 0;
		if (!(arg_type & g_op_tab[id_op].args[i]))
			return (0);
		i++;
		shift -= 2;
	}
	return (1);
}

int		calc_shift(t_uc b_ocp, t_uc direct_size, t_uc nb_arg)
{
	int shift;

	shift = 2;
	while (++nb_arg <= 4)
		b_ocp >>= 2;
	while (b_ocp)
	{
		shift += ((b_ocp & 0b11) == 0b01) ? 1 : 0;
		shift += ((b_ocp & 0b11) == 0b11) ? 2 : 0;
		shift += ((b_ocp & 0b11) == 0b10) ? direct_size : 0;
		b_ocp >>= 2;
	}
	return (shift);
}
