/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrossma <agrossma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 11:07:19 by agrossma          #+#    #+#             */
/*   Updated: 2019/04/27 15:34:16 by agrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	ft_handle_arg(t_lexer *lexer, int i)
{
	char	*buffer;
	t_op	op;

	if (lseek(lexer->fd, -(i + 1), SEEK_CUR) == -1
		|| (buffer = ft_strnew(i)) == NULL || read(lexer->fd, buffer, i) == -1)
	{
		ft_strdel(&buffer);
		ft_dprintf(2, "%s: %s\n", PROG_NAME, strerror(errno));
		lexer->state = S_ERROR;
		return ;
	}
	op = ft_getop_type(lexer->current_token->type);
	if (ft_isregister(buffer, lexer->current_token)
		&& (op.type[lexer->current_token->argc] & T_REG))
		lexer->current_token->argv[lexer->current_token->argc] = buffer;
	else if (ft_isdirect(buffer, lexer->current_token)
		&& (op.type[lexer->current_token->argc] & T_DIR))
		lexer->current_token->argv[lexer->current_token->argc] = buffer;
	else if (ft_isindirect(buffer, lexer->current_token)
		&& (op.type[lexer->current_token->argc] & T_IND))
		lexer->current_token->argv[lexer->current_token->argc] = buffer;
	else
		ft_plexerr(lexer, E_LEX);
	lexer->state == S_ERROR ? ft_strdel(&buffer) : NULL;
	lexer->current_token->argc += lexer->state == S_ERROR ? 0 : 1;
}

static void	ft_moveseparator(t_lexer *lexer)
{
	t_op	op;
	char	c;

	op = ft_getop_type(lexer->current_token->type);
	if (lexer->current_token->argc == (int)op.argc)
	{
		lexer->state = S_AFTER;
		return ;
	}
	while (lexer->state != S_ERROR && read(lexer->fd, &c, 1) > 0)
	{
		if (c == SEPARATOR_CHAR)
			break ;
		else if ((c != ' ' && c != '\t') || !ft_isprint(c))
			ft_plexerr(lexer, E_LEX);
	}
}

void		ft_addarg(t_lexer *lexer)
{
	char	c;
	int		i;

	i = 0;
	if (lseek(lexer->fd, -1, SEEK_CUR) == -1)
	{
		ft_dprintf(2, "%s: %s\n", PROG_NAME, strerror(errno));
		lexer->state = S_ERROR;
	}
	while (lexer->state != S_ERROR && read(lexer->fd, &c, 1) > 0)
	{
		if ((c == '\n' && lexer->current_token->argc
			== (int)(ft_getop_type(lexer->current_token->type).argc - 1))
			|| (c == ' ' || c == '\t') || c == SEPARATOR_CHAR
			|| c == COMMENT_CHAR)
		{
			ft_handle_arg(lexer, i);
			break ;
		}
		else if (c == '\n' || !ft_isprint(c))
			ft_plexerr(lexer, E_LEX);
		i++;
		lexer->col++;
	}
	ft_moveseparator(lexer);
}
