NAME = miniRT
CC = gcc -g
CFLAGS = -Wall -Wextra -Werror
RM = /bin/rm -rf

SRC_DIR = srcs/
OBJ_DIR = objs/
INC_DIR = includes
LIB_DIR = libft/
NML_DIR = nml_matrix/

UNAME = $(shell uname -s)
ifeq ($(UNAME), Linux)
	MLX_DIR		= minilibx-linux
	MLX_FLAGS	= -Imlx_Linux -Lmlx_Linux -lmlx_Linux -lXext -lX11 -lm -lz
	INCS		= -I$(INC_DIR) \
				  -I$(LIB_DIR)includes \
				  -I$(NML_DIR)includes \
				  -I/usr/include
	LIBS		= -L$(LIB_DIR) -lft \
				  -L$(NML_DIR) -lnml_matrix \
				  -L/usr/lib
else
	# MLX_DIR		= minilibx_macos
	MLX_DIR		= minilibx
	MLX_FLAGS	= -L$(MLX_DIR) -lmlx \
				  -framework OpenGL \
				  -framework AppKit
	INCS		= -I$(INC_DIR) \
				  -I$(LIB_DIR)includes \
				  -I$(NML_DIR)includes \
				  -I$(MLX_DIR)
	LIBS		= -L$(LIB_DIR) -lft \
				  -L$(NML_DIR) -lnml_matrix
endif

SRCS =	rt_key_handler.c \
		rt_draw.c \
		rt_render.c \
		blink.c \
		endian.c \
		camera_1.c \
		camera_2.c \
		camera_3.c \
		camera_4.c \
		camera_5.c \
		camera_6.c \
		v_util.c \
		ray_util.c \
		objectbase.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME) | copy

$(NAME):	$(addprefix $(OBJ_DIR),$(OBJS))
		@make -C $(LIB_DIR) --silent
		@make -C $(MLX_DIR) --silent
		@make -C $(NML_DIR) --silent
		@$(CC) -g $(CFLAGS) $(addprefix $(OBJ_DIR),$(OBJS)) $(LIBS) $(MLX_FLAGS) -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) -g $(CFLAGS) -c $< $(INCS) -o $@

copy:
	@$(shell cp ./minilibx/libmlx.dylib .)

clean:
	@make -C $(LIB_DIR) clean --silent
	@make -C $(NML_DIR) clean --silent
	@$(RM) $(OBJ_DIR)

fclean: clean
	@make -C $(LIB_DIR) fclean --silent
	@make -C $(MLX_DIR) clean --silent
	@make -C $(NML_DIR) fclean --silent
	@$(RM) libmlx.dylib
	@$(RM) $(NAME)
	@$(RM) libmlx.dylib.dSYM
	@$(RM) $(NAME).dSYM

re: fclean all

.PHONY: fclean all clean re miniRT copy
