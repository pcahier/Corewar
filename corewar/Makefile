# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agrossma <agrossma@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/19 03:25:47 by agrossma          #+#    #+#              #
#    Updated: 2019/04/27 18:09:37 by pcahier          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL		:= /bin/bash

################################################################################
# Start of system configuration section                                        #
################################################################################

NAME		:= corewar
CC			:= gcc
CFLAGS		+= -Wall -Wextra -Werror
MKDIR		:= mkdir -p
RM			:= rm -f
RMDIR		:= rmdir
ECHO		:= echo
QUIET		:= @
MAKE		:= make

################################################################################
# End of system configuration section                                          #
################################################################################

################################################################################
# Start of files definition section                                            #
################################################################################

_INCLUDE	:= include/
INCLUDE		:= \
	corewar.h
OP			:= op.h
CFLAGS		+= -I$(_INCLUDE)
_SRC		:= src/
SRC			:= \
	corewar.c 				\
	arena_init.c			\
	corechamp.c				\
	corerror.c				\
	display.c				\
	ft_atoipc.c				\
	ft_atouipc.c			\
	ft_endian_swap.c		\
	game_manager.c			\
	get_param.c				\
	init.c					\
	lst_manager.c			\
	ocp.c					\
	op_ld.c					\
	op_ldi.c				\
	op_manager.c			\
	op_math.c				\
	op_math2.c				\
	op_math3.c				\
	op_oth.c				\
	op_st.c					\
	op.c					\
	process_manager.c		\
	utilities.c				\
	ft_strext.c

_OBJ		:= obj/
OBJ			+= $(addprefix $(_OBJ), $(SRC:.c=.o))

################################################################################
# End of files definition section                                              #
################################################################################

################################################################################
# Start of libraries definition section                                        #
################################################################################

_LIBFT		:= ../libft/
CFLAGS		+= -I$(_LIBFT)$(_INCLUDE)
LIBFT_A		:= libft.a
LIBFT		:= ft

################################################################################
# End of libraries definition section                                          #
################################################################################

################################################################################
# Start of linking configuration section                                       #
################################################################################

LD			:= gcc
LDFLAGS		:= -L$(_LIBFT)
LDLIBS		:= -l$(LIBFT)

################################################################################
# End of linking configuration section                                         #
################################################################################

################################################################################
# Start of rules definition section                                            #
################################################################################

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(_LIBFT)$(LIBFT_A) $(_OBJ) $(OBJ)
	$(QUIET)$(ECHO) "[$(NAME)]	LD	$@"
	$(QUIET)$(LD) $(OBJ) $(LDFLAGS) $(LDLIBS) -o $@

$(_LIBFT)$(LIBFT_A):
	$(QUIET)$(MAKE) -C $(_LIBFT)

$(_OBJ):
	$(QUIET)$(MKDIR) $(_OBJ)

$(_OBJ)%.o: $(_SRC)%.c $(_INCLUDE)$(INCLUDE) $(_INCLUDE)$(OP)
	$(QUIET)$(ECHO) "[$(NAME)]	CC	$(notdir $@)"
	$(QUIET)$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(QUIET)$(ECHO) "[$(NAME)]	RM	$(_OBJ)"
	$(QUIET)$(RM) $(OBJ)
	$(QUIET)if [ -d "$(_OBJ)" ]; then \
		$(RMDIR) $(_OBJ); \
	fi
	$(QUIET)$(MAKE) -C $(_LIBFT) $@

fclean: clean
	$(QUIET)$(ECHO) "[$(NAME)]	RM	$(NAME)"
	$(QUIET)$(RM) $(NAME)
	$(QUIET)$(MAKE) -C $(_LIBFT) $@

re: fclean all

################################################################################
# End of rules definition section                                              #
################################################################################
