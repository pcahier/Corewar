/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrossma <agrossma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 16:50:59 by agrossma          #+#    #+#             */
/*   Updated: 2019/04/26 14:06:22 by agrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Iterate through the list and applies the function f to each link
** \param lst Pointer to the first link of the list
** \param f Adress of a function to apply to each link
*/

void	ft_lstiter(t_list *lst, void (*f)(t_list *elem))
{
	if (f == NULL)
		return ;
	while (lst)
	{
		(*f)(lst);
		lst = lst->next;
	}
}
