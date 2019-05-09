/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumber.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrossma <agrossma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 15:45:10 by agrossma          #+#    #+#             */
/*   Updated: 2018/01/15 15:51:24 by agrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isnumber(const char *str)
{
	int		i;

	i = 0;
	str[0] == '-' ? i++ : 0;
	while (i < (int)ft_strlen(str))
		if (!ft_isdigit(str[i++]))
			return (0);
	return (1);
}
