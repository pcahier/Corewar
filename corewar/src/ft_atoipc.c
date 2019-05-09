/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoipc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcahier <pcahier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 20:12:28 by pcahier           #+#    #+#             */
/*   Updated: 2019/04/10 17:17:49 by pcahier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strlendigit(const char *nb)
{
	size_t	i;

	i = 0;
	while (ft_isdigit(nb[i]))
		i++;
	return (i);
}

static int		ft_nbcmp(const char *nb, int i)
{
	char	imax[11];
	size_t	j;

	j = 0;
	if (i == 1)
		ft_strcpy(imax, "2147483647");
	else
		ft_strcpy(imax, "2147483648");
	if (ft_strlendigit(nb) > 10)
		return (i > 0 ? -1 : 0);
	else if (ft_strlendigit(nb) == 10)
		while ((nb[j] != '\0' || imax[j] != '\0') && ft_isdigit(nb[j]))
		{
			if (nb[j] > imax[j])
				return (i > 0 ? -1 : 0);
			else if (nb[j] == imax[j])
				j++;
			else if (nb[j] < imax[j])
				break ;
		}
	return (1);
}

static int		ft_atoi_convert(int i, const char *str)
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
			return (-1);
	}
	return (res * i);
}

int				ft_atoipc(const char *str)
{
	int		i;
	int		c;

	i = 1;
	if (*str)
	{
		while (ft_isspace(*str))
			str++;
		if (*str == '-' || *str == '+')
		{
			if (*str == '-')
				i = -1;
			str++;
		}
		if (!ft_isdigit(*str))
			return (-1);
		else if ((c = ft_nbcmp(str, i)) > 0)
			return (ft_atoi_convert(i, str));
		else
			return (c);
	}
	return (-1);
}
