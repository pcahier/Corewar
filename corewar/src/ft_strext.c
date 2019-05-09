/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strext.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcahier <pcahier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 08:56:15 by pcahier           #+#    #+#             */
/*   Updated: 2019/04/22 09:13:46 by pcahier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strext(const char *filename, const char *extension)
{
	size_t	ext_len;

	ext_len = ft_strlen(extension);
	if (ext_len > ft_strlen(filename) || *filename == '\0'
			|| *extension == '\0')
		return (0);
	while (*filename)
		filename++;
	while (*extension)
		extension++;
	while (ext_len)
	{
		if (*extension != *filename)
			return (0);
		extension--;
		filename--;
		ext_len--;
	}
	return (1);
}
