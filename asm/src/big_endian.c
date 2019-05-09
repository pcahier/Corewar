/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_endian.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrossma <agrossma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 01:02:46 by agrossma          #+#    #+#             */
/*   Updated: 2019/04/26 23:46:04 by agrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

unsigned short	ft_bigendian_16(unsigned int i)
{
	return (((i >> 8) & 0x00ff) | ((i << 8) & 0xff00));
}

unsigned int	ft_bigendian_32(unsigned int i)
{
	return (((i >> 24) & 0x000000ff)
	| ((i >> 8) & 0x0000ff00)
	| ((i << 8) & 0x00ff0000)
	| ((i << 24) & 0xff000000));
}
