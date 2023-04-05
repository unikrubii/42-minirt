# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/16 22:45:00 by nnakarac          #+#    #+#              #
#    Updated: 2023/04/05 22:19:59 by nnakarac         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc -g
CFLAGS = -Wall -Werror -Wextra

NAME = libnml_matrix.a
RM = rm -rf
SRC_DIR = srcs/
OBJ_DIR = objs/
INC_DIR = includes
LIB_DIR = ../libft/

NML = nml_util.c \
	nml_util2.c \
	nml_mat_new.c \
	nml_mat_free.c \
	nml_mat_rnd.c \
	nml_mat_sqr.c \
	nml_mat_eye.c \
	nml_mat_equal.c \
	nml_mat_print.c \
	nml_col_row_get.c \
	nml_mat_set.c \
	nml_mat_mult.c \
	nml_mat_smult.c \
	nml_col_row_rem.c \
	nml_col_row_swap.c \
	nml_row_addrow.c \
	nml_mat_cath.c \
	nml_mat_catv.c \
	nml_mat_add.c \
	nml_mat_sub.c \
	nml_mat_dot.c \
	nml_mat_transp.c \
	nml_mat_trace.c \
	nml_mat_pivot.c \
	nml_mat_ref.c \
	nml_mat_rref.c \
	nml_mat_absmaxr.c \
	nml_mat_lup_new.c \
	nml_mat_lup_free.c \
	nml_mat_lup_print.c \
	nml_mat_lup_solve.c \
	nml_mat_det.c \
	nml_mat_lu_get.c \
	nml_ls_solvefwd.c \
	nml_ls_solvebck.c \

SRCS = $(NML)
OBJS = $(SRCS:.c=.o)
INCS = -I$(INC_DIR) \
	-I$(LIB_DIR)includes
LIBS = -L$(LIB_DIR) -lft \

all: $(NAME)

$(NAME): $(addprefix $(OBJ_DIR),$(OBJS))
	@ar -rcs $@ $^
	@ranlib $@

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< $(INCS) -o $@

clean:
	@$(RM) $(OBJ_DIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
