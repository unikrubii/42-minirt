/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:24:20 by nnakarac          #+#    #+#             */
/*   Updated: 2023/04/17 17:08:26 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define _GNU_SOURCE

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <string.h>
# include <errno.h>
# include <limits.h>
# include <float.h>
# include "libft.h"
# include "get_next_line.h"
# include "mlx.h"
# include "nml_matrix.h"

# define PI 3.14159265358979323846
# define EPSILON 0.000001

# define WIDTH 1024
# define HEIGHT 768

enum e_key {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17,
	KEY_Q = 12,
	KEY_W = 13,
	KEY_E = 14,
	KEY_A = 0,
	KEY_S = 1,
	KEY_D = 2,
	KEY_F = 3,
	KEY_Z = 6,
	KEY_C = 8,
	KEY_R = 15,
	KEY_PLUS = 24,
	KEY_MINUS = 27,
	KEY_SQBO = 30,
	KEY_O = 31,
	KEY_I = 34,
	KEY_SQBC = 33,
	KEY_P = 35,
	KEY_QUOTE = 39,
	KEY_SEMI = 41,
	KEY_SPACE = 49,
	KEY_ESC = 53,
	KEY_LEFT = 123,
	KEY_RIGHT = 124,
	KEY_DOWN = 125,
	KEY_UP = 126,
};

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_draw
{
	int		begin_x;
	int		begin_y;
	int		end_x;
	int		end_y;
	int		color;
}	t_draw;

typedef struct s_vars {
	void	*mlx;
	void	*win;
	t_data	img;
}	t_vars;

typedef struct s_mouse
{
	int		is_pressed;
	int		pos_x;
	int		pos_y;
}	t_mouse;

typedef struct s_camera
{
	t_nml_mat		*view;
	t_nml_mat_lup	*view_lup;
	float			fov;
}	t_camera;

typedef struct s_object
{
	int				type;
	t_nml_mat		*pos;
	t_nml_mat		*dir;
	t_nml_mat		*color;
	float			radius;
	float			height;
	float			ambient;
	float			diffuse;
	float			specular;
	float			reflective;
	float			transparency;
	float			refractive_index;
	struct s_object	*next;
}	t_object;

typedef struct s_light
{
	t_nml_mat		*pos;
	t_nml_mat		*color;
	float			brightness;
	struct s_light	*next;
}	t_light;
typedef struct s_handle
{
	t_vars		data;
	t_draw		draw;
	t_mouse		mouse;
	t_camera	*camera;
	t_object	*objects;
	t_light		*lights;
}	t_handle;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

void	mlx_draw(t_data *data, t_draw *draw);

void	mlx_re_draw(t_handle *handy);

void	mlx_key_close(t_handle *handy);

int		mlx_close(t_vars *vars);

int		rt_key_handler(int keycode, t_handle *handy);

int		render(t_handle *handy);

#endif
