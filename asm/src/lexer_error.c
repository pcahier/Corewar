/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrossma <agrossma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 13:42:58 by agrossma          #+#    #+#             */
/*   Updated: 2019/04/19 16:38:15 by agrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ft_plexerr(t_lexer *lexer, int errtype)
{
	static char	*tab[7] = {
		"Lexical error at",
		"name too long",
		"comment too long",
		"wrong header directive",
		"invalid label name",
		"unknow operation",
		"Empty file"
	};

	ft_dprintf(2, "%s: %s ", PROG_NAME, tab[errtype]);
	if (errtype == E_LEX)
		ft_dprintf(2, "%d:%d", lexer->linec + 1, lexer->col + 1);
	else if (errtype == E_WRO || errtype == E_LAB || errtype == E_TOK)
		ft_dprintf(2, "at line %d", lexer->linec + 1);
	ft_dprintf(2, "\n");
	lexer->state = S_ERROR;
}
