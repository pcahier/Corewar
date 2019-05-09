/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrossma <agrossma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 11:39:29 by agrossma          #+#    #+#             */
/*   Updated: 2019/04/18 00:41:48 by agrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ft_clean(t_lexer *lexer)
{
	t_token	*tmp;
	t_token	*tmp2;

	ft_lstdel(&lexer->lst_label, &ft_lstdelcontent);
	tmp = lexer->lst_token;
	while (tmp)
	{
		tmp2 = tmp->next;
		ft_tokenfree(&tmp);
		tmp = tmp2;
	}
	ft_memdel((void **)&lexer->mem);
}
