/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrossma <agrossma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 16:51:02 by agrossma          #+#    #+#             */
/*   Updated: 2019/04/26 14:12:57 by agrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Allocates and returns the copy of a stretch of the string s.
** The stretch begins at the index start and has for length len.
** If start and len don't designate a valid stretch from the string,
** the behavior is undefined
** \param s The string in which to search
** \param start The index of the string where begin the stretch
** \param len The length of the stretch to copy
** \return The strech or NULL if the allocation failed
*/

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*stretch;

	if (s == NULL)
		return (NULL);
	if ((stretch = ft_strnew(len)) == NULL)
		return (NULL);
	while (start-- != 0)
		s++;
	ft_strncpy(stretch, s, len);
	return (stretch);
}
