# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/30 20:16:16 by nnakarac          #+#    #+#              #
#    Updated: 2023/06/05 17:26:04 by nnakarac         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc -g -Ofast
CFLAGS = -Wall -Werror -Wextra

NAME = libcamera_ray.a

RM = rm -rf

SRC_DIR = srcs/
OBJ_DIR = objs/
INC_DIR = includes
LIB_DIR = ../libft/
MAT_DIR = ../nml_matrix/

CR = camera_init_set_1.c \
	camera_set_2.c \
	camera_get_1.c \
	camera_get_2.c \
	camera_get_3.c \
	camera_get_1.c \
	camera_geomet_gen_ray.c \
	ray.c \

SRCS = $(CR)

OBJS = $(SRCS:.c=.o)

INCS = -I$(INC_DIR) \
	-I$(LIB_DIR)includes \
	-I$(MAT_DIR)includes \

LIBS = -L$(LIB_DIR) -lft \
	-L$(MAT_DIR) -lnml_matrix \

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
