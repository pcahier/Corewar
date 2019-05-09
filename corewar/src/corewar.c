/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcahier <pcahier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 22:06:34 by pcahier           #+#    #+#             */
/*   Updated: 2019/04/27 18:22:06 by pcahier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void				ft_check_values(void)
{
	if (CHAMP_MAX_SIZE > (MEM_SIZE / MAX_PLAYERS) || PROG_NAME_LENGTH < 1
			|| COMMENT_LENGTH < 0 || CYCLE_TO_DIE < 1)
		ft_error(H_VAL);
}

static void				ft_order_champ(t_vm *vm)
{
	int			i;
	int			j;
	t_player	swap;

	i = 0;
	while (i < vm->nplayer - 1)
	{
		j = 0;
		while (j < vm->nplayer - 1)
		{
			if (vm->list_player[j].number > vm->list_player[j + 1].number)
			{
				swap = vm->list_player[j];
				vm->list_player[j] = vm->list_player[j + 1];
				vm->list_player[j + 1] = swap;
			}
			j++;
		}
		i++;
	}
}

static void				ft_options(char **av, int noend, t_vm *vm
		, unsigned int *n)
{
	if (!ft_strcmp(&av[0][1], "dump") || !ft_strcmp(&av[0][1], "d"))
	{
		if ((!noend) || ((vm->dump_value = ft_atoipc(&av[1][0])) < 1))
			ft_error(VAL_OPT);
	}
	else if (!ft_strcmp(&av[0][1], "w"))
	{
		if ((!noend) || (vm->width = ft_atoipc(&av[1][0])) < 1
			|| vm->width > 128)
			ft_error(VAL_OPT);
	}
	else if (!ft_strcmp(&av[0][1], "n"))
	{
		if ((!noend) || ((n[0] = ft_atouipc(&av[1][0])) < 1))
			ft_error(VAL_OPT);
	}
	else if (!ft_strcmp(&av[0][1], "v"))
	{
		if ((!noend) || (vm->verbose_val = ft_atoipc(&av[1][0])) < 0
			|| vm->verbose_val > 31)
			ft_error(VAL_OPT);
	}
	else
		ft_error(OPT_ERR);
}

static void				ft_check_arguments(int ac, char **av, t_vm *vm)
{
	int				i;
	int				j;
	unsigned int	n[MAX_PLAYERS + 1];

	i = 0;
	j = 1;
	n[0] = 0;
	while (++i < ac)
	{
		if (av[i][0] == '-')
		{
			ft_options(&av[i], (ac - i - 1), vm, n);
			i++;
		}
		else
		{
			n[j++] = n[0];
			n[0] = 0;
			vm->nplayer += 1;
		}
		if (j > MAX_PLAYERS + 1)
			ft_error(MANY_CHAMP);
	}
	ft_get_champ(ac, av, vm, n);
}

int						main(int ac, char **av)
{
	t_vm			vm;

	if (ac == 1 || !av)
		return (ft_usage());
	ft_check_values();
	vm_init(&vm);
	ft_check_arguments(ac, av, &vm);
	if (vm.nplayer == 0)
		ft_error(NO_NAME);
	ft_order_champ(&vm);
	ft_print_intro(&vm);
	vm_generate_arena(&vm);
	vm_launch_game(&vm);
	kill_list_process(&vm);
	return (0);
}
