/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrossma <agrossma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 15:11:52 by agrossma          #+#    #+#             */
/*   Updated: 2019/04/19 17:59:31 by agrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	ft_namecpy(t_lexer *lexer, t_header *header)
{
	size_t	size;
	char	c;

	size = 0;
	while (lexer->state != S_ERROR && read(lexer->fd, &c, 1) > 0)
	{
		if (c == '"')
			break ;
		header->prog_name[size++] = c;
		if (size > PROG_NAME_LENGTH)
		{
			ft_plexerr(lexer, E_NAME);
			return ;
		}
	}
	lexer->col = lexer->col + 2 + ft_strlen(header->prog_name);
	lexer->name = 1;
}

static void	ft_commentcpy(t_lexer *lexer, t_header *header)
{
	size_t	size;
	char	c;

	size = 0;
	while (lexer->state != S_ERROR && read(lexer->fd, &c, 1) > 0)
	{
		if (c == '"')
			break ;
		header->comment[size++] = c;
		if (size > COMMENT_LENGTH)
		{
			ft_plexerr(lexer, E_COMMENT);
			return ;
		}
	}
	lexer->col = lexer->col + 2 + ft_strlen(header->comment);
	lexer->comment = 1;
}

void		ft_headercpy(t_lexer *lexer, t_header *header, int ft)
{
	char	c;

	while (lexer->state != S_ERROR && read(lexer->fd, &c, 1) > 0)
	{
		if (c == ' ' || c == '\t')
		{
			lexer->col++;
			continue ;
		}
		else if (c == '"')
			break ;
		else
		{
			ft_plexerr(lexer, E_LEX);
			return ;
		}
	}
	if (ft == 0)
		ft_namecpy(lexer, header);
	else
		ft_commentcpy(lexer, header);
}
