/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrossma <agrossma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 06:04:43 by agrossma          #+#    #+#             */
/*   Updated: 2019/04/15 22:13:04 by agrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	ft_tokenfree(t_token **token)
{
	t_token	*tmp;

	tmp = *token;
	while (tmp->argc)
		ft_strdel(&tmp->argv[--tmp->argc]);
	ft_memdel((void **)&tmp);
}

void	ft_tokenadd(t_token **lst, t_token *token)
{
	t_token	*tmp;

	tmp = *lst;
	if (tmp == NULL)
	{
		*lst = token;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = token;
}
