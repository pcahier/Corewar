/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrossma <agrossma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/24 20:08:32 by agrossma          #+#    #+#             */
/*   Updated: 2019/04/27 14:36:51 by agrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		ft_handle_newline(t_lexer *lexer)
{
	lexer->linec++;
	lexer->col = 0;
	lexer->state = lexer->name == 0 || lexer->comment == 0 ? S_HEADER
		: S_NORMAL;
}

static void		ft_handle_comment(t_lexer *lexer)
{
	if (lexer->state == S_NORMAL || lexer->state == S_HEADER
		|| lexer->state == S_AFTER || lexer->state == S_AFTER_LABEL)
		lexer->state = S_COMMENT;
	else
		ft_plexerr(lexer, E_LEX);
}

static void		ft_copy_header(t_lexer *lexer, t_header *header, int i)
{
	char	*buffer;

	if (lseek(lexer->fd, -i, SEEK_CUR) == -1 || (buffer = ft_strnew(i)) == NULL
		|| read(lexer->fd, buffer, i) == -1)
	{
		ft_strdel(&buffer);
		ft_dprintf(2, "%s: %s\n", PROG_NAME, strerror(errno));
		lexer->state = S_ERROR;
		return ;
	}
	if (ft_strlen(buffer) == ft_strlen(NAME_CMD_STRING)
		&& !ft_strncmp(buffer, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)))
		ft_headercpy(lexer, header, 0);
	else if (ft_strlen(buffer) == ft_strlen(COMMENT_CMD_STRING)
		&& !ft_strncmp(buffer, COMMENT_CMD_STRING,
		ft_strlen(COMMENT_CMD_STRING)))
		ft_headercpy(lexer, header, 1);
	else
		ft_plexerr(lexer, E_WRO);
	ft_strdel(&buffer);
	if (lexer->state == S_HEADER)
		lexer->state = S_AFTER;
}

static void		ft_handle_header(t_lexer *lexer, t_header *header)
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
		if (c == ' ' || c == '\t' || c == '"' || c == '\n' || c == COMMENT_CHAR)
		{
			if (lseek(lexer->fd, -1, SEEK_CUR) == -1)
			{
				ft_dprintf(2, "%s: %s\n", PROG_NAME, strerror(errno));
				lexer->state = S_ERROR;
			}
			break ;
		}
		lexer->col++;
		i++;
	}
	(c == '\n' || c == COMMENT_CHAR) && lexer->state != S_ERROR
		? ft_plexerr(lexer, E_LEX) : ft_copy_header(lexer, header, i);
}

int				ft_parse(t_lexer *lexer, t_header *header)
{
	char	c;

	lexer->state = S_HEADER;
	while (lexer->state != S_ERROR && read(lexer->fd, &c, 1) > 0)
	{
		if (c == '\n')
			ft_handle_newline(lexer);
		else if (c == COMMENT_CHAR && lexer->state != S_COMMENT)
			ft_handle_comment(lexer);
		else if ((lexer->state == S_AFTER && (c != ' ' && c != '\t'))
			|| c == 0)
			ft_plexerr(lexer, E_LEX);
		else if (lexer->state == S_HEADER && (c != ' ' && c != '\t'))
			ft_handle_header(lexer, header);
		else if ((lexer->state == S_NORMAL
			|| lexer->state == S_AFTER_LABEL) && (c != ' ' && c != '\t'))
			ft_tokenize(lexer);
		else if (lexer->state == S_TOKEN && (c != ' ' && c != '\t'))
			ft_addarg(lexer);
		lexer->col++;
	}
	if ((lexer->labelc == 0 && lexer->tokenc == 0) && lexer->state != S_ERROR)
		ft_plexerr(lexer, E_EMP);
	(void)close(lexer->fd);
	return (lexer->state == S_ERROR || lexer->name == 0 || lexer->comment == 0);
}
