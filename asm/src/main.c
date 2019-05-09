/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrossma <agrossma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 07:58:35 by agrossma          #+#    #+#             */
/*   Updated: 2019/04/26 21:22:15 by agrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int		ft_argsize(int arg_type, int i, t_op op)
{
	int		size;

	size = 0;
	if ((op.opcode == 11 || op.opcode == 0x0c || op.opcode == 9
		|| op.opcode == 0x0a || op.opcode == 0x0e || op.opcode == 15)
		&& arg_type == T_DIR)
	{
		if ((op.opcode == 11 && i == 1) || (op.opcode == 11 && i == 2)
			|| (op.opcode == 0x0c || op.opcode == 9 || op.opcode == 15)
			|| (op.opcode == 0x0a && i == 0) || (op.opcode == 0x0a && i == 1)
			|| (op.opcode == 0x0e && i == 0) || (op.opcode == 0x0e && i == 1))
			size = 2;
	}
	else if (arg_type == T_REG)
		size = 1;
	else if (arg_type == T_DIR)
		size = 4;
	else
		size = 2;
	return (size);
}

static int		ft_prog_size(t_lexer *lexer)
{
	int		size;
	t_token	*tmp;
	int		i;
	int		j;

	size = 0;
	j = 0;
	tmp = lexer->lst_token;
	while (tmp)
	{
		lexer->mem[j] = size + j;
		j++;
		i = -1;
		if (ft_getop_type(tmp->type).octal)
			size++;
		while (++i < tmp->argc)
		{
			if (tmp->args_type[i] == T_DIR || tmp->args_type[i] == T_IND)
				if (!ft_labelexist(tmp->argv[i], lexer))
					return (-1);
			size += ft_argsize(tmp->args_type[i], i, ft_getop_type(tmp->type));
		}
		tmp = tmp->next;
	}
	return (size + lexer->tokenc);
}

static void		ft_write_executable(t_lexer *lexer, t_header *header,
				char *file)
{
	char	output[ft_strlen(file) + 3];

	ft_strncpy(output, file, ft_strlen(file) - 1);
	ft_strcpy(output + ft_strlen(file) - 1, "cor\0");
	if ((lexer->fd = open(output, O_CREAT | O_WRONLY | O_TRUNC, 0755)) == -1
		|| (lexer->mem = ft_memalloc(sizeof(int) * (lexer->tokenc + 1)))
		== NULL)
	{
		lexer->fd != -1 ? (void)close(lexer->fd) : NULL;
		ft_dprintf(2, "%s: %s\n", PROG_NAME, strerror(errno));
		return ;
	}
	if ((int)(header->prog_size = ft_bigendian_32(ft_prog_size(lexer))) == -1)
	{
		(void)close(lexer->fd);
		return ;
	}
	lexer->mem[lexer->tokenc] = ft_bigendian_32(header->prog_size);
	ft_dprintf(1, "Writing output program to %s\n", output);
	header->magic = ft_bigendian_32(COREWAR_EXEC_MAGIC);
	write(lexer->fd, header, sizeof(t_header));
	ft_write_asm(lexer);
	(void)close(lexer->fd);
}

static void		ft_usage(void)
{
	ft_dprintf(2, "%s\n", "Usage: "PROG_NAME" <filename>.s");
	exit(1);
}

int				main(int ac, char **av)
{
	t_header	header;
	t_lexer		lexer;

	if (ac != 2 || !ft_extcmp(av[1], ".s"))
	{
		if (ac != 2)
			ac < 2 ? ft_perror(E_2LIT) : ft_perror(E_2BIG);
		else
			ft_perror(E_WEXT);
		ft_usage();
	}
	ft_bzero(&header, sizeof(t_header));
	ft_bzero(&lexer, sizeof(t_lexer));
	if ((lexer.fd = open(av[1], O_RDONLY)) == -1
		|| lseek(lexer.fd, 0, SEEK_CUR) != 0)
	{
		lexer.fd != -1 ? (void)close(lexer.fd) : NULL;
		errno != 0 ? ft_dprintf(2, "%s: %s\n", PROG_NAME, strerror(errno))
			: ft_dprintf(2, "%s: Offset is not at position 0\n", PROG_NAME);
		exit(errno);
	}
	if (ft_parse(&lexer, &header) == 0)
		ft_write_executable(&lexer, &header, av[1]);
	ft_clean(&lexer);
	return (0);
}
