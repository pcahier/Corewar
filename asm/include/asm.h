/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrossma <agrossma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 07:58:32 by agrossma          #+#    #+#             */
/*   Updated: 2019/04/27 15:27:41 by agrossma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

/*
** Includes for authorized functions
** stdlib.h for exit(3), malloc(3), realloc(3) and free(3)
** unistd.h for close(2), read(2) and write(2)
** string.h for strerror(3)
** errno.h for errno(3)
** sys/types.h, sys/stat.h and fcntl.h for open(2)
** libft.h for the libft functions
** op.h for the asm structs and defines
*/
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "libft.h"
# include "op.h"

# define PROG_NAME "asm"

# define E_2BIG		0
# define E_2LIT		1
# define E_WEXT		2
# define E_PN2L		3
# define E_CO2L		4

# define E_LEX		0
# define E_NAME		1
# define E_COMMENT	2
# define E_WRO		3
# define E_LAB		4
# define E_TOK		5
# define E_EMP		6

enum			e_state
{
	S_NORMAL,
	S_HEADER,
	S_LABEL,
	S_AFTER_LABEL,
	S_TOKEN,
	S_COMMENT,
	S_AFTER,
	S_ERROR = -1
};

typedef struct	s_token
{
	int				type;
	int				argc;
	char			*argv[MAX_ARGS_NUMBER];
	int				args_type[MAX_ARGS_NUMBER];
	struct s_token	*next;
}				t_token;

typedef struct	s_lexer
{
	enum e_state	state;
	int				tokenc;
	int				labelc;
	int				name:1;
	int				comment:1;
	int				linec;
	int				col;
	int				fd;
	int				*mem;
	t_token			*current_token;
	t_token			*lst_token;
	t_list			*lst_label;
}				t_lexer;

t_op			ft_getop(char *str);
t_op			ft_getop_type(int type);

void			ft_perror(int errnum);

int				ft_parse(t_lexer *lexer, t_header *header);

void			ft_tokenadd(t_token **lst, t_token *token);
void			ft_tokenfree(t_token **token);

void			ft_tokenize(t_lexer *lexer);

unsigned int	ft_bigendian_32(unsigned int i);
unsigned short	ft_bigendian_16(unsigned int i);

void			ft_headercpy(t_lexer *lexer, t_header *header, int ft);

void			ft_plexerr(t_lexer *lexer, int errtype);

void			ft_addarg(t_lexer *lexer);

int				ft_isregister(char *str, t_token *token);
int				ft_isdirect(char *str, t_token *token);
int				ft_isindirect(char *str, t_token *token);
int				ft_isvalidlabel(char *str);
void			ft_lstdelcontent(void *content, size_t content_size);

void			ft_clean(t_lexer *lexer);

int				ft_labelexist(char *label, t_lexer *lexer);

void			ft_write_asm(t_lexer *lexer);

t_list			*ft_getlabel(t_lexer *lexer, char *str);

#endif
