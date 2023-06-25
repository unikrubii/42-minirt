/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_key_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthitiku <sthitiku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:31:00 by nnakarac          #+#    #+#             */
/*   Updated: 2023/06/25 11:34:03 by sthitiku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	mlx_key_close(t_handle *handy)
{
	mlx_clear_window(handy->data.mlx, handy->data.win);
	mlx_destroy_window(handy->data.mlx, handy->data.win);
	objlst_clear(&handy->objects);
	lightlst_clear(&handy->lights);
	handy->data.mlx = NULL;
	handy->data.mlx = NULL;
	deinit_color_pix(handy);
	camera_deinit(handy->camera);
	exit(0);
}

int	mlx_close(t_handle *handy)
{
	mlx_clear_window(handy->data.mlx, handy->data.win);
	mlx_destroy_window(handy->data.mlx, handy->data.win);
	objlst_clear(&handy->objects);
	lightlst_clear(&handy->lights);
	handy->data.win = NULL;
	handy->data.mlx = NULL;
	deinit_color_pix(handy);
	camera_deinit(handy->camera);
	exit(0);
}

int	rt_key_handler(int keycode, t_handle *handy)
{
	if (keycode == KEY_ESC)
		mlx_key_close(handy);
	else if (keycode == KEY_SPACE)
		handy->to_render = 1;
	else
		handy->to_render = 0;
	return (0);
}
