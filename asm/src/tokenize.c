/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrossma <agrossma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 20:12:46 by agrossma          #+#    #+#             */
/*   Updated: 2019/04/26 13:35:30 by agrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_list		*ft_getlabel(t_lexer *lexer, char *str)
{
	t_list	*tmp;
	size_t	len;

	len = ft_strlen(str);
	tmp = lexer->lst_label;
	while (tmp)
	{
		if (ft_strlen((char *)tmp->content) == len
			&& !ft_strncmp((char *)tmp->content, str, len))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

int			ft_labelexist(char *label, t_lexer *lexer)
{
	t_list	*tmp;
	size_t	len;

	if (!ft_strchr(label, LABEL_CHAR))
		return (1);
	len = ft_strlen(label[0] == DIRECT_CHAR ? label + 2 : label + 1);
	tmp = lexer->lst_label;
	while (tmp)
	{
		if (ft_strlen((char *)tmp->content) == len
			&& !ft_strncmp((char *)tmp->content, label[0] == DIRECT_CHAR
				? label + 2 : label + 1, len))
			return (1);
		tmp = tmp->next;
	}
	ft_dprintf(2, "%s: %s %s: %s\n",
		PROG_NAME, "Error dereferencing", label, "no such label");
	return (0);
}

static void	ft_handle_label(t_lexer *lexer, int i)
{
	char	*buffer;
	t_list	*label;

	if (lseek(lexer->fd, -(i + 1), SEEK_CUR) == -1
		|| (buffer = ft_strnew(i)) == NULL || read(lexer->fd, buffer, i) == -1
		|| lseek(lexer->fd, 1, SEEK_CUR) == -1
		|| (label = ft_lstnew(buffer, ft_strlen(buffer) + 1)) == NULL)
	{
		ft_strdel(&buffer);
		ft_dprintf(2, "%s: %s\n", PROG_NAME, strerror(errno));
		lexer->state = S_ERROR;
		return ;
	}
	if (!ft_isvalidlabel(buffer))
	{
		ft_strdel(&buffer);
		ft_lstdelone(&label, &ft_lstdelcontent);
		ft_plexerr(lexer, E_LAB);
		return ;
	}
	ft_strdel(&buffer);
	label->content_size = lexer->tokenc;
	ft_lstadd(&lexer->lst_label, label);
	lexer->labelc++;
	lexer->state = S_AFTER_LABEL;
}

static void	ft_handle_op(t_lexer *lexer, int i)
{
	char	*buffer;
	t_token	*token;
	t_op	op;

	op.mnemonic = "dick";
	if (lseek(lexer->fd, -(i + 1), SEEK_CUR) == -1
		|| (buffer = ft_strnew(i)) == NULL || read(lexer->fd, buffer, i) == -1
		|| (token = (t_token *)ft_memalloc(sizeof(t_token))) == NULL
		|| (op = ft_getop(buffer)).mnemonic == NULL)
	{
		ft_strdel(&buffer);
		ft_memdel((void **)&token);
		op.mnemonic == NULL ? ft_plexerr(lexer, E_TOK)
			: ft_dprintf(2, "%s: %s\n", PROG_NAME, strerror(errno));
		lexer->state = S_ERROR;
		return ;
	}
	ft_strdel(&buffer);
	token->type = op.opcode;
	ft_tokenadd(&lexer->lst_token, token);
	lexer->current_token = token;
	lexer->tokenc++;
	lexer->state = S_TOKEN;
}

void		ft_tokenize(t_lexer *lexer)
{
	int		i;
	char	c;

	i = 0;
	if (lseek(lexer->fd, -1, SEEK_CUR) == -1)
	{
		ft_dprintf(2, "%s: %s\n", PROG_NAME, strerror(errno));
		lexer->state = S_ERROR;
	}
	while (lexer->state != S_ERROR && read(lexer->fd, &c, 1) > 0)
	{
		if ((c == LABEL_CHAR && lexer->state != S_AFTER_LABEL)
			|| (c == '\t' || c == ' '))
		{
			c == LABEL_CHAR ? ft_handle_label(lexer, i)
				: ft_handle_op(lexer, i);
			break ;
		}
		else if (c == '\n' || c == COMMENT_CHAR || (c == LABEL_CHAR
			&& lexer->state == S_AFTER_LABEL) || !ft_isprint(c))
			ft_plexerr(lexer, E_LEX);
		i++;
		lexer->col++;
	}
}
