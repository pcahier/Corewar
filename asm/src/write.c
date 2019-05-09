/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrossma <agrossma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 12:47:04 by agrossma          #+#    #+#             */
/*   Updated: 2019/04/26 23:46:33 by agrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	ft_write_octal(t_lexer *lexer, t_token *token)
{
	char	octal[9];
	int		i;
	int		j;

	ft_memset(octal, '0', sizeof(char) * 8);
	octal[8] = 0;
	i = -1;
	j = 0;
	while (++i < token->argc)
	{
		if (token->args_type[i] == T_REG)
			octal[j + 1] = '1';
		else if (token->args_type[i] == T_DIR)
			octal[j] = '1';
		else
		{
			octal[j] = '1';
			octal[j + 1] = '1';
		}
		j += 2;
	}
	j = ft_atoi_base(octal, 2);
	write(lexer->fd, &j, 1);
}

static void	ft_write_ind(t_lexer *lexer, t_token *token, int i, int count)
{
	unsigned short	val;

	if (ft_strchr(token->argv[i], LABEL_CHAR))
		val = lexer->mem[ft_getlabel(lexer, token->argv[i] + 1)->content_size]
			- lexer->mem[count];
	else
		val = ft_atoi(token->argv[i]);
	val = ft_bigendian_16(val);
	write(lexer->fd, &val, 2);
}

static void	ft_write_dir(t_lexer *lexer, t_token *token, int i, int count)
{
	t_op			op;
	unsigned int	val;
	int				size;

	size = 4;
	op = ft_getop_type(token->type);
	if (op.opcode == 11 || op.opcode == 0x0c || op.opcode == 9
		|| op.opcode == 0x0a || op.opcode == 0x0e || op.opcode == 15)
	{
		if ((op.opcode == 11 && i == 1) || (op.opcode == 11 && i == 2)
			|| (op.opcode == 0x0c || op.opcode == 9 || op.opcode == 15)
			|| (op.opcode == 0x0a && i == 0) || (op.opcode == 0x0a && i == 1)
			|| (op.opcode == 0x0e && i == 0) || (op.opcode == 0x0e && i == 1))
			size = 2;
	}
	if (ft_strchr(token->argv[i], LABEL_CHAR))
		val = lexer->mem[ft_getlabel(lexer, token->argv[i] + 2)->content_size]
			- lexer->mem[count];
	else
		val = ft_atoi(token->argv[i] + 1);
	val = size == 2 ? ft_bigendian_16(val) : ft_bigendian_32(val);
	write(lexer->fd, &val, size);
}

static void	ft_write_arg(t_lexer *lexer, t_token *token, int i, int count)
{
	int		reg;

	if (token->args_type[i] == T_REG)
	{
		reg = ft_atoi(token->argv[i] + 1);
		write(lexer->fd, &reg, 1);
	}
	else if (token->args_type[i] == T_IND)
		ft_write_ind(lexer, token, i, count);
	else
		ft_write_dir(lexer, token, i, count);
}

void		ft_write_asm(t_lexer *lexer)
{
	t_token		*tmp;
	t_op		op;
	int			i;
	int			count;

	tmp = lexer->lst_token;
	count = 0;
	while (tmp)
	{
		op = ft_getop_type(tmp->type);
		write(lexer->fd, &op.opcode, 1);
		if (op.octal)
			ft_write_octal(lexer, tmp);
		i = -1;
		while (++i < tmp->argc)
			ft_write_arg(lexer, tmp, i, count);
		tmp = tmp->next;
		count++;
	}
}
