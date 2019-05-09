/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corechamp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcahier <pcahier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 17:14:14 by pcahier           #+#    #+#             */
/*   Updated: 2019/04/27 18:21:43 by pcahier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		ft_check_champ(t_player *champ, uint32_t ret)
{
	if (champ->magic != COREWAR_EXEC_MAGIC)
		ft_error(HEADER_ERR);
	if (champ->code_length != ret - (PROG_NAME_LENGTH + COMMENT_LENGTH + 16)
			|| champ->code_length > CHAMP_MAX_SIZE)
		ft_error(LENGTH_ERR);
}

static void		ft_gen_champ(char *name, t_player *champ, unsigned int num
		, int bufsize)
{
	int		fd;
	int		ret;
	char	buf[bufsize];

	if (!ft_strext(name, ".cor"))
		ft_error(EXT_ERR);
	fd = open(name, O_RDONLY);
	if (fd == -1)
		ft_error(READ_ERR);
	if ((ret = read(fd, buf, bufsize)) < 19 || ret == bufsize)
		ft_error(READ_ERR);
	champ->number = num;
	ft_memcpy(champ, buf, ret);
	if (close(fd) == -1)
		ft_error(READ_ERR);
	champ->magic = ft_uns_swaptobig(champ->magic);
	if ((champ->code_length = ft_uns_swaptobig(champ->code_length)) == 0)
	{
		write(STDOUT_FILENO,
			"Hey, aren't you a bit too small to be a champion ?\n", 51);
		ft_error(LENGTH_ERR);
	}
	ft_check_champ(champ, ret);
}

static void		ft_check_for_similar_val(unsigned int *n, int nplayer)
{
	int				i;
	int				j;
	unsigned int	v;

	i = 1;
	while (i < nplayer)
	{
		v = n[i];
		j = i + 1;
		while (j <= nplayer)
		{
			if (n[j] == v)
				ft_error(DUP_ERR);
			j++;
		}
		i++;
	}
}

static int		ft_is_it_there(unsigned int *n, int nplayer)
{
	int				i;
	unsigned int	val;

	i = 1;
	val = 1;
	while (i <= nplayer)
	{
		if (val == n[i])
		{
			i = 0;
			val++;
		}
		i++;
	}
	return (val);
}

void			ft_get_champ(int ac, char **av, t_vm *vm, unsigned int *n)
{
	int				i;
	int				j;
	unsigned int	v;

	i = 0;
	j = 1;
	while (++i < ac)
	{
		if (av[i][0] == '-')
			i++;
		else
		{
			if (n[j] == 0)
			{
				v = ft_is_it_there(n, vm->nplayer);
				n[j] = v;
			}
			ft_gen_champ(av[i], &vm->list_player[j - 1], n[j],
				PROG_NAME_LENGTH + COMMENT_LENGTH + CHAMP_MAX_SIZE + 17);
			j++;
		}
	}
	ft_check_for_similar_val(n, vm->nplayer);
}
