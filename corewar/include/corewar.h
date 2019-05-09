/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcahier <pcahier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 21:34:44 by pcahier           #+#    #+#             */
/*   Updated: 2019/04/27 17:46:40 by agrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

/*
** Includes for authorized functions
** stdlib.h for exit, malloc, realloc and free
** unistd.h for close, read and write
** stdio.h for perror
** errno.h for strerror
** sys/types.h, sys/stat.h and fcntl.h for open
** errno.h for errno(3)
** libft.h for the libft functions
*/
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/types.h>
# include <fcntl.h>
# include <errno.h>
# include "libft.h"
# include "op.h"

typedef	enum		e_error
{
	H_VAL,
	READ_ERR,
	HEADER_ERR,
	LENGTH_ERR,
	VAL_OPT,
	OPT_ERR,
	DUP_ERR,
	MANY_CHAMP,
	NO_NAME,
	EXT_ERR
}					t_error;

typedef struct		s_player
{
	uint32_t		magic;
	t_uc			name[PROG_NAME_LENGTH + 4];
	uint32_t		code_length;
	t_uc			comment[COMMENT_LENGTH + 4];
	t_uc			code[CHAMP_MAX_SIZE];
	unsigned int	number;
	uint32_t		start_address;
}					t_player;

typedef struct		s_process
{
	int				nprocess;
	int				reg[REG_NUMBER];
	int				pc;
	char			carry;
	int				llc;
	int				next_op;
	int				op_exec;
}					t_process;

typedef struct		s_vm
{
	t_list			*list_process;
	t_player		list_player[MAX_PLAYERS];
	int				nplayer;
	int				nprocess;
	t_uc			arena[MEM_SIZE];
	int				dump_value;
	int				verbose_val;
	int				last_player_id;
	int				ncycle;
	int				nlive_ctd;
	int				ncycle_ctd;
	int				ncycle_fctd;
	int				cycle_to_die;
	int				nb_check_dec_ctd;
	int				width;
}					t_vm;

void				vm_generate_arena(t_vm *vm);

void				display_arena(t_vm *vm);
int					verbose_print(t_vm *vm, int verbosity);
void				print_adv(t_vm *vm, t_list *process, int shift);
void				ft_print_intro(t_vm *vm);

void				vm_launch_game(t_vm *vm);

void				vm_init(t_vm *vm);

void				define_next_op(t_vm *vm, t_process *process);

t_list				*del_head_lst_process(t_vm *vm, t_list *process);
t_list				*del_elem_lst_process(t_list *process, t_list **previous);

void				process_creation(t_vm *vm, t_list *process
													, unsigned int new_pc);
void				browse_list_process(t_vm *vm);
void				kill_list_process(t_vm *vm);

int					reverse_bytes(t_vm *vm, int pc, int nbytes);
int					search_id_player(t_vm *vm, unsigned int num_player);
void				load_reg(t_vm *vm, unsigned int value, int address);
int					check_arg_validity(t_uc id_op, t_uc b_oct, t_uc narg);
int					calc_shift(t_uc b_ocp, t_uc direct_size, t_uc nb_arg);

int					get_param_direct(t_vm *vm, t_list *process, t_uc *sft
															, t_uc arg_type);
int					get_param_indirect(t_vm *vm, t_process *p_c, t_uc *sft
															, t_uc arg_type);

int					ft_strext(const char *filename, const char *extension);
void				ft_error(t_error errnum);
void				ft_get_champ(int ac, char **av, t_vm *vm, unsigned int *n);
int					ft_usage(void);
int					ft_atoipc(const char *str);
int					ft_atouipc(const char *str);

uint32_t			ft_uns_swaptobig(uint32_t num);

int					ocp1(int x);
int					ocp2(int x);

#endif
