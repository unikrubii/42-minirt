/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_key_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:31:00 by nnakarac          #+#    #+#             */
/*   Updated: 2023/06/03 12:13:26 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	deinit_color_pix(t_handle *handy)
{
	int			width;
	int			height;
	t_nml_mat	**dst;

	// dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));

	width = 0;
	height = 0;
	while (width < WIDTH)
	{
		height = 0;
		while (height < HEIGHT)
		{
			dst = handy->vv_color + (HEIGHT * width) + (height);
			nml_mat_free(*dst);
			height++;
		}
		width++;
	}
	free(handy->vv_color);
}

void	mlx_key_close(t_handle *handy)
{
	mlx_clear_window(handy->data.mlx, handy->data.win);
	mlx_destroy_window(handy->data.mlx, handy->data.win);
	deinit_color_pix(handy);
	objlst_clear(&handy->objects);
	lightlst_clear(&handy->lights);
	handy->data.mlx = NULL;
	handy->data.mlx = NULL;
	exit(0);
}

int	mlx_close(t_handle *handy)
{
	mlx_clear_window(handy->data.mlx, handy->data.win);
	mlx_destroy_window(handy->data.mlx, handy->data.win);
	deinit_color_pix(handy);
	objlst_clear(&handy->objects);
	lightlst_clear(&handy->lights);
	handy->data.win = NULL;
	handy->data.mlx = NULL;
	exit(0);
}

int	rt_key_handler(int keycode, t_handle *handy)
{
	if (keycode == KEY_ESC)
		mlx_key_close(handy);
	else
		handy->to_render = 1;
	return (0);
}
