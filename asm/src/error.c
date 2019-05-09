/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrossma <agrossma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 20:10:37 by agrossma          #+#    #+#             */
/*   Updated: 2019/04/08 16:48:17 by agrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char	*ft_strerror(int errnum)
{
	static char	*tab[5] = {
		"Arg list too long",
		"Arg list too short",
		"Wrong filename extension",
		"Program name too long",
		"Program comment too long"
	};

	return (tab[errnum]);
}

void		ft_perror(int errnum)
{
	ft_dprintf(2, "%s: %s\n", PROG_NAME, ft_strerror(errnum));
}
