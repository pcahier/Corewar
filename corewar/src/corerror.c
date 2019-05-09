/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corerror.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcahier <pcahier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 17:04:48 by pcahier           #+#    #+#             */
/*   Updated: 2019/04/27 17:49:29 by pcahier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	ft_error(t_error errnum)
{
	if (errnum == H_VAL)
		write(STDOUT_FILENO, "Error : Stop messing with .h values.\n", 37);
	else if (errnum == READ_ERR)
		write(STDOUT_FILENO, "Error : Read or close error\n", 28);
	else if (errnum == HEADER_ERR)
		write(STDOUT_FILENO, "Error : Invalid header\n", 23);
	else if (errnum == LENGTH_ERR)
		write(STDOUT_FILENO, "Error : Length of champion is wrong\n", 36);
	else if (errnum == VAL_OPT)
		write(STDOUT_FILENO, "Error : Invalid value for an option.\n", 37);
	else if (errnum == OPT_ERR)
		write(STDOUT_FILENO, "Error : Invalid option, see usage.\n", 35);
	else if (errnum == DUP_ERR)
		write(STDOUT_FILENO, "Error : Duplicated champion number.\n", 37);
	else if (errnum == MANY_CHAMP)
		write(STDOUT_FILENO, "Error : Too many champions.\n", 28);
	else if (errnum == NO_NAME)
		write(STDOUT_FILENO, "Error : You forgot to name a champion.\n", 39);
	else if (errnum == EXT_ERR)
		write(STDOUT_FILENO, "Error : Wrong extension for champion.\n", 38);
	exit(0);
}

int		ft_usage(void)
{
	ft_printf("Usage: ./corewar [-options] [-n N] <champion1.cor> <...>\n" \
			"#### TEXT OUTPUT MODE ######################################\n" \
			" -dump D   : Dumps memory after D cycles then exits.\n" \
			" -d	D	: Same as -dump.\n" \
			" -w	W	: When printing a dump, determines width.\n" \
			" -n    N   : assign N number to next champion register 1.\n" \
			" -v    V   : Verbosity levels, value can enable multiples.\n" \
			"           - 0  : Show essentials only.\n" \
			"           - 1  : Hide lives.\n" \
			"           - 2  : Show cycles.\n" \
			"           - 4  : Show operations.\n" \
			"           - 8  : Show deaths. \n" \
			"           - 16 : Show PC movements (except for jumps).\n" \
			" D, W, N and V must be integers.\n" \
			" D value is between 1 and 2147483647, W is between 1 and 128.\n" \
			" N is betzeen 1 and 4294967295, V is between 0 and 31.\n" \
			" All cited values being included in the range.\n" \
			"############################################################\n");
	return (0);
}
