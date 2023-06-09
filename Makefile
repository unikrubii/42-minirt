NAME = miniRT

CC = gcc -g -Ofast

CFLAGS = -Wall -Wextra -Werror
RM = /bin/rm -rf

SRC_DIR = srcs/
OBJ_DIR = objs/
INC_DIR = includes
LIB_DIR = libft/
NML_DIR = nml_matrix/
CAM_DIR = camera_ray/

LIGHT_DIR = srcs/lights/
PRIM_DIR = srcs/primitives/
MAT_DIR = srcs/materials/

UNAME = $(shell uname -s)
ifeq ($(UNAME), Linux)
	MLX_DIR		= minilibx-linux
	MLX_FLAGS	= -Imlx_Linux -Lmlx_Linux -lmlx_Linux -lXext -lX11 -lm -lz
	INCS		= -I$(INC_DIR) \
				  -I$(LIB_DIR)includes \
				  -I$(NML_DIR)includes \
				  -I$(CAM_DIR)includes \
				  -I/usr/include
	LIBS		= -L$(LIB_DIR) -lft \
				  -L$(NML_DIR) -lnml_matrix \
				  -L$(CAM_DIR) -lcamera_ray \
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
				  -I$(CAM_DIR)includes \
				  -I$(MLX_DIR)
	LIBS		= -L$(LIB_DIR) -lft \
				  -L$(NML_DIR) -lnml_matrix \
				  -L$(CAM_DIR) -lcamera_ray
endif

SRCS =	rt_key_handler.c \
		rt_draw.c \
		rt_render.c \
		rt_render_helper.c \
		blink.c \
		endian.c \
		gtform.c \
		gtform2.c \
		gtform3.c \
		gtform4.c \
		pix_color.c \
		rt_readmap.c \
		rt_readmap_utils.c \
		rt_read_sphere_plane.c \
		rt_read_cam_light.c \
		rt_read_cyl_cn.c \
		rt_atof.c \

SRCS_LIGHT =	lightbase.c \
				lightlist.c \
				pointlight.c \
				pointlightutil.c \

SRCS_PRIM =	objectbase.c \
			objectbaseutil.c \
			objectlist.c \
			sphere.c \
			plane.c \
			cylinder.c \
			cylinder_utils.c \
			cone.c \
			cone_utils.c \
			cyl_cone_utils.c \

SRCS_MAT =	materialbase.c \
			materialbaseutil.c \
			simplemat.c \
			simplematutil.c \

OBJS = $(SRCS:.c=.o)

OBJS_LIGHT = $(SRCS_LIGHT:.c=.o)
OBJS_PRIM = $(SRCS_PRIM:.c=.o)
OBJS_MAT = $(SRCS_MAT:.c=.o)

all: $(NAME) | copy

$(NAME):	$(addprefix $(OBJ_DIR),$(OBJS)) $(addprefix $(OBJ_DIR),$(OBJS_LIGHT)) $(addprefix $(OBJ_DIR),$(OBJS_PRIM)) $(addprefix $(OBJ_DIR),$(OBJS_MAT))
		@make -C $(LIB_DIR) --silent
		@make -C $(MLX_DIR) --silent
		@make -C $(NML_DIR) --silent
		@make -C $(CAM_DIR) --silent
		@$(CC) -g $(CFLAGS) $(addprefix $(OBJ_DIR),$(OBJS)) $(addprefix $(OBJ_DIR),$(OBJS_LIGHT)) $(addprefix $(OBJ_DIR),$(OBJS_PRIM)) $(addprefix $(OBJ_DIR),$(OBJS_MAT)) $(LIBS) $(MLX_FLAGS) -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) -g $(CFLAGS) -c $< $(INCS) -o $@

$(OBJ_DIR)%.o: $(LIGHT_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) -g $(CFLAGS) -c $< $(INCS) -o $@

$(OBJ_DIR)%.o: $(PRIM_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) -g $(CFLAGS) -c $< $(INCS) -o $@

$(OBJ_DIR)%.o: $(MAT_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) -g $(CFLAGS) -c $< $(INCS) -o $@

copy:
	@$(shell cp ./minilibx/libmlx.dylib .)

clean:
	@make -C $(LIB_DIR) clean --silent
	@make -C $(NML_DIR) clean --silent
	@make -C $(CAM_DIR) clean --silent
	@$(RM) $(MLX_DIR)/*.swiftsourceinfo
	@$(RM) $(OBJ_DIR)

fclean: clean
	@make -C $(LIB_DIR) fclean --silent
	@make -C $(MLX_DIR) clean --silent
	@make -C $(NML_DIR) fclean --silent
	@make -C $(CAM_DIR) fclean --silent
	@$(RM) libmlx.dylib
	@$(RM) $(NAME)
	@$(RM) libmlx.dylib.dSYM
	@$(RM) $(NAME).dSYM

lib:	$(addprefix $(OBJ_DIR),$(OBJS))
	@make -C $(LIB_DIR) re --silent
	@make -C $(NML_DIR) re --silent
	@make -C $(CAM_DIR) re --silent
	@$(CC) -g $(CFLAGS) $(addprefix $(OBJ_DIR),$(OBJS)) $(LIBS) $(MLX_FLAGS) -o $(NAME)

re: fclean all

.PHONY: fclean all clean re miniRT copy
