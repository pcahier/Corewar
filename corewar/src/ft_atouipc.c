/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atouipc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcahier <pcahier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 18:36:47 by pcahier           #+#    #+#             */
/*   Updated: 2019/04/24 20:09:18 by pcahier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t			ft_strlendigit(const char *nb)
{
	size_t	i;

	i = 0;
	while (ft_isdigit(nb[i]))
		i++;
	return (i);
}

static unsigned int		ft_nbcmp(const char *nb)
{
	char	imax[11];
	size_t	j;

	j = 0;
	ft_strcpy(imax, "4294967295");
	if (ft_strlendigit(nb) > 10)
		return (0);
	else if (ft_strlendigit(nb) == 10)
		while ((nb[j] != '\0' || imax[j] != '\0') && ft_isdigit(nb[j]))
		{
			if (nb[j] > imax[j])
				return (0);
			else if (nb[j] == imax[j])
				j++;
			else if (nb[j] < imax[j])
				break ;
		}
	return (1);
}

static unsigned int		ft_atoui_convert(const char *str)
{
	int		res;

	res = 0;
	while (*str)
	{
		if (ft_isdigit(*str))
		{
			res = (res * 10) + (*str - 48);
			str++;
		}
		else
			return (0);
	}
	return (res);
}

unsigned int			ft_atouipc(const char *str)
{
	unsigned int	c;

	if (*str)
	{
		while (ft_isspace(*str))
			str++;
		if (*str == '-' || *str == '+')
		{
			if (*str == '-')
				return (0);
			str++;
		}
		if (!ft_isdigit(*str))
			return (0);
		else if ((c = ft_nbcmp(str)) > 0)
			return (ft_atoui_convert(str));
		else
			return (c);
	}
	return (0);
}
