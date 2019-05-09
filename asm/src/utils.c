/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrossma <agrossma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 11:06:59 by agrossma          #+#    #+#             */
/*   Updated: 2019/04/24 20:16:42 by agrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		ft_isvalidlabel(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
		if (ft_strchr(LABEL_CHARS, str[i]) == NULL)
			return (0);
	return (1);
}

int		ft_isregister(char *str, t_token *token)
{
	int		reg;

	if (str[0] != 'r' || !ft_isnumber(str + 1))
		return (0);
	reg = ft_atoi(str + 1);
	if (reg == 0 || reg > REG_NUMBER)
		return (0);
	token->args_type[token->argc] = T_REG;
	return (1);
}

int		ft_isdirect(char *str, t_token *token)
{
	if (str[0] != DIRECT_CHAR)
		return (0);
	else if (str[1] == LABEL_CHAR && !ft_isvalidlabel(str + 2))
		return (0);
	else if (!ft_isnumber(str + 1) && str[1] != LABEL_CHAR)
		return (0);
	token->args_type[token->argc] = T_DIR;
	return (1);
}

int		ft_isindirect(char *str, t_token *token)
{
	if (str[0] == LABEL_CHAR && !ft_isvalidlabel(str + 1))
		return (0);
	else if (!ft_isnumber(str) && str[0] != LABEL_CHAR)
		return (0);
	token->args_type[token->argc] = T_IND;
	return (1);
}

void	ft_lstdelcontent(void *content, size_t content_size)
{
	ft_memdel(&content);
	(void)content_size;
}
