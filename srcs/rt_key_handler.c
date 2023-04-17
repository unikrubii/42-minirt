/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_key_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnakarac <nnakarac@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:31:00 by nnakarac          #+#    #+#             */
/*   Updated: 2023/04/12 19:06:16 by nnakarac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	mlx_key_close(t_handle *handy)
{
	mlx_clear_window(handy->data->mlx, handy->data->win);
	mlx_destroy_window(handy->data->mlx, handy->data->win);
	handy->data->win = NULL;
	handy->data->mlx = NULL;
	free(handy->mouse);
	exit(0);
}

int	rt_key_handler(int keycode, t_handle *handy)
{
	if (keycode == KEY_ESC)
		mlx_key_close(handy);
	else
		mlx_re_draw(handy);
	return (0);
}
