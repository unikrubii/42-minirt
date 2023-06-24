/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthitiku <sthitiku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:24:20 by nnakarac          #+#    #+#             */
/*   Updated: 2023/06/24 18:40:05 by sthitiku         ###   ########.fr       */
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
# include <time.h>
# include "libft.h"
# include "get_next_line.h"
# include "mlx.h"
# include "nml_matrix.h"
# include "camera.h"
# include "ray.h"
# include "scene.h"
# include "t_base.h"
# include "objectbase.h"
# include "lightbase.h"
# include "gtform.h"

# define PI 3.14159265358979323846
# define EPSILON 1e-21f
# define ONE_DEG 0.01745329251f

# define WIDTH 1280
# define HEIGHT 720

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

void	mlx_draw(t_data *data, t_draw *draw);
void	mlx_draw2(t_data *data, t_draw *draw);

int		mlx_re_draw(t_handle *handy);

void	mlx_key_close(t_handle *handy);

int		mlx_close(t_handle *handy);

int		rt_key_handler(int keycode, t_handle *handy);

int		render(t_handle *handy);

int		endian(void);

void	scene_deinit(t_scene *scn);
void	scene_init(t_scene *scn);

int		read_map(int argc, char **argv, t_handle *handy);

void	init_color_pix(t_handle *handy);
void	deinit_color_pix(t_handle *handy);

void	opt_color(t_handle *handy);

void	pix_color_put(t_scene *scn, t_handle *handy);
void	pix_color_put_v(t_scene *scn, t_nml_mat *v_color, t_handle *handy);

// readmap
int		get_row(char *path);
char	**get_map(char *path, int row_count);
float	rt_atof(char *str);
void	free_arr(char **arr);

#endif
